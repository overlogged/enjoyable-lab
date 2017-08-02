import re
import time
import difflib
from selenium import webdriver

def onQQMessage(bot, contact, member, content):
    words = content[3:]
    if content[:3]=="/w ":
        out = "可能出错了/(ㄒoㄒ)/~~"
        fin= open("zju.list","rt",encoding='utf-8')
        rmax = 0
        res = ""
        for line in fin:
            m = re.match(r'"(http.*)" "(.*)"',line)
            r = difflib.SequenceMatcher(None,m.groups()[1],words).ratio()
            if r>rmax:
                rmax=r
                res=m.groups()[1] + " " + m.groups()[0]
        if rmax<0.4:
            res = "つ﹏⊂抱歉我没找到" + words
        bot.SendTo(contact,res)
        fin.close()
    if content[:3]=='/m ':
        try:
            d = webdriver.PhantomJS(executable_path=r"/home/ubuntu/node_modules/phantomjs/bin/phantomjs")
            d.get('http://www.wolframalpha.com/')
            d.find_element_by_id('query').send_keys(words)
            d.find_element_by_name('equal').click()
            time.sleep(5)
            d.execute_script("document.querySelector('#Input > section > footer > div > button.plaintext.ng-isolate-scope').click()")
            ans = d.find_element_by_xpath('//*[@id="plaintext"]').text
            out = "^o^答案是：%s\n详细解答见：%s" % (ans,d.current_url)
            bot.SendTo(contact,out)
            d.close()
        except:
            bot.SendTo(contact,"可能出错了/(ㄒoㄒ)/~~")
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

words = "d(x+x^3)/dx"
d = webdriver.PhantomJS(executable_path=r"/home/ubuntu/node_modules/phantomjs/bin/phantomjs")
d.get('http://www.wolframalpha.com/')
time.sleep(1)
d.find_element_by_id('query').send_keys(words)
d.find_element_by_name('equal').click()
time.sleep(5)
print(d.current_url)
d.execute_script("document.querySelector('#Input > section > footer > div > button.plaintext.ng-isolate-scope').click()")
print(d.find_element_by_xpath('//*[@id="plaintext"]').text)
