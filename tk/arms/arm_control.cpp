/*
This file manages control of the robot through a TCP client connected to the robot's
    MV controller.

Primarily used to send points to the controller, it can be constructed in any file.

On the other end, the TCP.Server0 program needs to be running, accepting a string
    packet shaped appropriately.
*/

#include "arm_control.h"
Arm_Control::Arm_Control(int in_arm_num, string ip_addr, int port_num)
{
  arm_num = in_arm_num;
  robot_status = (char*)malloc(status_buffer_size);
  if(tcp_connect(ip_addr, port_num) == 0)
  {
    connected = true;
  }else{
    connected = false;
  }
}
Arm_Control::~Arm_Control(){
  close(socket_id);
  free(robot_status);
}
bool Arm_Control::is_connected()
{
  return connected;
}

int Arm_Control::send_point(char speed,int x,int y,int z)
{
  struct packet new_pckt;
  struct point6d new_data;
  new_pckt.status = 4;
  new_pckt.robot = arm_num;
  new_pckt.speed = speed;
  new_pckt.index = 0;
  new_data.x = x;
  new_data.y = y;
  new_data.z = z;
  new_data.r = 0;
  new_data.p = 180;
  new_data.t = 0;
  new_pckt.data = new_data;
  curr_position = new_data;
  //this is a really neat call to asynchronously send a point to the robot.
  //the future produced by it is able to be checked to see if the robot has replied.
  auto ret_movement_status = async(launch::async,&Arm_Control::send_packet,this,new_pckt);
  movement_status = std::move(ret_movement_status);
  return 1;//send_packet(new_pckt);
}

int Arm_Control::send_point(char speed,Point3d input)
{

  struct packet new_pckt;
  struct point6d new_data;
  new_pckt.status = 4;
  new_pckt.robot = arm_num;
  new_pckt.speed = speed;
  new_pckt.index = 0;
  new_data.x = input.x;
  new_data.y = input.y;
  new_data.z = input.z;
  new_data.r = 0;
  new_data.p = 180;
  new_data.t = 0;
  new_pckt.data = new_data;
  curr_position = new_data;
  auto ret_movement_status = async(launch::async,&Arm_Control::send_packet,this,new_pckt);
  movement_status = std::move(ret_movement_status);
  return 1;//send_packet(new_pckt);
}

int Arm_Control::send_transformed(char speed,int x, int y, int z)
{

}

bool Arm_Control::is_ready()
  {
    if(movement_status.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
      return true;
    else
      return false;
  }

cv::Point3d Arm_Control::get_position(){
  cv::Point3d ret_point;
  if(movement_status.get())
  {

    ret_point.x = curr_position.x;
    ret_point.y = curr_position.y;
    ret_point.z = curr_position.z;
  }else{
      ret_point.x = 000;
      ret_point.y = 000;
      ret_point.z = 000;
  }
  return ret_point;
}

int Arm_Control::send_packet(struct packet in_packet)
{

  if(connected)
  {
    string message = packet_to_string(in_packet);
    int len =strlen((char *)message.c_str());
    // std::cout << "message: " << message<<'\n';
    if(send(socket_id, (char *)message.c_str(), len, 0) > 0)
    {
      return recv(socket_id, robot_status, status_buffer_size, 0);
    }else{
      return -1;
    }
  }else{
    return -52;
  }
}

int Arm_Control::tcp_connect(string ip_addr, int port_num)
{
  struct addrinfo hints, * res;
  int status;

  //clear hints
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(ip_addr.c_str(),to_string(port_num).c_str(), &hints, &res);
  if(status != 0)
  {
    fprintf(stderr, "Error getaddrinfo\n");
    return -1;// exit(1);
  }

  socket_id = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(socket_id < 0)
  {
    fprintf(stderr, "Error socket \n");
    return -2;//exit(2);
  }

  status = connect(socket_id, res->ai_addr, res->ai_addrlen);
  if(status < 0)
  {
    fprintf(stderr, "Error connecting to robot \n");
    return -3;//exit(3);
  }


  // int numbytes = 0;
  // char buf[10];
  // numbytes = recv(socket_id,buf,10,0);
  // if(numbytes == -1)
  // {
  //   fprintf(stderr, "Error receive \n");
  //   exit(4);
  // }
  // buf[numbytes] = '\0';
  // printf("Received %s \n", buf);
  return 0;

  freeaddrinfo(res);

}

//these to_strings produce the packets that are sent to the robot.
string packet_to_string(struct packet in_packet)
{
  return to_string(in_packet.status)+","+to_string(in_packet.robot)+","+
          to_string(in_packet.speed)+","+to_string(in_packet.index)+","+
          point_to_string(in_packet.data);
}
string point_to_string(struct point6d in_point)
{
  return to_string(in_point.x)+","+to_string(in_point.y)+","+
          to_string(in_point.z)+","+to_string(in_point.r)+","+
          to_string(in_point.p)+","+to_string(in_point.t);
}
