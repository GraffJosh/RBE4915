import socket
import numpy
import time
import cv2

UDP_IP = "130.215.75.131"
UDP_PORT = 1234

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind ((UDP_IP, UDP_PORT))

s=""

while True:

    data, addr = sock.recvfrom(46080)

    s += data

    if len(s) == (46080*40):

        frame = numpy.fromstring (s,dtype=numpy.uint8)
        frame = frame.reshape (480,1280,3)

        cv2.imshow('frame',frame)

        s=""

    if cv2.waitKey(1) & 0xFF == ord ('q'):
        break
