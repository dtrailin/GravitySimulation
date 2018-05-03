import io
import sys
import re
from os import listdir
from os.path import isfile, join
mypath = "."
onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

out = open("runtime_single.csv", "w")
def get_walltime(file):
    match = re.search("submit_([0-9]+)_([0-9]+)_([0-9]+)_single",file)
    if match is not None:
        with open(file, "r") as ins:
            for line in ins:
                m = re.search("Walltime Used: ([0-9]+:[0-9]+:[0-9]+)",line)
                if m is not None:
                    group = m.group(1)                
                    out.write(match.group(1) + "," + match.group(2) + "," + match.group(3)  +","+ group + "\n")
 

for file in onlyfiles:
    # print(file)
    match = re.search(".o",file)
    if match is not None:
        get_walltime(file)