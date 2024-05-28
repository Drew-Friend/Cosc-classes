import os
import numpy as np
import pandas as pd



def lab2exec(particleNum, inertia, cognition, social, testNum, function, varying, level="420"):
    os.execvp('python3', ['python3', 'pso.py', '--num_particles', str(particleNum), \
                                                '--inertia', str(inertia), \
                                                '--cognition',  str(cognition), \
                                                '--social', str(social), \
                                                '--testNum', str(testNum),\
                                                '--function', str(function),\
                                                '--varying', str(varying),\
                                                '--level', str(level)\
                                                ])

def runLab2Program():
    maxP = 128
    pCount = 0
    testNum = [0,0]
    numOfTests = 20
    globalTestNum = 0
    totalTests = 4000
    defaultParticle = 40
    defaultInertia = .5
    defaultCognition = 1
    defaultSocial = 1

    for functionIndex, function in enumerate(["booth","rosenbrock"]):
        for particleNum in range(10, 101, 10):
            for _ in range(0, numOfTests):       
                pid = os.fork()
                if pid == 0:
                    lab2exec(particleNum, defaultInertia, defaultCognition, defaultSocial, testNum[functionIndex], function, "num_particles")
                else:
                    print(globalTestNum, " / ", totalTests)
                    globalTestNum += 1
                    testNum[functionIndex] += 1
                    pCount += 1
                    if pCount == maxP:
                        pid, status = os.wait()
                        pCount -= 1

    while(pCount > 0 ):
        os.wait()
        pCount -= 1                  

    for functionIndex, function in enumerate(["booth","rosenbrock"]):
        for inertia in np.round(np.arange(.1, 1.01, .1), 2):
            for _ in range(0, numOfTests):       
                pid = os.fork()
                if pid == 0:
                    lab2exec(defaultParticle, inertia, defaultCognition, defaultSocial, testNum[functionIndex], function, "inertia")
                else:
                    print(globalTestNum, " / ", totalTests)
                    globalTestNum += 1
                    testNum[functionIndex] += 1
                    pCount += 1
                    if pCount == maxP:
                        pid, status = os.wait()
                        pCount -= 1

    while(pCount > 0 ):
        os.wait()
        pCount -= 1

    for functionIndex, function in enumerate(["booth","rosenbrock"]):
        for cognition in np.round(np.arange(0.1, 4.01, .1), 2):
            for _ in range(0, numOfTests):       
                pid = os.fork()
                if pid == 0:
                    lab2exec(defaultParticle, defaultInertia, cognition, defaultSocial, testNum[functionIndex], function, "cognition")
                else:
                    print(globalTestNum, " / ", totalTests)
                    globalTestNum += 1
                    testNum[functionIndex] += 1
                    pCount += 1
                    if pCount == maxP:
                        pid, status = os.wait()
                        pCount -= 1

    while(pCount > 0 ):
        os.wait()
        pCount -= 1

    for functionIndex, function in enumerate(["booth","rosenbrock"]):
        for social in np.round(np.arange(0.1, 4.01, .1), 2):
            for _ in range(0, numOfTests):       
                pid = os.fork()
                if pid == 0:
                    lab2exec(defaultParticle, defaultInertia, defaultCognition, social, testNum[functionIndex], function, "social")
                else:
                    print(globalTestNum, " / ", totalTests)
                    globalTestNum += 1
                    testNum[functionIndex] += 1
                    pCount += 1
                    if pCount == maxP:
                        pid, status = os.wait()
                        pCount -= 1

    while(pCount > 0 ):
        os.wait()
        pCount -= 1

'''
    for functionIndex, function in enumerate(["booth","rosenbrock"]):
        for social in np.round(np.arange(0.1, 4.01, .1), 2):
            for cognition in np.round(np.arange(0.1, 4.01, .1), 2):
                for _ in range(0, numOfTests):       
                    pid = os.fork()
                    if pid == 0:
                        lab2exec(defaultParticle, defaultInertia, cognition, social, testNum[functionIndex], function, "social/cognition", "527")
                    else:
                        print(globalTestNum, " / ", totalTests)
                        globalTestNum += 1
                        testNum[functionIndex] += 1
                        pCount += 1
                        if pCount == maxP:
                            pid, status = os.wait()
                            pCount -= 1

    while(pCount > 0 ):
        os.wait()
        pCount -= 1
'''

#num_particles  = Particle param
#inertia        = inertia param
#cognition      = cognition param
#social         = social param
#testnum        = testnumber (used for sorting data frame)
#varying        = Which param was beinbg varied for that test
#level          = Undergrad level --> 420, Graduate level --> 527
#epoch_stop     = Epoch stop number
#fitness        = Fitness
#solution_found = Solution found

with open("rosenbrock.csv", "w") as f:
    f.write("num_particles,inertia,cognition,social,testnum,varying,level,epoch_stop,fitness,solution_found\n")

with open("booth.csv", "w") as f:
    f.write("num_particles,inertia,cognition,social,testnum,varying,level,epoch_stop,fitness,solution_found\n")

runLab2Program()

df = pd.read_csv("rosenbrock.csv", delimiter=",")
df = df.sort_values(by=['testnum'])
df.to_csv('rosenbrock_sorted.csv', sep=',', index=False)

df = pd.read_csv("booth.csv", delimiter=",")
df = df.sort_values(by=['testnum'])
df.to_csv('booth_sorted.csv', sep=',', index=False)
