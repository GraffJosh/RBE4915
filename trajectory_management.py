import time
import numpy
import tcp_client as client
import packet as pckt


def create_circle(robot, speed):
    start_packet = pckt.packet(3,robot, speed,0,0) #3 is start message
    trajectory=[start_packet]


    angle = 180
    radius =150
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
        trajectory.append(pckt.packet(2, robot,speed,i,pckt.point(x,y,z,0,180,0))) #2 is pose msg


    trajectory.append(pckt.packet(1,robot, speed, 0,0)) #1 is execute message
    return trajectory


def go_to_point(speed,x,y,z):
    start_packet = pckt.packet(4,1, speed,0,pckt.point(x,y,z,0,180,0)) #4 means point message
    trajectory=[start_packet]
    return trajectory

tcp = client.connection('192.168.10.64')

#trajectory = create_circle(1,50)
trajectory = go_to_point(100,400,00,300)
i=0
for pckt in trajectory:
    print pckt
    print str(tcp.send_packet(pckt))+" " +str(i)+"\n"
    i+=1
    pass

tcp.close_connection()
