import message_parser

tests = [
    "hello",
    "6:45am",
    "12:00 PM",
    "next thursday",
    "monday night",
    "lets go bowling on saturday night around 8pm?",
    "How about SoKno tomorrow at 7",
    "im going to the game at 4p.m. on sunday",
    "Im going to get breakfast at midnight tomorrow. maybe also at 16:57 pm",
    "1 in the afternoon is the same as 13 in the afternoon",
    "this is just the number 6",
    "around 12 in the evening",
    "at about 3:45, I'll be leaving until tuesday",
    "I will be driving back home next month to see my doctor at 9:15 in the morning",
    "the grocery store yesterday around midnight was packed",
    "last year I went to the beach",
    "I went last weekend on sunday at 3 in the afternoon",
]

for i in range(len(tests)):
    message_parser.parse(tests[i])
# message_parser.parse(tests[7])
