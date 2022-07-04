import sys
args = sys.argv[1:]

FILE_PREFIX = args[0].split("modistarc_")[0] + "modistarc_" 

test_names = []
for file in args:
    test_names.append(file.split("modistarc_")[1])

def filter(elem):
    return elem.split("_")[0]

test_names.sort(key=filter)

for test in test_names:
    print(FILE_PREFIX, test, sep="")
