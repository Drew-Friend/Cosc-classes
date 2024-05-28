import numpy as np
import matplotlib.pyplot as plt

# Define the sign
def sign(x):
    return 1 if x >= 0 else -1


# Check Stability
# Output: False if any s' != s, True otherwise
def run(network, weights):  # Step 3b
    n = len(network)
    for i in range(n):
        h = 0
        for j in range(n):
            h += weights[i][j] * network[j]
        if network[i] != sign(h):
            return False
    return True


# Imprints Patterns
def getWeights(N, p, arr):
    weights = np.zeros((N, N))
    for i in range(N):
        for j in range(i, N):
            for k in range(p + 1):
                weights[i][j] += arr[k][i] * arr[k][j]
            weights[j][i] = weights[i][j]
        weights[i][i] = 0
    weights = weights / N
    return weights


# Average function bc its across my 2nd dimension, not first like numpy likes
def avg(nums):
    ret = np.zeros(50)
    for i in range(len(nums[0])):
        for j in range(5):
            ret[i] += nums[j][i]
        ret[i] = ret[i] / 5
    return ret


# Standard Deviation function for the same reason as above
def std(nums):
    ret = np.zeros(50)
    pH = [0] * 5
    for i in range(len(nums[0])):
        for j in range(5):
            pH[j] = nums[j][i]
        ret[i] = np.std(pH)
    return ret


n = 100
p = 50
stableNum = [[0 for i in range(p)] for j in range(5)]
unstableNum = [[0 for i in range(p)] for j in range(5)]


for k in range(5):
    patterns = [np.random.choice([-1, 1], n) for i in range(p)]  # Step 1
    for i in range(p):
        weights = getWeights(n, i, patterns)
        for j in range(i + 1):
            network = patterns[j]  # Step 3a
            if run(network, weights):
                stableNum[k][i] += 1

for j in range(5):
    for i in range(p):
        unstableNum[j][i] = 1 - (stableNum[j][i] / (i + 1))

# Stable Graphs
for i in range(5):
    plt.plot(range(p), stableNum[i])
plt.show()
mean = avg(stableNum)
error = std(stableNum)
plt.plot(range(p), mean)
plt.fill_between(range(p), mean - error, mean + error, alpha=0.5)
plt.show()

# Unstable Graphs
for i in range(5):
    plt.plot(range(p), unstableNum[i])
plt.show()
mean = avg(unstableNum)
error = std(unstableNum)
plt.plot(range(p), mean)
plt.fill_between(range(p), mean - error, mean + error, alpha=0.5)
plt.show()
