import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import csv
import seaborn

types = []
lambdas = []
lambdasT = []
h = []
hT = []
fours = 0

mydata0 = pd.read_csv("readable.csv", header=None)
for i in mydata0[2]:
    # print(i)
    if i == "4":
        types.append(1)
        fours += 1
    else:
        types.append(2 if i == "3" else 0)

mydata0[2] = types
# mydata0.to_csv("translated.csv")
dfSplit = np.split(mydata0, 30)

# mydata0[3].sor
# lAvg = np.average(mydata0[3])
# lTAvg = np.average(mydata0[4])
# hAvg = np.average(mydata0[5])
# hTAvg = np.average(mydata0[6])
# print(df)

for i in range(30):
    plt.plot(dfSplit[i][6], dfSplit[i][2])
# plt.legend(i for i in range(13))
plt.show()
# print("Average value for class IV:")
# print("   Lambda:           ", lAvg)
# print("   Totalistic Lambda:", lTAvg)
# print("   H:                ", hAvg)
# print("   Totalistic H:     \n", hTAvg)

# lAvg = np.std(mydata0[3])
# lTAvg = np.std(mydata0[4])
# hAvg = np.std(mydata0[5])
# hTAvg = np.std(mydata0[6])

# print("Standard Deviation for class IV:")
# print("   Lambda:           ", lAvg)
# print("   Totalistic Lambda:", lTAvg)
# print("   H:                ", hAvg)
# print("   Totalistic H:     ", hTAvg)
