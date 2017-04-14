#!/usr/bin/env python

import socket
import time
import numpy
import packet

class connection:
    """docstring for connection."""
    socket  = 0
    ip_addr = 0
    def __init__(self, in_ip_addr):
        self.ip_addr = in_ip_addr
        self.socket = self.start_connection()



    def start_connection(self):
        TCP_IP = self.ip_addr
        TCP_PORT = 5005
<<<<<<< HEAD
        BUFFER_SIZE = 1024
=======
        BUFFER_SIZE = 300
>>>>>>> 583970e4529ad34ad0a07bb23c0284a40d48b1ae
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((TCP_IP, TCP_PORT))
        return s

    def close_connection(self):
        self.socket.close()


    def send_ints(self,robot, point):
        message = str(robot)
        for number in point:
            message += ','
            message += str(number)

        socket.send(message)
        return socket.recv(1024)

    def send_packet(self,pckt):
        msg = str(pckt)
        self.socket.send(msg)
        time.sleep(.5)
        return self.socket.recv(300)



    # angle = 180
    # radius = 100
    # x= 400
    # y = 0
    # num_steps = 30
    # sub_angle=.05*numpy.deg2rad(angle);
    # for i in range(0,628,20):
    #     time.sleep(.25)
    #
    #     # -y**2
    #     x = x+(radius*numpy.cos(i*.01))
    #     y = y+(radius*numpy.sin(i*.01))
    #     print "x, y "+str(x)+", "+str(y)+","+str(sub_angle)
    #     robot_status = send_ints(1,[x,y,350,0,180,0])
    #     print robot_status
    # #
    #
    # for i in range (-400, 400,10):
    #         time.sleep(.25)
    #         robot_status = send_ints(1,[600,i,350,0,180,0])
            # print robot_status[0]
