import sys
import symbol as sym
import os
class Gramma:

    def __init__(self,s):
        slist=s.split(" >> ")
        slist=map(lambda x:x.strip(),slist)
        self.Gid=slist[0]
        self.part_name=slist[1]
        self.Rid=slist[2]
        self.left=sym.find_id_bysym(slist[3])
        self.right=map(sym.find_id_bysym,slist[4].split(' '))
        '''
        print str(self.left)
        print str(self.right)

        '''
    def __str__(self):
        return str(self.left)+' >> '+str(self.right)
    def __repr__(self):
        return str(self.left)+' >> '+str(self.right)+'\n'
        #return ' >> '+self.right
    #def __str__(self):
        #return '%s,%s,%s,%d ->'%(self.Gid,self.Rid,self.part_name,self.left)
        #print self.right,"\n"
class GrammaService:
    gramma_list=[]
    gramma_path="./data/gramma"
    def read_gra(self):
        try:
            f=open(self.gramma_path)
        except Exception,e:
            sys.stderr.write('Error:%s\n' % e)
        readbuf=f.read()
        for record in readbuf.split('\n'):
            if(len(record)!=0):
                g = Gramma(record)
            self.gramma_list.append(g)
    def __init__(self):
        self.read_gra()

        #print g
    def debug(self):
        #print len(self.gramma_list)
        print self.gramma_list

if __name__ == '__main__':
    gra=GrammaService()
    gra.debug()



