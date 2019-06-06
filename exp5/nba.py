import jieba
import os
import re
#define stop words
rulefile = open("./stopwords.txt","r")
rules=set()
while True:
    line = rulefile.readline()
    line = line.strip('\n')
    rules.add(line)
    if not line:
        break

def train(D,Dc):
    global rules
    #Extract Vocabulary
    V = set() #tokens of all docs
    for document in D:
        rfile = open(document,"r")
        while True:
            line = rfile.readline()
            line = line.strip('\n')
            if not line:
                break
            terms = jieba.cut(line)
            for term in terms:
                if term not in rules and (not re.match("^[0-9]\d*$",term)):
                    V.add(term)
    for document in Dc:
        rfile = open(document,"r")
        while True:
            line = rfile.readline()
            line = line.strip('\n')
            if not line:
                break
            terms = jieba.cut(line)
            for term in terms:
                if term not in rules and (not re.match("^[0-9]\d*$",term)):
                    V.add(term)
    N = len(D)
    Nc = len(Dc)
    prior = Nc/(N+Nc)
    textc = [] #list
    T = {}
    Tn = {}
    for documentInClass in Dc:
        # print(documentInClass)
        DICfile = open(documentInClass,"r")
        while True:
            line = DICfile.readline()
            line = line.strip('\n')
            if not line:
                break
            terms = jieba.cut(line)
            for term in terms:
                if term not in rules and (not re.match("^[0-9]\d*$",term)):
                    if term in T:
                        T[term]+=1
                    else:
                        T[term]=1
    for documentNotInClass in D:
        # print(documentNotInClass)
        DICfile = open(documentNotInClass,"r")
        while True:
            line = DICfile.readline()
            line = line.strip('\n')
            if not line:
                break
            terms = jieba.cut(line)
            for term in terms:
                if term not in rules and (not re.match("^[0-9]\d*$",term)):
                    if term in Tn:
                        Tn[term]+=1
                    else:
                        Tn[term]=1
    condprob = {}
    condprobnot = {}
    denominator = 0
    denominatornot = 0
    for t in V:
        if t in T:
            denominator += T[t]+1
        else:
            T[t] = 0
            denominator += 1
        if t in Tn:
            denominatornot += Tn[t]+1
        else:
            Tn[t] = 0
            denominatornot += 1
    for t in V:
        condprob[t] = (T[t]+1)/denominator
        condprobnot[t] = (Tn[t]+1)/denominatornot
    # print(denominator)
    # print(denominatornot)
    # for line in T:
    #     print(line+":"+str(T[line]))
    # for line in Tn:
    #     print(line+":"+str(Tn[line]))
    return V,prior,condprob,condprobnot

traindir = "doc/trainset/"
tcfilelist = []
tfilelist = [] 
for filename in os.listdir(traindir+"1/"):
    tcfilelist.append(traindir+"1/"+filename)

count = 0

for filename in os.listdir(traindir):
    if os.path.isdir(traindir+filename):
        continue
    tfilelist.append(traindir+filename)
V,prior,condprob,condprobnot = train(tfilelist,tcfilelist)
# print(prior)
# for line in condprob:
#     print(line+":"+str(condprob[line])+"/"+str(condprobnot[line])+"="+str(condprob[line]/condprobnot[line]))
# exit()
modelfile = open("model","w+")
modelfile.writelines(str(len(V))+'\n')
for line in V:
    modelfile.writelines(line+'\n')
modelfile.writelines(str(prior)+'\n')
modelfile.writelines(str(len(condprob))+'\n')
for line in condprob:
    modelfile.writelines(line+'\n')
    modelfile.writelines(str(condprob[line])+'\n')
    modelfile.writelines(str(condprobnot[line])+'\n')
