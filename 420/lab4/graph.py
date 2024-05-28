import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

rosenbrock_df = pd.read_csv("rosenbrock_sorted.csv", delimiter=",")
booth_df = pd.read_csv("booth_sorted.csv", delimiter=",")

rosenbrock_df['varying'] = rosenbrock_df['varying'].replace(['particle'], 'num_particles')
booth_df['varying'] = booth_df['varying'].replace(['particle'], 'num_particles')

rosenbrock_df = rosenbrock_df.astype({  'num_particles': int,\
                                        'inertia': float,\
                                        'cognition' : float,\
                                        'social' : float,\
                                        'testnum': int,\
                                        'varying': str,\
                                        'level': int,\
                                        'epoch_stop': int,\
                                        'fitness': str,\
                                        'solution_found': float})

booth_df = booth_df.astype({    'num_particles': int,\
                                'inertia': float,\
                                'cognition' : float,\
                                'social' : float,\
                                'testnum': int,\
                                'varying': str,\
                                'level': int,\
                                'epoch_stop': int,\
                                'fitness': str,\
                                'solution_found': float})

df_names = ['Rosenbrock', 'Booth']
varying = ['num_particles', 'inertia', 'cognition', 'social']

#for some reason pso.py was printing like 2.10000000005 --> idk why :shrug:
for vary in varying:
    booth_df[vary] = booth_df[vary].round(2)
    rosenbrock_df[vary] = rosenbrock_df[vary].round(2)

dataframes = [rosenbrock_df, booth_df]

graphData = {}
saveFigures = []

for index, df in enumerate(dataframes):
    df_name = df_names[index]
    for param in varying:
        
        sub_df = df.loc[ (df['solution_found'] < (10**(-10))) &\
                         (df['varying'] == param)]
        
        x_temp = sub_df['epoch_stop'].to_list()
        y_temp = sub_df[param].to_list()
        graphData = {}
        
        for var in range(0, len(x_temp)):
            try:
                graphData[y_temp[var]].append(x_temp[var])
            except:
                graphData[y_temp[var]] = []
                graphData[y_temp[var]].append(x_temp[var])

        x_axis = list(graphData.keys())
        y_axis = list(graphData.values())
        averageLine = [np.mean(x) for x in y_axis]
        
        saveFigures.append(plt.figure()) 
        plt.boxplot(y_axis)
        plt.plot(range(1, len(x_axis) + 1), averageLine)
        plt.xticks(range(1, len(x_axis) + 1), labels=x_axis)
        
        plt.xlabel(param)
        plt.ylabel("Number of Epochs")
        plt.title(df_name)

for index, df in enumerate(dataframes):
    df_name = df_names[index]
    for param in varying:

        sub_df = df.loc[ (df['solution_found'] > (10**(-10))) & (df['varying'] == param)]
        if(sub_df.empty == True): continue
        
        paramValues = sub_df[param].unique()
        x_axis = []
        y_axis = []
        
        for val in paramValues:
            count = sub_df[param].loc[df[param] == val].count()
            x_axis.append(val)
            y_axis.append(count)
        
        saveFigures.append(plt.figure()) 
        plt.bar(range(1, len(x_axis) + 1), y_axis)
        plt.xticks(range(1, len(x_axis) + 1), labels=x_axis)
        plt.xlabel(param)
        plt.ylabel("Number of tests that did not converge")
        plt.title(df_name)
    
for index, fig in enumerate(saveFigures):
    fig.savefig("graphs/" + str(index) + ".png")

plt.show()

"""
for index, df in enumerate(dataframes):
    
    df_name = df_names[index]
    x_axis = []
    y_axis = []
    z_axis = []

    for social in np.round(np.arange(0.1, 4.01, .1), 2):
        for cognition in np.round(np.arange(0.1, 4.01, .1), 2):
            
            sub_df = df.loc[(df['social'] == social) &\
                            (df['cognition'] == cognition) &\
                            (df['varying'] == 'social/cognition')]
            
            meanEpochStop = np.mean(sub_df['epoch_stop'].to_list())
            
            x_axis.append(social)
            y_axis.append(cognition)
            z_axis.append(float(meanEpochStop))
    
    xi = np.linspace(min(x_axis), max(x_axis), 1000)
    yi = np.linspace(min(y_axis), max(y_axis), 1000)
    xi, yi = np.meshgrid(xi, yi)

    # Interpolate data
    zi = griddata((x_axis, y_axis), z_axis, (xi, yi), method='cubic')
    
    # Plot the result
    saveFigures.append(plt.figure()) 
    plt.pcolormesh(xi, yi, zi, shading='auto', cmap='gist_earth')
    plt.colorbar(label="Average Epoch Stop")
    plt.xlabel("Social")
    plt.ylabel("Cognition")


for index, df in enumerate(dataframes):
    
    df_name = df_names[index]
    x_axis = []
    y_axis = []
    z_axis = []

    for social in np.round(np.arange(0.1, 4.01, .1), 2):
        for cognition in np.round(np.arange(0.1, 4.01, .1), 2):
            
            sub_df = df.loc[ (df['social'] == social) &\
                             (df['cognition'] == cognition) &\
                             (df['varying'] == 'social/cognition') &\
                             (df['solution_found'] > (10**(-10)))]

            count = sub_df.shape[0]
            
            x_axis.append(social)
            y_axis.append(cognition)
            z_axis.append(float(count))
    
    xi = np.linspace(min(x_axis), max(x_axis), 1000)
    yi = np.linspace(min(y_axis), max(y_axis), 1000)
    xi, yi = np.meshgrid(xi, yi)

    zi = griddata((x_axis, y_axis), z_axis, (xi, yi), method='cubic')
    
    saveFigures.append(plt.figure())

    # Plot the result
    plt.pcolormesh(xi, yi, zi, shading='auto', cmap='gist_earth')
    plt.colorbar(label="Number of tests not converged")
    plt.xlabel("Social")
    plt.ylabel("Cognition")
"""    

