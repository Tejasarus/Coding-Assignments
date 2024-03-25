import numpy as np
import cv2 as cv

#Problem 2: K Means Segmentation
img = cv.imread('green_peppers.png')
Z = img.reshape((-1,3))
Z = np.float32(Z)
cv.imshow('Original', img)

#K means
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 10, 1.0) 
K = 2
ret,label,center=cv.kmeans(Z,K,None,criteria,10,cv.KMEANS_RANDOM_CENTERS)

#show image
center = np.uint8(center)
res = center[label.flatten()]
res2 = res.reshape((img.shape))
cv.imshow('Segmented Image',res2)
cv.waitKey(0)
cv.destroyAllWindows()