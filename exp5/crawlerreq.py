import requests
import re
from bs4 import BeautifulSoup

url = "https://www1.szu.edu.cn/board/"
head = {
        "cookie":"ASPSESSIONIDQCQRCQQD=ADPFDOPCLNIGMAFFHNAJKGEB; ASPSESSIONIDQARRBTQD=MNMLCNCDDOHGBPHONJNFHCBE"
        }
# playload = {
#         "dayy":"30%2330%CC%EC%C4%DA",
#         "from_username":None,
#         "keyword":None,
#         "searchb1":"%CB%D1%CB%F7"
#         }
def getdata():
    purl = url+"?dayy=30%2330%CC%EC%C4%DA&from_username=&keyword=&searchb1=%CB%D1%CB%F7"
    # r = requests.post(url,headers=head,data=playload)
    r = requests.post(purl,headers=head)
    print(r.status_code)
    soup = BeautifulSoup(r.content,"html.parser",from_encoding="gb18030")

    alist = soup.find_all('a',target="_blank",href=re.compile("view.asp"))
    titlefile = open("title","w+")
    urlfile = open("boardurls","w+")
    for a in alist:
        urlfile.writelines(url+a["href"]+"\n")
        titlefile.writelines(a.string+"\n")

# getdata()
# exit()

alist = []
urlfile = open("boardurls","r+")
titlefile = open("title","r+")
while 1:
    urlline = urlfile.readline().strip('\n')
    titleline = titlefile.readline().strip('\n')
    if not urlline or not titleline:
        break
    alist.append((urlline,titleline))
# for a in alist:
#     print(a[1])
# exit()
cp = 1379
# result = re.findall('\"(.*?)\"', '"aa"aa(bc)"def"')
# print(result)
# exit()
for index,a in enumerate(alist[cp:]):
    r = requests.get(a[0],headers=head)
    print("doc"+str(index+cp)+":"+str(r.status_code))
    print(a[0])
    soup = BeautifulSoup(r.content,"html.parser",from_encoding="gb18030")
    title = a[1]
    wtfile = open("doc/"+title+".txt","w+")
    content = soup.find("table").find_all("table")[4].find_all("p")
    wtfile.writelines(title+'\n')
    for line in content:
        # if line.find_all("span") !=None:
        # line = re.findall('<.*>',str(line))
        # print(type(line))
        try:
            line = line.get_text()
            # print(line)
            wtfile.writelines(line+'\n')
        except TypeError:
            print("TypeError")
    # break
        # for span in line.find_all("span"):
            # print(span.string)
        # print(line.find_all("span"))
        # print(line.string)
        # if line.string != None:
            # print(line.string)
    # content = content.find("tbody").find_all("tr")[2].find("tbody").find_all("tr")[1]
    # print(content)
    # for p in plist:
    #     line=""
    #     empty = True
    #     spanlist=p.find_all("span")
    #     for span in spanlist:
    #         if span.string!=None:
    #             line=line+span.string
    #             empty = False
    #     if not empty:
    #         line=line+'\n'
    #         wtfile.writelines(line)
