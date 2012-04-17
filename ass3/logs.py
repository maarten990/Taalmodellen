import re, sys, math

with open(sys.argv[1], 'r') as f:
    probs = '[' + f.read() + ']'

probs = eval( re.sub(r'\n', r',\n', probs) )
logs = [math.log(p) for p in probs]

# output to stdout
for l in logs:
    print l
