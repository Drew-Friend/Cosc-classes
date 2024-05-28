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
    "generation",
    "iteration",
    "N",
    "p_m",
    "p_c",
    "tournament_size",
    "average_fitness",
    "best_fitness",
    "best_genome",
    "solution_found",
    "num_solutions_found",
]
df = pd.read_csv("liliCSV.csv", usecols=columns)

generation = df.generation
average_fitness = df.best_fitness
average_fitness = df.average_fitness
N = df.N
p_m = df.p_m
p_c = df.p_c
t_size = df.tournament_size
print(N.shape)

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
        holder = x * 30 + i
        # print(generation[holder])
        if t_size[holder] == 2:
            if N[holder] == 50:
                if p_c[holder] == 0.3:
                    if float(p_m[holder]) == 0:
                        t_plotr.append(generation[holder])
                        fit_printr.append(average_fitness[holder])
                    elif float(p_m[holder]) == 0.01:
                        t_plotb.append(generation[holder])
                        fit_printb.append(average_fitness[holder])
                    elif float(p_m[holder]) == 0.03:
                        t_ploty.append(generation[holder])
                        fit_printy.append(average_fitness[holder])
                    elif float(p_m[holder]) == 0.05:
                        t_plotg.append(generation[holder])
                        fit_printg.append(average_fitness[holder])

    plt.plot(t_plotr, fit_printr, color="red")
    plt.plot(t_plotb, fit_printb, color="blue")
    plt.plot(t_ploty, fit_printy, color="yellow")
    plt.plot(t_plotg, fit_printg, color="green")

    # print(t_plotb)
plt.legend(["0", ".01", ".03", ".05"])
plt.show()
