import re
import time
import difflib
from selenium import webdriver
from urllib.parse import quote

def onQQMessage(bot, contact, member, content):
    words = content[3:]
    if content[:2]=="/h":
        bot.SendTo(contact,"/h => 帮助\n/w 网站名称 => 查询校内常用网站\n/m 数学式子 => 调用wolframalpha(显示友好但回复慢)\n/a 数学式子 => 快速回复")
    elif content[:3]=="/w ":
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
    elif content[:3]=='/m ':
        url="可能出错了QAQ"
        try:
            d = webdriver.PhantomJS(executable_path=r"/home/ubuntu/node_modules/phantomjs/bin/phantomjs")
            code = quote(words)
            url = 'http://www.wolframalpha.com/input/?i=%s'%code
            d.get(url)
            
            time.sleep(1)
            fail=10
            while(fail>0):
                try:
                    d.execute_script("document.querySelector('#Input > section > footer > div > button.plaintext.ng-isolate-scope').click()")
                    fail = -1
                except:
                    time.sleep(1)
                    fail -= 1
            
            ans = d.find_element_by_xpath('//*[@id="plaintext"]').text
            out = "^_^答案是：%s\n详细解答见：%s" % (ans,url)
            bot.SendTo(contact,out)
            d.close()
        except:
            bot.SendTo(contact,url)
    elif content[:3]=='/a ':
        time.sleep(0.5)
        code = quote(words)
        out = 'PC端：http://www.wolframalpha.com/input/?i=%s \n 移动端：http://m.wolframalpha.com/input/?i=%s '%(code,code)
        bot.SendTo(contact,out)
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
"""