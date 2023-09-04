import cv2
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import time

cap = cv2.VideoCapture(0)
howmanyframes = 50  # How many frames you want to analyze
Netplots = []
while True:
    ret, photo = cap.read()
    photo = cv2.flip(photo, 1)
    cv2.imshow('photo', photo)
    cropu1 = photo[232:238, :]       # select part of photo
    cv2.imshow("cropu1", cropu1)     # It will show cropu1 part in a window
    if cv2.waitKey(1) & 0xFF == ord('a'):
        howmanyframes -= 1
        #Your already done analysis
        shape = cropu1.shape
        dist = []
        for i in range(shape[1]):
            I = np.mean(cropu1[:, i][:, 0]) + np.mean(cropu1[:, i]
                                                      [:, 1]) + np.mean(cropu1[:, i][:, 2])
            dist.append(I)
        plt.plot(dist)
        # Store the instantaneous thing in Netplots
        Netplots.append(np.array(dist))
        plt.show()
        pd.DataFrame(Netplots).to_csv(
            r"D:\PhD\optical table\Device\Transmission\t_data_all_nir_smallLED_new_1.csv", header=None)
    if howmanyframes == 0:
        break
cap.release()
cv2.destroyAllWindows()

Netplots = np.array(Netplots)
# <- This will take the average of all the captured frames
Avgplot = np.mean(Netplots, axis=0)
plt.plot(Avgplot)
pd.DataFrame(Avgplot).to_csv(
    r"D:\PhD\optical table\Device\Transmission\t_data_average_nir_smallLED_new_1.csv", header=None)
plt.show()
