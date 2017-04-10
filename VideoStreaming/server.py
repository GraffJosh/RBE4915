import socket
import numpy
import time
import cv2

UDP_IP = "130.215.75.131"
UDP_PORT = 1234

sock0 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock0.bind ((UDP_IP, 1234))
sock1 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock1.bind ((UDP_IP, 1235))
s=""

while True:

    data0, addr = sock0.recvfrom(46080)
    data1, addr = sock1.recvfrom(46080)

    s0 += data0
    s1 += data1

    if len(s0) == (46080*20):
        frame0 = numpy.fromstring (s0,dtype=numpy.uint8)
        frame0 = frame0.reshape (480,680,3)
        cv2.imshow('frame',frame0)
        s0=""
    # if len(s1) == (46080*20):
    #     frame1 = numpy.fromstring (s1,dtype=numpy.uint8)
    #     frame1 = frame1.reshape (480,680,3)
    #     cv2.imshow('frame',frame1)
    #     s1=""

    if cv2.waitKey(1) & 0xFF == ord ('q'):
        break
