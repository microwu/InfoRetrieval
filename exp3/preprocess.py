import re
import os
import sys
import getopt

def preprocess():
    rulefile = open("common-english-words.txt","r")#stop words list
    opfile = open("AMiner-Paper.txt","r")#source file
    wtfile = open("AMiner-Paper-Abs.txt","w+")#abstract only
    stopfile =open("AMiner-Paper-Abs-Stop.txt","w+") #stopword removed
    count=0
    stop=set()
    while 1:
        line=rulefile.readline()
        stop.add(line.strip('\n'))
        if not line:
            break
    while 1:
        line=opfile.readline()
        if(line[0:2]=="#!"):
            count+=1
            # print(line)
            terms = re.findall('[a-zA-Z0-9]+',line[3:])
            outputline = ''
            stopline = ''
            for index,term in enumerate(terms):
                if index!=len(terms)-1:
                    outputline+=term.lower()+' '
                    if term.lower() not in stop:
                        stopline+=term.lower()+' '
                else:
                    outputline+=term.lower()+'\n'
                    if term.lower() not in stop:
                        stopline+=term.lower()+'\n'
                    else:
                        stopline+='\n'
            wtfile.writelines(outputline)
            stopfile.writelines(stopline)
        if not line or count>=100000:
            break

if __name__=='__main__':
    preprocess()
