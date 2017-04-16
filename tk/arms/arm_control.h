
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

#define status_buffer_size 20

using namespace std;
string packet_to_string(struct packet in_packet);
string point_to_string(struct point6d in_point);

struct point6d{
  int x, y, z, r, p, t;
};

struct packet{
  char status, robot, speed;
  int index;
  point6d data;
};

class Arm_Control{

  public:
    Arm_Control(int arm_num,string ip_addr, int port_num);
    ~Arm_Control();
    bool is_connected();

    int send_point(char speed,int x,int y,int z);

  private:
    char* robot_status;
    bool connected= false;
    int socket_id;
    int arm_num;
    int tcp_connect(string ip_addr,int port_num);
    int send_packet(struct packet);

};
