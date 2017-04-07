import numpy as np
import cv2
import socket

def send(frame, IP, Port):



UDP_IP = "130.215.75.131"
UDP_PORT = 1234

cam0 = cv2.VideoCapture(0)
cam1 = cv2.VideoCapture(1)
stitcher = cv2.createStitcher(False)

while(True):
    ret, frame0 = cam0.read()
    ret, frame1 = cam1.read()

    #d0 = frame0.flatten ()
    #s0 = d0.tostring ()
    #d1 = frame1.flatten()
    #s1 = d1.tostring()


    stitched = np.concatenate((frame0,frame1),axis=1)

    d = stitched.flatten ()
    s = d.tostring ()
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
   

    for i in range(40):
        sock.sendto (s[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam0.release()
cam1.release()
cv2.destroyAllWindows()
