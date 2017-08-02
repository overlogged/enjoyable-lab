import re
import time
import difflib

def onQQMessage(bot, contact, member, content):
    if content[:3]=="/w ":
        words = content[3:]
        out = "可能出错了/(ㄒoㄒ)/~~"
        fin= open("zju.list","rt",encoding='utf-8')
        rmax = 0
        res = ""
        for line in fin:
            m = re.match(r'"(http.*)" "(.*)"',line)
            r = difflib.SequenceMatcher(None,m.groups()[1],words).ratio()
            if r>rmax:
                rmax=r
                res=m.groups()[1] + " " + words
        if rmax<0.4:
            res = "つ﹏⊂抱歉我没找到" + words
        bot.SendTo(contact,res)
        fin.close()
    """
def init():
    from bs4 import BeautifulSoup
    fin = open("zju.html","rt",encoding='utf-8')
    html = fin.read()
    soup = BeautifulSoup(html,"html.parser")
    out = open("zju.out","wt",encoding='utf-8')
    for item in soup.find_all('a'):
        out.write('"%s" "%s"\n' % (item.get('href'),item.get_text()))
def filter():
    fin = open("zju.out","rt",encoding='utf-8')
    fout = open("zju.list","wt",encoding='utf-8')
    import re
    for line in fin:
        m = re.match(r'("http.*") (".*")',line)
        if m:
            outs = "".join(m.groups()[1].split(' '))
            if outs!='""':
                fout.write('%s %s\n' % (m.groups()[0],outs))
    fin.close()
    fout.close()

filter()
"""