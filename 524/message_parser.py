import re
import sys

# 1 digit hour, leading 0, or 24 hour time
tC = "[0-9]|[0-1][0-9]|[2][0-3]:[0-5][0-9]\s?AM|PM|am|pm|a.m.|A.M.|p.m.|P.M.?"
# Relative
rel = "next|last"
# section of time
toD = "afternoon|morning|noon|evening|midnight|week(end)?|month|year|night"
# Weekday
wD = "sunday|Sunday|Monday|monday|Tuesday|tuesday|Wednesday|wednesday|Thursday|thursday|Friday|friday|Saturday|saturday"
# Specific relative days
titles = "yesterday|tomorrow|today"

mods = "on|around|at|in"

pattern = "|".join([tC, rel, toD, wD, titles, mods])
pattern = "\\b(" + pattern + ")"


def parse(sentence):
    complete = ""
    isTime = False
    words = sentence.split()

    for w in range(len(words)):
        if re.search(pattern, words[w]) != None:
            if not isTime:
                complete += "_"
                isTime = True
            complete += words[w] + " "
        else:
            if isTime and words[w] != "the":
                complete = complete[:-1] + "_"
                complete += " "
                isTime = False
            complete += words[w] + " "

    if isTime:
        complete = complete[:-1] + "_"
    print(complete)


sentence = sys.argv[1]
parse(sentence)
