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



    merged_frame = Mat(Size(frame0.cols*2,frame0.rows), CV_8UC3)
    roi = Mat(merged_frame, Rect(0, 0, frame0.cols, frame0.rows));
    frame0.copyTo(roi);
    roi = Mat(merged_frame, Rect(frame0.cols, frame0.rows,frame0.cols*2,frame0.rows));
    frame1.copyTo(roi);

    d1 = frame1.flatten()
    s1 = d1.tostring()


    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    for i in range(20):
        sock.sendto (s0[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))


    # sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    # for i in range(20):
    #     sock.sendto (s1[i*46080:(i+1)*46080],(UDP_IP, UDP_PORT))

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam0.release()
cam1.release()
cv2.destroyAllWindows()
