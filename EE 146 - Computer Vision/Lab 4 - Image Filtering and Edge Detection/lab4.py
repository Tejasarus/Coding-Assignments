import cv2
from matplotlib import pyplot as plt
import numpy as np

#problem 1 - Mean, Median, Gaussian Filters
def filter(file_name):
    image = cv2.imread(file_name)
    cv2.imshow("original", image)

    #gaussian Filter
    g_filter = cv2.GaussianBlur(image, (5,5), 0, 0)
    cv2.imshow("Gaussian Filter", g_filter)

    #median filter
    med_filter = cv2.medianBlur(image,5) 
    cv2.imshow('Median Filter', med_filter) 

    #mean filter
    mean_filter = cv2.blur(image, (5,5))
    cv2.imshow('Mean Filter', mean_filter) 

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

#problem 2 - Edge Detection with Prewitt, Sobel, Laplacian of Gaussian, and Canny 
def edge_detection(file_name):
    image = cv2.imread(file_name)
    cv2.imshow("original", image)

    ##################### Threshold 1: 5 ##################
    #blur for better edge detection
    image = cv2.GaussianBlur(image, (5,5), 0, 0)

    #prewitt
    kernelx = np.array([[1,1,1],[0,0,0],[-1,-1,-1]])
    kernely = np.array([[-1,0,1],[-1,0,1],[-1,0,1]])
    prewittx = cv2.filter2D(image, -1, kernelx)
    prewitty = cv2.filter2D(image, -1, kernely)
    prewitt = prewittx + prewitty
    cv2.imshow('Prewitt 1', prewitt)

    #sobel
    sobel = cv2.Sobel(image,cv2.CV_64F,1,1,5)
    cv2.imshow('Sobel 1', sobel)

    #Laplacian of Gaussian
    laplacian = cv2.Laplacian(image, cv2.CV_16S, 5)
    laplacian = cv2.convertScaleAbs(laplacian)
    cv2.imshow('Laplacian 1', laplacian)

    #canny
    canny = cv2.Canny(image,100,200)
    cv2.imshow('Canny 1', canny)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    ############## Threshold 2: 3 #######################
    #blur for better edge detection
    image = cv2.imread(file_name)
    image = cv2.GaussianBlur(image, (3,3), 0, 0)

    #prewitt
    kernelx = np.array([[1,1,1],[0,0,0],[-1,-1,-1]])
    kernely = np.array([[-1,0,1],[-1,0,1],[-1,0,1]])
    prewittx = cv2.filter2D(image, -1, kernelx)
    prewitty = cv2.filter2D(image, -1, kernely)
    prewitt = prewittx + prewitty
    cv2.imshow('Prewitt 2', prewitt)

    #sobel
    sobel = cv2.Sobel(image,cv2.CV_64F,1,1,3)
    cv2.imshow('Sobel 2', sobel)

    #Laplacian of Gaussian
    laplacian = cv2.Laplacian(image, cv2.CV_16S, 3)
    laplacian = cv2.convertScaleAbs(laplacian)
    cv2.imshow('Laplacian 2', laplacian)

    #canny
    canny = cv2.Canny(image,100,200)
    cv2.imshow('Canny 2', canny)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

#problem 3 - Image sharpening by Laplacian
def sharpen(file_name, weight):
    image = cv2.imread(file_name)
    cv2.imshow("original", image)
    
    #gaussian + laplacian
    image = cv2.GaussianBlur(image, (5, 5), 0)
    lap = cv2.Laplacian(image, cv2.CV_64F)

    #subtract weight from blurred
    sharpened_image = image - weight * lap

    sharpened_image = np.clip(sharpened_image, 0, 255)
    sharpened_image = np.uint8(sharpened_image)
    cv2.imshow("sharpened", sharpened_image)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

filter(("cameramanGN.tif"))
filter(("cameramanSPN.tif"))

edge_detection("cameramanBlur.tif")

sharpen("slightly_blurred.png", 5)
sharpen("slightly_blurred.png", 2)