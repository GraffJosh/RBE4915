import time
import numpy
import tcp_client as client
import packet as pckt


def create_circle(robot, speed,radius,centerx,centery):
    start_packet = pckt.packet(3,robot, speed,0,0) #3 is start message
    trajectory=[start_packet]


    angle = 180
    radius =150
    # x=
    # y = centery
    for i in range(0,62):
        # x = (i*5)+350
        # y = (i*5)+350
        x = centerx+(radius*numpy.cos(i*.1))
        y = centery+(radius*numpy.sin(i*.1))
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
    trajectory.append()
    return trajectory

tcp = client.connection('192.168.10.64')

# trajectory = create_circle(1,50,30,400,-400)
trajectory = [pckt.packet(4,1, 100,0,pckt.point(400,400,375,0,180,0))]
trajectory.append(pckt.packet(4,1, 100,0,pckt.point(400,-400,375,0,180,0)))
i=0
for pckt in trajectory:
    print pckt
    print str(tcp.send_packet(pckt))+" " +str(i)+"\n"
    i+=1
    pass

tcp.close_connection()
