from skimage.metrics import structural_similarity
import cv2
import numpy as np

im1 = cv2.imread('car_frame1.jpg',cv2.IMREAD_GRAYSCALE)
im2 = cv2.imread('car_frame2.jpg',cv2.IMREAD_GRAYSCALE)

(score, diff) = structural_similarity(im1, im2, full=True)

diff = (diff * 255).astype("uint8")
diff_box = cv2.merge([diff, diff, diff])

#thresh of 5
thresh = cv2.threshold(diff, 5, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
contours = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
contours = contours[0] if len(contours) == 2 else contours[1]

mask = np.zeros(im1.shape, dtype='uint8')
filled_im2 = im2.copy()

#min area of 10
for c in contours:
    area = cv2.contourArea(c)
    if area > 10:
        x,y,w,h = cv2.boundingRect(c)        
        cv2.drawContours(mask, [c], 0, (255,255,255), -1)
        backtorgb = cv2.cvtColor(mask,cv2.COLOR_GRAY2RGB)
        cv2.rectangle(backtorgb, (x, y), (x + w, y + h), (0,255,0), 2)

cv2.imshow('img', backtorgb)
cv2.waitKey()