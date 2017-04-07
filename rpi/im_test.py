import numpy as np
import cv2



img = cv2.imread('ray.jpg',0)
input_video = cv2.VideoCapture(0)

while 1:
    input_video.read(img)
    cv2.imshow('image',img)
    cv2.waitKey(0)

    pass

cv2.destroyAllWindows()
