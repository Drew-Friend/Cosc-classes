import pandas as pd
from matplotlib import pyplot as plt

generation = list()
average_fitness = list()
N = list()
p_m = list()
p_c = list()
t_size = list()


plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True
columns = [
    "iteration",
    "N",
    "p_m",
    "p_c",
    "tournament_size",
    "generation",
    "average_fitness",
    "best_fitness",
    "best_genome",
    "solution_found",
    "num_solutions_found",
]
df = pd.read_csv("liliCSV.csv", usecols=columns)

generation = df.Generation
average_fitness = df.best_fitness
N = df.N
p_m = df.p_m
p_c = df.p_c
t_size = df.tournament_size
print(t_size)
print(N)
print(p_m)
print(p_c)

for x in range(5120):
    t_plotr = list()
    fit_printr = list()
    t_plotb = list()
    fit_printb = list()
    t_ploty = list()
    fit_printy = list()
    t_plotg = list()
    fit_printg = list()

    for i in range(30):

        if N[x * 30 + i] == 50:
            # print("in firsrt lop")

            if float(p_c[x * 30 + i]) == 0.3:
                if p_m[x * 30 + i] == 0.01:
                    # print("in inner lop")

                    if t_size[x * 30 + i] == 2:
                        t_plotr.append(generation[x * 30 + i])
                        fit_printr.append(average_fitness[x * 30 + i])
                    if t_size[x * 30 + i] == 3:
                        t_plotb.append(generation[x * 30 + i])
                        fit_printb.append(average_fitness[x * 30 + i])
                    if t_size[x * 30 + i] == 4:
                        t_ploty.append(generation[x * 30 + i])
                        fit_printy.append(average_fitness[x * 30 + i])
                    if t_size[x * 30 + i] == 5:
                        t_plotg.append(generation[x * 30 + i])
                        fit_printg.append(average_fitness[x * 30 + i])

    plt.plot(t_plotr, fit_printr, color="red")
    plt.plot(t_plotb, fit_printb, color="blue")
    plt.plot(t_ploty, fit_printy, color="yellow")
    plt.plot(t_plotg, fit_printg, color="green")

    # print(t_plotb)

plt.show()
