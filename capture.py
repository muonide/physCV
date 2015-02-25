/http://stackoverflow.com/questions/12054907/opencv-videowriter-wont-write-anything-although-cvwritetoavi-does


import numpy as np
imprt cv2

cap = cv2.VideoCapture(0)

# Defin the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'MJPG')
out = cv2.VideoWriter('output.avi',fourcc, 10.0, (1920,1080),1)

while(cap.isOpened()):
  ret, frame = cap.read()
  
  #insert algorithms applied to frame here
  
  
  out.write(frame)
  
  cv2.imshow('frame',frame)
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break
  else:
    break
    
#release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()


