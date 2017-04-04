import time
import numpy
import tcp_client as client
import packet as pckt


def create_trajectory(robot, speed):
    start_packet = pckt.packet(3,robot, speed,0)
    trajectory=[start_packet]
    for i in range(0,10):
        x = (i*5)+250
        y = (i*5)+250
    #   x = x+(radius*numpy.cos(i*.01))
    #   y = y+(radius*numpy.sin(i*.01))
        z = 375
        trajectory.append(pckt.packet(2, robot,speed,pckt.point(x,y,z,0,180,0)))

    return trajectory

tcp = client.connection('192.168.10.64')

trajectory = create_trajectory(1,50)
for pckt in trajectory:
    tcp.send_packet(pckt)
    print str(pckt)+"\n"

tcp.close_connection(socket)
