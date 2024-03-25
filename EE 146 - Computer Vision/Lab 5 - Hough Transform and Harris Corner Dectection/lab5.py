import cv2
import numpy as np
import math

#Problem 1: Hough Transformation Algorithm
def huff(file_name):
    #obtain/show image
    image = cv2.imread(file_name, cv2.COLOR_BGR2GRAY)
    cv2.imshow("original", image)

    #get lines
    filter = cv2.Canny(image, 50, 200, None, 3)
    linesP = cv2.HoughLinesP(filter, 1, np.pi / 180, 50, None, 50, 10)

    #draw lines
    min = 999
    max = 0
    if linesP is not None:
        for i in range(0, len(linesP)):
            l = linesP[i][0]
            distance = math.sqrt((l[2] - l[0])**2 + (l[3]-l[1])**2)
            
            #get max and min
            if distance > max:
                max = distance
                l_min = l
            if distance < min:
                min = distance
                l_max = l
            
            cv2.line(image, (l[0], l[1]), (l[2], l[3]), (255,0,0), 3, cv2.LINE_AA) #blue = everything else
    
    #show max and min lines
    cv2.line(image, (l_min[0], l_min[1]), (l_min[2], l_min[3]), (66, 245, 72), 3, cv2.LINE_AA) #green = min
    cv2.line(image, (l_max[0], l_max[1]), (l_max[2], l_max[3]), (0,0,255), 3, cv2.LINE_AA) #red = max 
    print("min distance: ", min, " max distance: ", max)
    cv2.imshow("result", image)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

#Problem 2: Harris Corner Detection
def harris(file_name):
    #get/show image
    image = cv2.imread(file_name)
    cv2.imshow("original", image)
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)

    #do harris
    dst = cv2.cornerHarris(gray,2,3,0.01) #control parameter = 0.01, neighborhood radius = 2
    image[dst>0.01*dst.max()]=[0,0,255]
    cv2.imshow("result 1",image)

    dst = cv2.cornerHarris(gray,2,31,0.001) #control parameter = 1, neighborhood radius = 2
    image[dst>0.01*dst.max()]=[0,0,255]
    cv2.imshow("result 2",image)

    dst = cv2.cornerHarris(gray,6,3,0.06) #control parameter = 0.06, neighborhood radius = 6
    image[dst>0.01*dst.max()]=[0,0,255]
    cv2.imshow("result 3",image)

    dst = cv2.cornerHarris(gray,10,3,0.06) #control parameter = 0.06, neighborhood radius = 10
    image[dst>0.01*dst.max()]=[0,0,255]
    cv2.imshow("result 4",image)

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()


#Problem 1
#few lines
huff("lines_img.png")
huff("gamecube.jpeg")
#many lines
huff("architecture.jpeg")
huff("minecraft.png")

#Problem 2
harris("shapesCorner.tif")