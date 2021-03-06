##BRCarroll OpenCV Kinematics Lab   Feb 18, 2015
##adapted from OpenCV.org tutorials for video capture & feature detection
#http://docs.opencv.org/trunk/doc/py_tutorials/py_feature2d/py_matcher/py_matcher.html
#http://docs.opencv.org/trunk/doc/py_tutorials/py_calib3d/py_calibration/py_calibration.html#calibration
##<insert links…>



import numpy as np
import cv2
from matplotlib import pyplot as plt

MIN_MATCH_COUNT = 10

##open video capture
cap=cv2.VideoCapture()   #create VideoCapture class

cap.set(cv2.CV_CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CV_CAP_PROP_FRAME_HEIGHT, 1080)
#might need to transform to 8-bit greyscale for analysis

#for( i < numFrames, i++ #kinda thing  sets up number of frames to capture
ret, img1 = cap.read()      # queryImage
img2 = cv2.imread('reference.jpg',0) # trainImage

# Initiate SIFT detector
sift = cv2.SIFT()

# find the keypoints and descriptors with SIFT - Scale Invariant Feature Transform
kp1, des1 = sift.detectAndCompute(img1,None)
kp2, des2 = sift.detectAndCompute(img2,None)

#Fast Library for Approximate Nearest Neighbors. 
FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks = 50)

flann = cv2.FlannBasedMatcher(index_params, search_params)

matches = flann.knnMatch(des1,des2,k=2)

# store all the good matches as per Lowe's ratio test.
good = []
for m,n in matches:
    if m.distance < 0.7*n.distance:
        good.append(m)

if len(good)>MIN_MATCH_COUNT:
    src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
    dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)

    M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
    matchesMask = mask.ravel().tolist()

    h,w = img1.shape
    pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
    dst = cv2.perspectiveTransform(pts,M)

    img1 = cv2.polylines(img1,[np.int32(dst)],True,255,3, cv2.LINE_AA)

else:
    print "Not enough matches are found - %d/%d" % (len(good),MIN_MATCH_COUNT)
    matchesMask = None

plt.imshow(img1, 'gray'),plt.show()

#store img1 & perspectiveTransform & points into time frams of appropriate data type
#)  end the numFrame for loop()

#real time clock values??

cap.release()
##visualization code here using matplotlib
##initialize HD capture & analysis based on PRU register value connected to physical switch or web
##output HD capture video & analysis via matplotlib fanciness
