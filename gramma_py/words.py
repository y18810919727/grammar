import sys
# storage the words list and theirs  type
class words:
    words_list=[]
    words_map = {}
    words_cnt=0

    #find on the id of the words
    def find_id_bywords(self,s):
        if(self.is_in_words_list(s)==0):
            self.words_map[s]=len(self.words_list)
            self.words_list.append(s)
        return self.words_map[s]

    #find the words by id
    def find_words_byid(self,id):
        return self.words_list[id]
    #To judge the words are in words_list or not
    def is_in_words_list(self,s):
        if(self.words_map.setdefault(s,-1)==-1):
            return 0
        else:
            return 1
if __name__ == '__main__':
    '''
    print find_words_byid(0)
    print find_words_byid(1)
    '''
