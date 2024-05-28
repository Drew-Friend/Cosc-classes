# CS 420/CS 527 Lab 1: "Edge of Chaos" with Cellular Automata
# Adapted from Java program written by student in CS 420 in 2007
# Original Source found: http://web.eecs.utk.edu/~bmaclenn/Classes/420-527-S18/projects/project1/ca.html
# Adapted by Catherine Schuman
# January 2022

from imp import reload
import os
import numpy as np
import sys
import matplotlib.pyplot as plt
import matplotlib
import argparse
import time

class CASimulator():
    def __init__(self, num_experiments, seed, fn="MasterExperiment.csv", exp_dir="experiments"):
        self.num_experiments = num_experiments
        np.random.seed(seed)
        self.seed = seed
        self.num_states = 5
        self.radius = 1
        self.neighborhood = 2*self.radius+1
        self.fn = fn
        self.exp_dir = exp_dir
        self.dim = 200
        self.timesteps = 1000
       
        # TODO: You can update the colors as necessary 
        #state_colors = ["black", "blue", "green", "yellow", "orange"]
        self.palette = np.array([[0,0,0], [0, 0, 255], [0, 255, 0], [255, 255, 0], [255, 165, 0]])

    def simulate(self):
        reload(matplotlib)
        matplotlib.use('Agg')
        f = open(self.fn, "w")

        # TODO: Change to your name here!
        f.write("Drew Friend\n")
        f.write("Wrap:,true\n")
        f.write("K(states):," + str(self.num_states) + "\n")
        f.write("Radius:," + str(self.radius) + "\n")
        f.write("Quiescence:,true\n")    
        f.write("random seed:," + str(self.seed) + "\n")
        
        if not os.path.exists(self.exp_dir):
            os.makedirs(self.exp_dir)

        for experiment in range(self.num_experiments):
            # Initialize the board for this experiments
            board_seed = np.random.randint(0, self.num_states, self.dim)
            self.board = np.zeros((self.timesteps, self.dim))
            self.board[0,:] = board_seed
                       
            # Randomly initialize the rule
            to_be_decimated = []
            self.rule_table = [0]*13
            self.rule_table[0] = 0      # Quiescence 
            sb = "0"
            for x in range(1, 13):
                self.rule_table[x] = np.random.randint(1, self.num_states)
                to_be_decimated.append(x)
                sb += str(self.rule_table[x])

            rule_string = sb
            
            # Add in writing to experiment file
            f.write("\n\n")
            f.write("Experiment #:," + str(experiment)+"\n")
            f.write("Rule:," + rule_string+"\n")
            f.write("Step,Entry Zeroed,Class,Lambda,Lambda_t,H,H_t,Zeta,Observations\n")
            
            index_to_0 = 0
            for z in range(len(self.rule_table)):
                lam_T = self.calculate_lambda_t()
                lam = self.calculate_lambda()
                H_T = self.calculate_H_T()
                H = self.calculate_H()

                if (z == 0):
                    entry_zeroed = "-"
                else:
                    entry_zeroed = str(index_to_0)

                f.write(str(z) + "," + entry_zeroed + ",," + str(lam) + "," + str(lam_T) + "," + str(H) + "," + str(H_T) + ",,\n") 
                
                # Randomly select one to be decimated and remove it
                if (len(to_be_decimated) > 0):
                    index = np.random.randint(0, len(to_be_decimated))
                    index_to_0 = to_be_decimated.pop(index)

                # Step through time updating the board
                for x in range(len(self.board)-1):
                    for y in range(len(self.board[x])):
                        self.board[x+1][y] = int(self.rule_table[int(self.calculate_my_sum(x,y))])

                # Create the associated figure 
                fig = plt.figure()
                ax = plt.Axes(fig, [0., 0., 1., 1.])
                ax.set_axis_off() 
                fig.add_axes(ax)
                ax.imshow(self.palette[self.board.astype(int)]) 
                img_fn = self.exp_dir + "/experiment_" + str(experiment) + "_step_" + str(z) + ".png"
                plt.savefig(img_fn, dpi=800, bbox_inches="tight", pad_inches=0)
                plt.close('all')

                # Zero out one of the rule tables
                self.rule_table[index_to_0] = 0 
               
        f.close() 

    def calculate_lambda_t(self):
        num0 = 0
        for x in range(len(self.rule_table)):
             if (self.rule_table[x] == 0):
                num0 += 1
            
        return 1.0-(float(num0)/float(len(self.rule_table)))

    def calculate_lambda(self):
        d = [1, 3, 6, 10, 15, 18, 19, 18, 15, 10, 6, 3, 1]
        num0 = 0
        for x in range(len(self.rule_table)):
            new_state = self.rule_table[x]
            if (new_state == 0):
                num0 += d[x]
        
        return 1.0-((float(num0)/np.power(self.num_states, self.neighborhood))) 

    def calculate_H_T(self):
        state_occurrence = [0]*self.num_states
        for x in range(len(self.rule_table)):
            state_occurrence[self.rule_table[x]] += 1

        H_T = 0
        for x in range(self.num_states):
            ps = float(state_occurrence[x])/float(len(self.rule_table))
            if (ps != 0):
                H_T += (ps*np.log2(ps))

        return -1*H_T

    def calculate_H(self):
        d = [1, 3, 6, 10, 15, 18, 19, 18, 15, 10, 6, 3, 1]
        state_occurrence = [0]*self.num_states
        H = 0
        for x in range(len(self.rule_table)):
            new_state = self.rule_table[x]
            state_occurrence[new_state] += d[x]

        for x in range(self.num_states):
            ps = float(state_occurrence[x])/np.power(self.num_states, self.neighborhood)
            if (ps != 0):
                H += ps*np.log2(ps)

        return -1*H            
            
    def calculate_my_sum(self, r, c):
        row = self.board[r]
        s = 0
        for x in reversed(range(1,self.radius+1)):
            index = c-x
            if (index<0):
                s += row[len(row) + index]
            else:
                s += row[index]

        for x in range(0, self.radius+1):
            index = c+x
            if (index >= len(row)):
                s += row[index-len(row)]
            else:
                s += row[index]

        return s

    
if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Cellular Automata -- CS 420/527 Project 1")
    parser.add_argument("--experiments", "-e", required=True, type=int, help="Number of experiments")
    parser.add_argument("--seed", required=False, type=int, default=-123, help="RNG seed (default is the time")
    parser.add_argument("--exp_dir", type=str, default="experiments", help="Directory to put experiment files.")
    parser.add_argument("--master_file", type=str, default="MasterExperiment.csv", help="Master file name")

    args = parser.parse_args()

    if (args.seed == -123):
        seed = int(time.time())
    else:
        seed = args.seed

    cas = CASimulator(args.experiments, seed, args.master_file, args.exp_dir)
    cas.simulate()
