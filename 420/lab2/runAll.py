import os

ctr = 0
for i in range(20):
    for N in [25, 50, 75, 100]:
        for pm in [0, 0.01, 0.03, 0.05]:
            for pc in [0, 0.1, 0.3, 0.5]:
                for tSize in [2, 3, 4, 5]:
                    name = f"lili/{i},{N},{pm},{pc},{tSize}.csv"
                    os.system(
                        f"python3.9 lab2.py --n {N} --p_m {pm} --p_c {pc} --trn_size {tSize} --csv_output {name}"
                    )
                    ctr += 1
                    print(ctr)
