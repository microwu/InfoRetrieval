import re
from bs4 import BeautifulSoup
import urllib3
import certifi

head = {
        "cookie":"ASPSESSIONIDQATRCQRD=OMPKHFFCNDCCEOCEKABNKDFC;ASPSESSIONIDSCTTDRRC=IFINGEICBMBBBEBELOIDHOAM",
        # "content-length":"73",
        # "accept-language":"zh-TW,zh;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6",
        # "host":"www1.szu.edu.cn",
        # "content-type":"application/x-www-form-rulencoded",
        # "connection":"keep-alive",
        # "referer":"https://www1.szu.edu.cn/board/guide.asp",
        # "upgrade-insecure-requests":"1",
        "user-agent":"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.157 Safari/537.36"
    }
url = "https://www1.szu.edu.cn/board/"
field = {
    'dayy':'7%23%D2%BB%D6%DC%C4%DA',
    'from_username':'',
    'keyword':'',
    'searchb1':'%CB%D1%CB%F7'
        }
# proxy = urllib3.ProxyManager('127.0.0.1:1080',headers=default_headers)
http = urllib3.PoolManager(
    cert_reqs='CERT_REQUIRED',
    ca_certs=certifi.where())
# r = http.request('POST',url,headers=head)
# http.request
# r = http.request('post','https://www1.szu.edu.cn/board',headers=head,fields=field)
r = http.request('post','https://www1.szu.edu.cn/board',headers=head)
# r = http.request('GET','https://www1.szu.edu.cn')
# g = http.request('get','https://blog.csdn.net/c406495762/article/details/58716886')
print(r.status)

soup = BeautifulSoup(r.data,"html.parser",from_encoding="utf-8")
# print(soup.find_all('p'))
print(soup)

