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
    num_packets = int(frame_size/512) + 1
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 2000)
    for i in range(num_packets):
       sock.sendto (frame[i*512:(i+1)*512],(IP,Port))
    # sock.sendall()
    # sock.sendto(frame.encode('utf-8'),(IP,Port))



UDP_IP = "192.168.10.6"
UDP_PORT = 1234

vs0 = VideoStream(1).start()
#cam1 = cv2.VideoCapture(1)
time.sleep(1)

while(True):
    ret, frame0 = vs0.read()
    # cv2.imshow("cam0",frame0)
    send(frame0, UDP_IP, 1234)

    # sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    # for i in range(40):
    #     sock.sendto (s[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))



cam0.release()
cam1.release()
cv2.destroyAllWindows()
