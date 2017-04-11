import numpy as np
import cv2
import socket
import sys
import time
from video_stream import VideoStream


def send(frame, IP, Port):
    pass
#    d = frame.flatten ()
#    s = d.tostring ()
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    frame_size = sys.getsizeof(frame0)

    d0 = frame0.flatten ()
    s0 = d0.tostring ()

    frame_size = len(d0)
    packet_size = 10000#bits
    num_packets = int(frame_size/packet_size) + 1
    shibboleth = "01234567"
    sock.sendto (shibboleth.encode('utf-8'),(IP,Port))
    for i in range(num_packets):
        sock.sendto (d0[i*packet_size:(i+1)*packet_size],(IP,Port))

    sock.sendto (("").encode('utf-8'),(IP,Port))
    # print ("frame")
    # sock.sendall()
    # sock.sendto(frame.encode('utf-8'),(IP,Port))



UDP_IP = "192.168.10.6"
UDP_PORT = 1234

vs0 = VideoStream(0).start()
#cam1 = cv2.VideoCapture(1)
# time.sleep(1)
i = 0
while(True):
    ret, frame0 = vs0.read()
    # cv2.imshow("cam0",frame0)
    if(ret):
        send(frame0, UDP_IP, 1234)
        print(i)
        i+=1
    # sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    # for i in range(40):
    #     sock.sendto (s[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))



vs0.stop()
cv2.destroyAllWindows()
