import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import time
def sift_image(img1, img2):    
    start = time.time()

    sift = cv.SIFT_create()
    kp1, des1 = sift.detectAndCompute(img1,None)
    kp2, des2 = sift.detectAndCompute(img2,None)
    bf = cv.BFMatcher()
    matches = bf.knnMatch(des1,des2,k=2)
    good = []
    for m,n in matches:
        if m.distance < 0.75*n.distance:
            good.append([m])
    
    img3 = cv.drawMatchesKnn(img1,kp1,img2,kp2,good,None,flags=cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    end = time.time()
    print(str(end - start) + " seconds")
    plt.imshow(img3),plt.show()

#original
og = cv.imread('bell-tower.jpeg',cv.IMREAD_GRAYSCALE)
img = cv.imread('bell-tower.jpeg',cv.IMREAD_GRAYSCALE)
sift_image(og,img)

#scale
img = cv.resize(og, (500, 500))
sift_image(og,img)

#rotate
height, width = og.shape[:2]
angle = 45
rotation_matrix = cv.getRotationMatrix2D((width / 2, height / 2), angle, 1)
rotated_image = cv.warpAffine(og, rotation_matrix, (width, height))
sift_image(og,rotated_image)

#contrast (illumination)
img = cv.convertScaleAbs(og, 1.2, 3)
sift_image(og,img)

#occlusion
img = cv.rectangle(og, (100,100), (200,200), (0,0,0), -1)
sift_image(og,img)