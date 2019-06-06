import os
import math
import jieba

#define stop words
rulefile = open("./stopwords.txt","r")
rules=set()
while True:
    line = rulefile.readline()
    line = line.strip('\n')
    rules.add(line)
    if not line:
        break

word = "创业"
N={"11":0,"01":0,"10":0,"00":0} #N[0]:N11 N[1]:N01 N[2]:N10 N[3]:N00
# N[0]
filecount = 0

#get filelist
filelist = os.listdir("doc/trainset/1")
for fname in filelist:
    fname = "doc/trainset/1/"+fname
    if os.path.isdir(fname):
        continue
    filecount+=1
    rfile = open(fname,"r")
    #read lines of the file
    while True:
        flag = False
        line = rfile.readline()
        line = line.strip('\n')
        if not line:
            break
        terms = jieba.cut(line)
        for term in terms:
            if term==word:  #this word is in this doc
                flag = True
                break
        if flag:
            break
    if flag:
        # N[0]+=1 #N11++
        N["11"]+=1
    else:
        # N[1]+=1 #N01++
        N["01"]+=1

filelist = os.listdir("doc/trainset")
for fname in filelist:
    fname = "doc/trainset/"+fname
    if os.path.isdir(fname):
        continue
    filecount+=1
    rfile = open(fname,"r")
    #read lines of the file
    while True:
        flag = False
        line = rfile.readline()
        line = line.strip('\n')
        if not line:
            break
        terms = jieba.cut(line)
        for term in terms:
            if term==word:  #this word is in this doc
                flag = True
                break
        if flag:
            break
    if flag:
        # N[2]+=1 #N10++
        N["10"]+=1
    else:
        # N[3]+=1 #N00++
        N["00"]+=1

print(N)
print(filecount)
# N={"11":49,"01":141,"10":27652,"00":774106} #example
# filecount = 801948

I = N["11"]/filecount*math.log(filecount*N["11"]/((N["10"]+N["11"])*(N["11"]+N["01"])),2)
I += N["01"]/filecount*math.log(filecount*N["01"]/((N["00"]+N["01"])*(N["11"]+N["01"])),2)
I += N["10"]/filecount*math.log(filecount*N["10"]/((N["10"]+N["11"])*(N["10"]+N["00"])),2)
I += N["00"]/filecount*math.log(filecount*N["00"]/((N["00"]+N["01"])*(N["10"]+N["00"])),2)
print(I)
