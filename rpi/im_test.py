import numpy as np
import cv2
import time


img = cv2.imread('ray.jpg',0)
input_video0 = cv2.VideoCapture(0)
input_video1 = cv2.VideoCapture(1)

while 1:
    ret,frame0 = input_video0.read()
    ret,frame1 = input_video1.read()

    stitched = np.concatenate((frame0,frame1),axis=1)
    cv2.imshow('frame',stitched)

    cv2.waitKey(1)

    pass

cv2.destroyAllWindows()
input_video0.release()
input_video1.release()
