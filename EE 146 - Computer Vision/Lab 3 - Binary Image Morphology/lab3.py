import cv2
import numpy as np
from matplotlib import pyplot as plt
import argparse
import skimage as ski
import math

def structuring_elements(file_name):
    image = cv2.imread(file_name)

    str_e_1 = np.ones((5,5), np.uint8) 
    img_erosion_1 = cv2.erode(image, str_e_1, iterations=1) 
    img_dilation_1 = cv2.dilate(image, str_e_1, iterations=1)
    img_opening_1 = cv2.morphologyEx(image, cv2.MORPH_OPEN, str_e_1)
    img_closing_1 = cv2.morphologyEx(image, cv2.MORPH_CLOSE, str_e_1)

    cv2.imshow(file_name, image)
    cv2.imshow(file_name + " erosion 1", img_erosion_1)
    cv2.imshow(file_name + " dilation 1", img_dilation_1)
    cv2.imshow(file_name + " opening 1", img_opening_1)
    cv2.imshow(file_name + " closing 1", img_closing_1)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    str_e_2 = np.ones((10,10), np.uint8) 
    img_erosion_2 = cv2.erode(image, str_e_2, iterations=1) 
    img_dilation_2 = cv2.dilate(image, str_e_2, iterations=1)
    img_opening_2 = cv2.morphologyEx(image, cv2.MORPH_OPEN, str_e_2)
    img_closing_2 = cv2.morphologyEx(image, cv2.MORPH_CLOSE, str_e_2)

    cv2.imshow(file_name, image)
    cv2.imshow(file_name + " erosion 2", img_erosion_2)
    cv2.imshow(file_name + " dilation 2", img_dilation_2)
    cv2.imshow(file_name + " opening 2", img_opening_2)
    cv2.imshow(file_name + " closing 2", img_closing_2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def one_value(N):
    num = N[0]
    for i in N:
        if i > 1:
            if num == 0: num = i
        elif i > 1 and num != i:
            return False, i
    return True,num

def SequentialLabeling(I):
    #step 1: assign inital labels
    label = 2
    C = []
    for v in range(len(I)):
        for u in range(len(I[v])):
            if I[v][u] == 1:
                N = []
                #get neighbors
                directions = [(0, -1),(-1,-1),(-1,0),(-1,1)]
                for dr, dc in directions:
                    if 0 <= v+dr < len(I) and 0 <= u+dc < len(I[v]):
                        N.append(I[v+dr][u+dc])
                    else:
                        N.append(0)
                
                one_val, val = one_value(N)
                #if all neighbors are 0
                if all(i == 0 for i in N):
                    I[v][u] = label
                    label += 1
                #if exactly one value is in N
                elif one_value(N):
                    I[v][u] = val
                #if more than one value is in N
                elif not one_value(N):
                    I[v][u] = val
                    for Nl in N:
                        if Nl != val and Nl > 1:
                            C.append((Nk,Nl))       
    #print(I)
    #print(C)

    #step 2: resolve label conditions
    R = [{i} for i in range(2,label)]

    for A,B in C:
        a = next(index for index, i in enumerate(R) if A in i)
        b = next(index for index, i in enumerate(R) if B in i)
        if a != b:
            R[a] |= R[b]
            R[b] = set()

    #step 3: relabel the image:
    for u in range(len(I)):
        for v in range(len(I[v])):
            if I[u][v] > 1:
                j = next(index for index, i in enumerate(R) if I[u][v] in i)
                k = min(R[j])
                I[u][v] = k

    #print it in a way that I can see it properly
    for i in range(len(I)):
        print(I[i])            
    print() #empty line for my sanity =)

structuring_elements("binary.png")
structuring_elements("binary2.png")

Im1 = [
    [0, 0, 1, 0, 0, 1, 1, 1],
    [0, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 0, 0, 1, 1],
    [1, 1, 1, 0, 0, 0, 0, 0],
    [1, 1, 1, 0, 0, 1, 1, 1],
    [1, 1, 1, 0, 0, 1, 1, 1]
]

Im2 = [
    [1, 1, 0, 1, 1, 1, 0, 1],
    [1, 0, 1, 0, 1, 0, 1, 0],
    [1, 1, 1, 1, 0, 0, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 0, 1, 0, 1],
    [0, 0, 0, 1, 0, 1, 0, 1],
    [1, 1, 0, 1, 0, 0, 0, 1],
    [1, 1, 0, 1, 0, 1, 1, 1]
]

print("Sequential Labeling Im1:")
SequentialLabeling(Im1)

print("Sequential Labeling Im2:")
SequentialLabeling(Im2)

def components(file_name):
    image = cv2.imread(file_name)
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(gray,150,255,0)
    contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnt = contours[0]
    M = cv2.moments(cnt)
    area = cv2.contourArea(cnt)
    perimeter = cv2.arcLength(cnt, True)
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])
    circularity = 4*math.pi*(area/perimeter*perimeter)
    print("Area: ", area)
    print("Centroid: ",cx,cy)
    print("Perimeter: ", perimeter)
    print("Circulariy: ",circularity)

components("binary.png")