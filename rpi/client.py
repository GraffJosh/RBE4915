import numpy as np
import cv2
import socket

UDP_IP = "130.215.75.131"
UDP_PORT = 1234

cam0 = cv2.VideoCapture(0)
cam1 = cv2.VideoCapture(1)

while(True):
    ret, frame0 = cam0.read()
    ret, frame1 = cam1.read()

    d0 = frame0.flatten ()
    s0 = d0.tostring ()

    d1 = frame1.flatten()
    s1 = d1.tostring()

    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    for i in range(20):
        sock.sendto (s0[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))


    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    for i in range(20):
        sock.sendto (s1[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam0.release()
cam1.release()
cv2.destroyAllWindows()
