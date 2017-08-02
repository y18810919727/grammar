import gramma
import lexicon
import symbol
import sys
class Run_sentence:

    def __init__(self):
        a=10
        self.gra =gramma.GrammaService()
        #self.lex = lexicon.LexiconService()

    def make_new_dp(self,n,m):
        dp=[[[{'vis':0, 'method':[],'cnt':0} for s in range(m)] for col in range(n)] for row in range(n+1)]
        return dp

    def run(self,sentence):
        slist=sentence.lower().split(' ')
        slist.remove('.')
        n=len(slist)
        m=len(self.gra.gramma_list)
        dp=self.make_new_dp(n,m)
        for i in range(0,n):
            for j in range(i+1,n+1):
                print ' '.join(slist[i:j])
    '''
    def run(self,sentence):
        dp=self.pre(n,len(grama_list))
        #sentence= str(sentence)

        print slist
        for i in range(0,n):
            str=""
            for j in range(i,n):
                str=str+slist[j]
                slist=sentence.lower().split(' ')


    '''
if __name__ == '__main__':
    a=10
