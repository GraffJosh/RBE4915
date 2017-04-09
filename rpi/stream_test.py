# import the necessary packages
from __future__ import print_function
from video_stream import VideoStream
from threading import Thread
import argparse
import numpy as np

import cv2



print("[INFO] sampling THREADED frames from webcam...")
vs0 = VideoStream(0).start()
# vs1 = VideoStream(1).start()
# cv2.startWindowThread()
# cv2.namedWindow("preview")
i=0
Thread(target=vs0.show(), args=())
# Thread(target=self.update, args=())
while 1:

    time.sleep(1)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break



    pass


vs0.stop()
vs1.stop()
cv2.destroyAllWindows()
