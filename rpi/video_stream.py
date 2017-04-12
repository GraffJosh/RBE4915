# import the necessary packages
from threading import Thread
import cv2
import time

class VideoStream:
	def __init__(self, src=0):
		# initialize the video camera stream and read the first frame
		# from the stream
		self.instance = src
		self.stream = cv2.VideoCapture(src)
		self.stream.set(3,640)
		self.stream.set(4,480)
		self.stream.set(4,10)
		self.stream.set(11,180)
		(self.grabbed, self.frame) = self.stream.read()

		# initialize the variable used to indicate if the thread should
		# be stopped
		self.stopped = False


	def start(self):
		# start the thread to read frames from the video stream
		Thread(target=self.update, args=()).start()
		return self

	def update(self):
		# keep looping infinitely until the thread is stopped
		while True:
			# if the thread indicator variable is set, stop the thread
			if self.stopped:
				return

			# otherwise, read the next frame from the stream
			(self.grabbed, self.frame) = self.stream.read()
			time.sleep(.01)

	def read(self):
		# return the frame most recently read
		return_grab = self.grabbed
		self.grabbed = False
		return return_grab,self.frame

	def stop(self):
		# indicate that the thread should be stopped
		self.stopped = True

	def show(self):
		i = 0
		while 1:
			if self.grabbed:
				print(str(self.instance)+" "+str(i))
				cv2.imshow("frame: "+self.instance,self.frame)
			if cv2.waitKey(1) & 0xFF == ord('q'):
				break
			i = i+1
		self.stop()
