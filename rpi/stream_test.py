# import the necessary packages
from __future__ import print_function
from video_stream import VideoStream
import argparse
import numpy as np

import cv2



print("[INFO] sampling THREADED frames from webcam...")
vs0 = VideoStream(1).start()
# vs1 = VideoStream(1).start()
# cv2.startWindowThread()
# cv2.namedWindow("preview")
i=0
# Thread(target=self.update, args=())
while 1:

    ret,frame = vs0.read()

    if ret == True:
        # cv2.imshow("frame",frame)
        i=i+1
    print (str(i))
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


    pass


vs0.stop()
vs1.stop()
cv2.destroyAllWindows()
