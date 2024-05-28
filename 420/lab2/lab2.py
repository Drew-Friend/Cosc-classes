# CS 420/CS 527 Lab 2: Genetic Algorithms in LEAP
# Author: Catherine Schuman
# February 2022

import os
import numpy as np
from toolz import pipe

from leap_ec import Individual, context, test_env_var
from leap_ec import ops, probe, util
from leap_ec.decoder import IdentityDecoder
from leap_ec.binary_rep.problems import MaxOnes
from leap_ec.binary_rep.initializers import create_binary_sequence
from leap_ec.binary_rep.ops import mutate_bitflip
from leap_ec.binary_rep.problems import ScalarProblem
import argparse
import sys


# Implementation of a custom problem
class Lab2Problem(ScalarProblem):
    def __init__(self):
        super().__init__(maximize=True)

    def evaluate(self, ind):
        binNum = np.uint(0)
        for i in range(40):
            binNum = (binNum << 1) | ind[i]
        return (binNum / ((2 ** ind.size) - 1)) ** 10


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Lab 2: Genetic Algorithms")
    parser.add_argument("--n", default=50, help="population size", type=int)
    parser.add_argument(
        "--p_m", default=0.01, help="probability of mutation", type=float
    )
    parser.add_argument(
        "--p_c", default=0.3, help="probability of crossover", type=float
    )
    parser.add_argument("--trn_size", default=2, help="tournament size", type=int)
    parser.add_argument(
        "--csv_output", required=True, help="csv output file name", type=str
    )
    args = parser.parse_args()

    N = args.n
    p_m = args.p_m
    p_c = args.p_c
    trn_size = args.trn_size

    max_generation = 30
    l = 40
    parents = Individual.create_population(
        N,
        initialize=create_binary_sequence(l),
        decoder=IdentityDecoder(),
        problem=Lab2Problem(),
    )

    # Evaluate initial population
    parents = Individual.evaluate_population(parents)

    generation_counter = util.inc_generation()
    out_f = open(args.csv_output, "w", newline="")
    while generation_counter.generation() < max_generation:
        offspring = pipe(
            parents,
            ops.tournament_selection(k=trn_size),
            ops.clone,
            mutate_bitflip(probability=p_m),
            ops.uniform_crossover(p_xover=p_c),
            ops.evaluate,
            ops.pool(size=len(parents)),  # accumulate offspring
            probe.AttributesCSVProbe(stream=out_f, do_fitness=True, do_genome=True),
        )

        parents = offspring
        generation_counter()  # increment to the next generation

    out_f.close()
