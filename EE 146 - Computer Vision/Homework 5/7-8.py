import cv2
import numpy as np
import math
def harris(image):

    cv2.imshow("original", image)
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)

    #do harris
    dst = cv2.cornerHarris(gray,2,3,0.01) #control parameter = 0.01, neighborhood radius = 2
    image[dst>0.01*dst.max()]=[0,0,255]
    cv2.imshow("result 1",image)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

image = cv2.imread("shapesCorner.tif")

#rotate
height, width = image.shape[:2]
angle = 30
rotation_matrix = cv2.getRotationMatrix2D((width / 2, height / 2), angle, 1)
rotated_image = cv2.warpAffine(image, rotation_matrix, (width, height))
cv2.imshow('Rotated Image', rotated_image)

#distort
distortion_matrix = np.array([[1.5, 0.2, 0],
                              [0.2, 1, 0],
                              [0, 0, 1]])
distorted_image = cv2.warpPerspective(image, distortion_matrix, (image.shape[1], image.shape[0]))

harris(distorted_image)
harris(rotated_image)
harris(image)
