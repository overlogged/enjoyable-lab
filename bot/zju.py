import re
import time

fin= open("zju.list","rt",encoding='utf-8')
zjudict = {}
for line in fin:
    m = re.match(r'"(http.*)" "(.*)"',line)
    zjudict[m.groups()[1]] = m.groups()[0]

def onQQMessage(bot, contact, member, content):
    time.sleep(2)
    if 1 or content[:3]=="/w ":
        words = content[3:]
        bot.SendTo(contact,zjudict.get("".join(words.split(' ')),d="つ﹏⊂抱歉我没找到")+" "+words)
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