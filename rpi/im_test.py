import numpy as np
import cv2



img = cv2.imread('ray.jpg',0)
input_video = cv2.VideoCapture(0,0)

while 1:
    ret,frame = input_video.read()
    cv2.imshow('frame',frame)

    k = cv2.waitKey(1) & 0xff
    if k == 27:
        break

    pass

cv2.destroyAllWindows()
input_video.release()
