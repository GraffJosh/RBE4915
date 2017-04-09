import numpy as np
import cv2
import socket
import time

def send(frame, IP, Port):
    pass
#    d = frame.flatten ()
#    s = d.tostring ()
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    #for i in range(20):
    #    sock.sendto (s[i*46080:(i+1)*46080],(IP,Port))
    sock.sendto(frame.encode('utf-8'),(IP,Port))



UDP_IP = "192.168.10.6"
UDP_PORT = 1234

#cam0 = cv2.VideoCapture(0)
#cam1 = cv2.VideoCapture(1)

while(True):
#    ret, frame0 = cam0.read()
#    ret, frame1 = cam1.read()
#    cv2.imshow('frame0',frame0)
#    send(frame0, UDP_IP, 1234)
    send("hello", UDP_IP, 1234)
    time.sleep(1)
    #send(frame1, UDP_IP, 1235)
    #d0 = frame0.flatten ()
    #s0 = d0.tostring ()
    #d1 = frame1.flatten()
    #s1 = d1.tostring()


    # stitched = np.concatenate((frame0,frame1),axis=1)

    # d = stitched.flatten ()
    # s = d.tostring ()

    #
    # sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    # for i in range(40):
    #     sock.sendto (s[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))


    #if cv2.waitKey(1) & 0xFF == ord('q'):
    #    break

cam0.release()
cam1.release()
cv2.destroyAllWindows()
