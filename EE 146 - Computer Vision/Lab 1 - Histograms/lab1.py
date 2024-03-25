import cv2
import numpy as np
from matplotlib import pyplot as plt
import argparse
### problem 1: ###
image = cv2.imread('last_supper.jpeg')

#display rows, columns, bytes/pixel
rows, columns, channels = image.shape
bytes_per_pixel = image.dtype.itemsize * channels
print("rows:", rows, "columns:", columns, "bytes per pixel:", bytes_per_pixel)

#color image, greyscale image, binary image
cv2.imshow('Color', image) 

gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) 
cv2.imshow('Grayscale', gray_image) 

ret,binary = cv2.threshold(gray_image,70,255,0)
cv2.imshow('Binary', binary)

#destroy the windows at key press
cv2.waitKey(0)
cv2.destroyAllWindows()

### problem 2: ###
#part a
#histogram of black and white high contrast and low contrast image

high_contrast = cv2.convertScaleAbs(image, 10, 2)
low_contrast = cv2.convertScaleAbs(image, 0.5, 1)
gray_high_contrast = cv2.cvtColor(high_contrast, cv2.COLOR_BGR2GRAY)
gray_low_contrast = cv2.cvtColor(low_contrast, cv2.COLOR_BGR2GRAY)  
cv2.imshow("high contrast",high_contrast)
cv2.imshow("low contrast", low_contrast)
cv2.imshow("grey high contrast",gray_high_contrast)
cv2.imshow("grey low contrast", gray_low_contrast)

plt.subplot(121)
histogram_high_contrast = cv2.calcHist([gray_high_contrast], [0], None, [256], [0, 256])
plt.plot(histogram_high_contrast, color='k')
plt.xlabel("high contrast histogram")


plt.subplot(122)
histogram_low_contrast = cv2.calcHist([gray_low_contrast], [0], None, [256], [0, 256])
plt.plot(histogram_low_contrast, color='k')
plt.xlabel("low contrast histogram")

plt.suptitle("High and Low contrast histograms")
plt.show()

#destroy the windows at key press
cv2.waitKey(0)
cv2.destroyAllWindows()

#part b
#histogram of binary image

cv2.imshow('Binary', binary)

histogram_binary = cv2.calcHist([binary], [0], None, [256], [0, 256])
plt.plot(histogram_binary, color='k')
plt.xlabel("binary histogram")
plt.show()

#destroy the windows at key press
cv2.waitKey(0)
cv2.destroyAllWindows()

#part c
#histogram of color image

cv2.imshow('Color', image)
#part i

#individual rgb color histograms
plt.subplot(131)
histogram_r = cv2.calcHist([image[0]], [0], None, [256], [0, 256])
plt.plot(histogram_r, color='r')
plt.xlabel("R histogram")

plt.subplot(132)
histogram_g = cv2.calcHist([image[1]], [0], None, [256], [0, 256])
plt.plot(histogram_g, color='g')
plt.xlabel("G histogram")

plt.subplot(133)
histogram_b = cv2.calcHist([image[2]], [0], None, [256], [0, 256])
plt.plot(histogram_b, color='b')
plt.xlabel("B histogram")

plt.suptitle("Separate RGB histograms")
plt.show()

#part ii
#combined rgb histogram
histogram_r = cv2.calcHist([image[0]], [0], None, [256], [0, 256])
histogram_g = cv2.calcHist([image[1]], [0], None, [256], [0, 256])
histogram_b = cv2.calcHist([image[2]], [0], None, [256], [0, 256])

plt.plot(histogram_r, color='red', label='Red')
plt.plot(histogram_g, color='green', label='Green')
plt.plot(histogram_b, color='blue', label='Blue')

plt.title('Color Image Histogram')
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.legend()
plt.show()

#destroy the windows at key press
cv2.waitKey(0)
cv2.destroyAllWindows()

#part iii
#8 bit histogram color image (in black and white)
#obtain rgb channels
blue_channel, green_channel, red_channel = cv2.split(image)

#split the rgb channels
new_red_channel = (red_channel >> 5) << 5 
new_green_channel = (green_channel >> 5) << 5  
new_blue_channel = (blue_channel >> 6) << 6


#merge into new image
eight_bit_image = cv2.merge([new_blue_channel, new_green_channel, new_red_channel])
gray_eight_bit_image = cv2.cvtColor(eight_bit_image, cv2.COLOR_BGR2GRAY)
cv2.imshow("8-Bit Image", gray_eight_bit_image)
#get histogram of 8 bit image
eight_bit_histogram = cv2.calcHist([gray_eight_bit_image], [0], None, [256], [0, 256])
plt.plot(histogram_r, color='k')
plt.xlabel("8-bit histogram")
plt.show()

#destroy the windows at key press
cv2.waitKey(0)
cv2.destroyAllWindows()

#part d
#cumulative histogram of an image
plt.subplot(121)
cumulative_histogram_before = cv2.calcHist([gray_image], [0], None, [256], [0, 256])
plt.plot(cumulative_histogram_before, color='k')
plt.xlabel("histogram before")

plt.subplot(122)
cumulative_histogram_after = np.cumsum(cumulative_histogram_before)
plt.plot(cumulative_histogram_after, color='k')
plt.xlabel("cumulative histogram")

plt.suptitle("Cumulative Histogram")
plt.show()

#part e
#get mean, variance, and median from image
mean = np.mean(image)
variance = np.var(image)
median = np.median(image)
print("Mean:",mean,"Variance:",variance,"Median:",median)