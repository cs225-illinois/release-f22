#!/usr/bin/python
import csv
import sys
import random, string

# NOTE: This produces an extra new line at the end of both files! 
# Manually delete (for now)

classes=int(sys.argv[1]) #no more than 500 courses (or adjust rantint bounds)
students=int(sys.argv[2])
s_per_c=int(sys.argv[3])
outName=sys.argv[4]

'''
courses = ['CS100', 'CS101', 'CS102', 'CS105', 'CS107', 'CS124', 'CS125', 'CS128', 'CS173', 'CS196',\
  'CS199', 'CS210', 'CS211', 'CS225', 'CS233', 'CS240', 'CS241', 'CS265', 'CS277', 'CS296', 'CS307',\
  'CS357', 'CS361', 'CS374', 'CS398', 'CS400', 'CS401', 'CS402', 'CS403', 'CS407', 'CS409', 'CS410',\
  'CS411', 'CS413', 'CS414', 'CS416', 'CS417', 'CS418', 'CS419', 'CS420']
'''

courseSet = set()
while(len(courseSet)<classes):
  courseSet.add("CS{}".format(random.randint(100, 600)))

studentSet = set()
while(len(studentSet)<students):
  x = ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range(4))
  studentSet.add(x)

courseDic = {}
studentDic = {}
studentList = list(studentSet)
for c in courseSet:
  courseDic[c]=random.sample(studentList, s_per_c)
  for stu in courseDic[c]:
    if stu in studentDic.keys():
      studentDic[stu].append(c)
    else:
      studentDic[stu]=[c]


outList = []
for c1 in courseDic.keys():
  outString = "{}".format(c1)
  for c2 in courseDic[c1]:
    outString+=", {}".format(c2)
  outList.append(outString+"\n")

outStu = []
for c1 in studentDic.keys():
  outString = "{}".format(c1)
  for c2 in studentDic[c1]:
    outString+=", {}".format(c2)
  outStu.append(outString+"\n")

with open(outName+"_roster.csv", "w") as myFile:
  for line in outList:
    myFile.write(line)

with open(outName+"_students.csv", "w") as myFile:
  for line in outStu:
    myFile.write(line)