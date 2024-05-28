import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import csv


df = pd.read_csv("liliCSV.csv")
params = [list()] * 20

for (
    index,
    row,
) in df.iterrows():
    if (
        row["Population Size"] == 50
        and row["Mutation Prob"] == 0.01
        and row["Crossover Prob"] == 0.3
    ):
        print(
            row["Tournament Size"],
            row["Average Fitness"],
            row["Best Fitness"],
        )

        params[int(row["Iteration"])][int(row["Tournament Size"])].append(
            [row["Average Fitness"], row["Best Fitness"]]
        )
        print(params[int(row["Iteration"])])


for i in range(20):
    plt.plot(params[i][0], params[i][1])
    plt.plot(params[i][0], params[i][2], color="green")

plt.show()
