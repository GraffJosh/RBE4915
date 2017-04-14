import time
import numpy
import tcp_client as client
import packet as pckt


def create_trajectory(robot, speed):
    start_packet = pckt.packet(3,robot, speed,0,0) #start message
    trajectory=[start_packet]


    angle = 180
    radius = 150
    x= 400
    y = 0
    for i in range(0,62):
        # x = (i*5)+350
        # y = (i*5)+350
        x = 450+(radius*numpy.cos(i*.1))
        y = -450+(radius*numpy.sin(i*.1))
        z = 375
        print "x, y "+str(x)+", "+str(y)+'\n'
        # x = 450
        # y = -450
        # z= 375
        trajectory.append(pckt.packet(2, robot,speed,i,pckt.point(x,y,z,0,180,0))) #pose msg


    trajectory.append(pckt.packet(1,robot, speed, 0,0)) #execute message
    return trajectory

tcp = client.connection('192.168.10.64')

trajectory = create_trajectory(1,50)
for pckt in trajectory:
    print pckt
    print tcp.send_packet(pckt) +"\n"
    pass

tcp.close_connection()
