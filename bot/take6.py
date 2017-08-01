import re
import time
import os

def onQQMessage(bot, contact, member, content):
    time.sleep(2)
    def admin(contact):
        return (contact.qq=="1761440454" or contact.mark=="admin")
    m = re.match(r"\/log (\d+)",content)
    if m and ((contact.qq=="659529585") or admin(contact)):
        try:
            n = int(m.groups()[0])
            fin = open("~/take6/log.txt","rt")
            lines = fin.readlines()
            skip=len(lines)-n
            out=""
            for line in lines:
                if skip>0:
                    skip -= 1
                else:
                    out+=line
            bot.SendTo(contact,out.rstrip('\n'))
            fin.close()
        except:
            pass
    elif content=="reset" and (admin(member) or admin(contact)):
        os.system("pkill java & cd ~/take6/server & sbt run &")