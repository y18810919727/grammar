import sys
import words
import symbol as sym
import os
class Lexicon:

    def __init__(self,s):
        slist=s.split(" >> ")
        slist=map(lambda x:x.strip(),slist)
    #    print slist
        self.Gid=slist[0]
        self.part_name=slist[1]
        self.Rid=slist[2]
        self.left=sym.find_id_bysym(slist[3])
    #    print slist[4]
        self.right=words.find_id_bywords(slist[4])
        #def __str__(self):
        #return '%s,%s,%s,%d ->'%(self.Gid,self.Rid,self.part_name,self.left)
        #print self.right,"\n"
    def findleft(self):
        return self.left
    def findright(self):
        return self.right

class LexiconService:
    word_dict={}
    lexicon_path="./data/lexicon"
    lexicon_list=[]
    def __init__(self):
        self.read_words()
        word_dict = words()
    def read_words(self):
        try:
            f=open(self.lexicon_path)
        except Exception,e:
            sys.stderr.write('Error:%s\n' % e)
        readbuf=f.read()
        lexicon_list=[]
        for record in readbuf.split('\n'):
            if(len(record)!=0):
                g = Lexicon(record)
            lexicon_list.append(g)
            #print g
    def getlexicon_size(self):
        return len(self.lexicon_list)
def split_sentence(s):
    s=str(s).strip().lower()
    l=s.split(' ')
    print l
    pre=""
    ans=[]
    for w in l:
        pre=pre+" "+w
        print pre.strip()
        res=words.is_in_words_list(pre.strip())
        if(res==1):
            ans.append(words.find_id_bywords(pre.strip()))
            pre=""
    return ans
if __name__ == '__main__':
    read_words()
    #print word_dict
    s="Characteristic transformation temperatures were determined using electrical resistivity"
    print words.words_map
    print split_sentence(s)


