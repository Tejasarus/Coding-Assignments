import cv2
import numpy as np
from math import copysign, log10

image = cv2.imread("last_supper.png",cv2.IMREAD_GRAYSCALE)
_,image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)

moments = cv2.moments(image) 
huMoments = cv2.HuMoments(moments)

for i in range(7):
   huMoments[i] = -1* copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]))

print("Hu Moments")
print(huMoments)

scaled = cv2.resize(image, (0, 0), fx=0.5, fy=0.5)  
rotated = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)

scaled_moments = cv2.moments(scaled)
rotated_moments = cv2.moments(rotated)

scaled_huMoments = cv2.HuMoments(scaled_moments)
rotated_huMoments = cv2.HuMoments(rotated_moments)

for i in range(7):
    scaled_huMoments[i] = -1 * copysign(1.0, scaled_huMoments[i]) * log10(abs(scaled_huMoments[i]))
    rotated_huMoments[i] = -1 * copysign(1.0, rotated_huMoments[i]) * log10(abs(rotated_huMoments[i]))

print("Scaled Hu Moments:")
print(scaled_huMoments)

print("Rotated Hu Moments:")
print(rotated_huMoments)