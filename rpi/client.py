import cv2
import numpy as np
import socket
import sys
import pickle
import struct ### new code

cap=cv2.VideoCapture(0)
clientsocket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
clientsocket.connect(('130.215.75.131',1234))
while True:
    ret,frame=cap.read()
    data = pickle.dumps(frame) ### new code
    cv2.imshow('frame',frame)
    clientsocket.sendall(struct.pack("H", len(data))+data) ### new code
