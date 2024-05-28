import pandas as pd
import numpy as np
import os
import csv


def findMax(generation):
    ind = generation.loc[:, "fitness"].idxmax()
    return (generation.loc[:, "fitness"][ind], generation.loc[:, "genome"][ind])


def findOne(generation):
    ones = list()
    a = 0
    for index, row in generation.iterrows():
        if row["genome"].count("0") == 0:
            ones.append(a)
        a += 1
    return len(ones)


directory = "runs/"
avg_fits = list()
max_fits = list()
check_one = list()
params = list()
ctr = 0
for filename in os.listdir(directory):
    params.append(filename.split(","))
    ctr += 1
    f = os.path.join(directory, filename)
    if ctr % 10 == 0:
        print(ctr)

    df = pd.read_csv(f)

    # Getting rid of extra labels after every generation
    df_alt = df.transpose()
    ind_list = list()
    for i in range(0, df_alt.shape[1]):
        if df_alt[i][0] == "step":
            ind_list.append(i - len(ind_list))
    for j in ind_list:
        df_alt = df_alt.drop(df_alt.columns[j], axis=1)
    df_alt = df_alt.transpose()
    df_alt = df_alt.astype({"step": "int", "fitness": "float"})

    gens = np.array_split(df_alt, 30)

    for k in range(30):
        avg_fits.append(gens[k].loc[:, "fitness"].mean())
        max_fits.append(findMax(gens[k]))
        check_one.append(findOne(gens[k]))

cFile = open("liliCSV.csv", "w")
writer = csv.writer(cFile)

writer.writerow(
    [
        "Generation",
        "Iteration",
        "Population Size",
        "Mutation Prob",
        "Crossover Prob",
        "Tournament Size",
        "Average Fitness",
        "Best Fitness",
        "Best Genome",
        "Solution Found?",
        "Number of Solutions",
    ]
)

for r in range(len(avg_fits)):
    print(r)
    writer.writerow(
        [
            r % 30,
            params[r // 30][0],
            params[r // 30][1],
            params[r // 30][2],
            params[r // 30][3],
            params[r // 30][4],
            avg_fits[r],
            max_fits[r][0],
            max_fits[r][1],
            "false" if check_one[r] == 0 else "true",
            check_one[r],
        ]
    )

cFile.close()
