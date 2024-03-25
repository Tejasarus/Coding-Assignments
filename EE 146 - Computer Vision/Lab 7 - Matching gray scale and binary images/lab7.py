import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
from PIL import Image
import time
from numpy import asarray

def matching(img, template):
    cv.imshow("og",img)
    cv.imshow("template",template)
    img2 = img.copy()
    w, h = template.shape[::-1]

    # All the 6 methods for comparison in a list
    methods = ['cv.TM_CCOEFF', 'cv.TM_CCOEFF_NORMED']
    for meth in methods:
        img = img2.copy()
        method = eval(meth)
        # Apply template Matching
        res = cv.matchTemplate(img,template,method)
        min_val, max_val, min_loc, max_loc = cv.minMaxLoc(res)
        # If the method is TM_SQDIFF or TM_SQDIFF_NORMED, take minimum
        if method in [cv.TM_SQDIFF, cv.TM_SQDIFF_NORMED]:
            top_left = min_loc
        else:
            top_left = max_loc
        bottom_right = (top_left[0] + w, top_left[1] + h)
        cv.rectangle(img,top_left, bottom_right, (255,255,255), 2)
        plt.subplot(121),plt.imshow(res,cmap = 'gray')
        plt.title('Matching Result'), plt.xticks([]), plt.yticks([])
        plt.subplot(122),plt.imshow(img,cmap = 'gray')
        plt.title('Detected Point'), plt.xticks([]), plt.yticks([])
        plt.suptitle(meth)
        plt.show()

    #destroy the windows at key press
    cv.waitKey(0)
    cv.destroyAllWindows()

def matching_multiple(img,template):
    start = time.time()
    cv.imshow("t",template)
    w, h = template.shape[::-1]
    res = cv.matchTemplate(img,template,cv.TM_CCOEFF_NORMED)
    threshold = 0.8
    loc = np.where( res >= threshold)
    for pt in zip(*loc[::-1]):
        cv.rectangle(img, pt, (pt[0] + w, pt[1] + h), (255,255,255), 2)
    cv.imwrite('res.png',img)
    cv.imshow("im",img)
    end = time.time()
    print(str(end - start) + " seconds")
    #destroy the windows at key press
    cv.waitKey(0)
    cv.destroyAllWindows()

def dist_transform(img):
    start = time.time()
    ret, thresh = cv.threshold(img, 127, 255, cv.THRESH_BINARY) 
    dist = cv.distanceTransform(thresh, cv.DIST_L2, 5) 
    dist_output = cv.normalize(dist, None, 0, 1.0, cv.NORM_MINMAX) 
    end = time.time()
    print(str(end - start) + " seconds")
    
    cv.imwrite('distance transform.png',dist_output)
    cv.imshow('Distance Transform', dist_output)

    cv.waitKey(0)
    cv.destroyAllWindows()

#Problem 1
#part a
img = cv.imread("cameraman.tif", cv.IMREAD_GRAYSCALE)
template = img[60:85,130:170]
print("Part a")
#matching(img,template)

#part b - change intensity of template
img2 = img
brightness = 10 
contrast = 2.3  
img2 = cv.addWeighted(img, contrast, np.zeros(img.shape, img.dtype), 0, brightness)
template = img2[60:85,130:170]
print("Part b")
#matching(img,template)

#part c - change intensity of image, not template
template = img[60:85,130:170]
print("Part c")
#matching(img2,template)

#part d - change intensity of both image and template
template = img2[60:85,130:170]
print("Part d")
#matching(img2,template)

#part e - rotate og template by 90 degrees
print("Part e")
template = img[60:85,130:170]
#rotate
height, width = template.shape[:2]
angle = 90
rotation_matrix = cv.getRotationMatrix2D((width / 2, height / 2), angle, 1)
rotated_template = cv.warpAffine(template, rotation_matrix, (width, height))
#matching(img,rotated_template)

#Problem 2
image = np.loadtxt("lab7 text.txt", dtype=int) 
template = np.loadtxt("lab7 template.txt", dtype=int) 

im = Image.fromarray((image * 255).astype(np.uint8))
#im.show()
im.save("img.png")

im_temp = Image.fromarray((template * 255).astype(np.uint8))
#im_temp.show()
im_temp.save("template.png")

#part a - locate all instances
print("Part a")
img = cv.imread("img.png",cv.IMREAD_GRAYSCALE)
template = cv.imread("template.png",cv.IMREAD_GRAYSCALE)
#matching_multiple(img,template)

#part b - distance transform
print("Part b")
dist_transform(img)

#part c - instances w/ distance transform image
img = cv.imread("distance transform.png", cv.IMREAD_GRAYSCALE)
template = cv.imread("distance transform template.png", cv.IMREAD_GRAYSCALE)
matching_multiple(img,template)