import numpy as np
import cv2 as cv

img1 = cv.imread('car_frame1.jpg')
img2 = cv.imread('car_frame2.jpg')
g1 = cv.cvtColor(img1, cv.COLOR_BGR2GRAY)
g2 = cv.cvtColor(img2, cv.COLOR_BGR2GRAY)

lk_params = dict(winSize=(15, 15),maxLevel=2,criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.03))

corners = cv.goodFeaturesToTrack(g1, maxCorners=100, qualityLevel=0.3, minDistance=7)
p1, st, err = cv.calcOpticalFlowPyrLK(g1, g2, corners, None, **lk_params)

g1_color = cv.cvtColor(g1, cv.COLOR_GRAY2BGR)
g2_color = cv.cvtColor(g2, cv.COLOR_GRAY2BGR)

for new, old in zip(p1[st == 1], corners[st == 1]):
    a, b = new.ravel()
    c, d = old.ravel()
    g1_color = cv.circle(g1_color, (int(c), int(d)), 5, (0, 255, 0), -1)
    g2_color = cv.circle(g2_color, (int(a), int(b)), 5, (0, 255, 0), -1)
    g2_color = cv.line(g2_color, (int(a), int(b)), (int(c), int(d)), (0, 0, 255), 2)

result = np.concatenate((g1_color, g2_color), axis=1)
cv.imshow('Motion Vectors', result)
cv.waitKey(0)
cv.destroyAllWindows()