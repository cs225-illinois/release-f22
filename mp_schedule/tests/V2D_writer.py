#!/usr/bin/python
import csv
import sys
import random, string

# Reads in a text file and prints out an autograder friendly format to copy over
# Also have to delete the last ',\' because I'm lazy
f=sys.argv[1] 

print("{")
with open(f) as myFile:
  for line in myFile:
    spline = line.split(",")
    outLine = "{"
    for i in range(len(spline)-1):
      outLine = outLine + "\"" + spline[i].strip() + "\", "
    outLine = outLine + "\"" + spline[len(spline)-1].strip()+"\"}, \\"
    print(outLine)
print("};")

    
