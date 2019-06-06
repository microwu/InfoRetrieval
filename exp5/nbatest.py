import math
import os
import re
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

def getdata():
    datafile = open("./model","r")
    size = datafile.readline()
    size = int(size)
    V = set()
    while size>0:
        line = datafile.readline()
        line = line.strip('\n')
        V.add(line);
        size-=1
    prior = datafile.readline()
    size = datafile.readline()
    size = int(size)
    condprob = {}
    condprobnot = {}
    while size>0:
        key = datafile.readline().strip('\n')
        value1 = datafile.readline().strip('\n')
        value1 = float(value1)
        value2 = datafile.readline().strip('\n')
        value2 = float(value2)
        condprob[key]=value1
        condprobnot[key]=value2
        size-=1
    return V,prior,condprob,condprobnot

def getscore(filename):
    global V,prior,condprob,condprobnot
    evalfile = open(filename,"r")
    W = set()
    while True:
        try:
            line = evalfile.readline().strip('\n')
            if not line:
                break
            terms = jieba.cut(line)
            for term in terms:
                if term not in rules and (not re.match("^[0-9]\d*$",term)):
                    if term in V:
                        W.add(term)
        except UnicodeDecodeError:
            print("Error:"+filename)
            return 0
    score =  math.log(float(prior),10)
    for t in W:
        # print(t+":"+str(condprob[t]/condprobnot[t]))
        if t in condprob:
            score += math.log(condprob[t]/condprobnot[t],10)
        # print(score)
    return score

V,prior,condprob,condprobnot = getdata()
# filename = "./doc/evalueset/1/全国大学生物联网设计竞赛简介.txt"
evaldir = "doc/evalueset/"
ecfilelist = []
efilelist = []
losscount = 0
for filename in os.listdir(evaldir+"1/"):
    ecfilelist.append(evaldir+"1/"+filename)
for ecfile in ecfilelist:
    score = getscore(ecfile)
    if score < 1:
        print(ecfile+":"+str(score))
        losscount+=1
for filename in os.listdir(evaldir):
    if os.path.isdir(evaldir+filename):
        continue
    efilelist.append(evaldir+filename)
for efile in efilelist:
    score = getscore(efile)
    if score > 1 :
        print(efile+":"+str(score))
        losscount+=1
print("Accuracy:"+str(1-(losscount/(len(ecfilelist)+len(efilelist)))))
