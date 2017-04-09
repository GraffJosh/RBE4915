# import the necessary packages
from __future__ import print_function
from video_stream import VideoStream
import argparse

import cv2



print("[INFO] sampling THREADED frames from webcam...")
vs = VideoStream(0).start()
# cv2.startWindowThread()
# cv2.namedWindow("preview")
while 1:
    frame = vs.read()
    if not frame is None and len(frame) > 0:
        cv2.imshow("preview",frame)
        cv2.waitKey(1)


    pass


vs.stop()
cv2.destroyAllWindows()
