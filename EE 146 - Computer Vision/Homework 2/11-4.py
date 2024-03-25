import cv2
import numpy as np

image = cv2.imread("last_supper.png")
gray_image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

(b, g, r) = cv2.split(image)
ret2, thresh2 = cv2.threshold(b, 150, 255, cv2.THRESH_BINARY)
ret3, thresh3 = cv2.threshold(g, 150, 255, cv2.THRESH_BINARY)
ret4, thresh4 = cv2.threshold(r, 150, 255, cv2.THRESH_BINARY)
bgr_thresh = cv2.merge((thresh2, thresh3, thresh4))

ret,binary = cv2.threshold(gray_image,70,255,0)
cv2.imshow('grayscale', binary)
cv2.imshow("merged",bgr_thresh)
cv2.imshow("original",image)
cv2.waitKey(0)
cv2.destroyAllWindows()