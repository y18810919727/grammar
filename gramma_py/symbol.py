import sys
class Symbol:
    def __init__(self,s,id):
        self.name=s
        self.id=id
sym_list=[]
sym_map = {}
sym_cnt=0
def find_id_bysym(s):
    if(is_in_sym_list(s)==0):
        sym_map[s]=len(sym_list)
        sym_list.append(s)
    return sym_map[s]
def find_sym_byid(id):
    return sym_list[id]
def is_in_sym_list(s):
    if(sym_map.setdefault(s,-1)==-1):
        return 0
    else:
        return 1
if __name__ == '__main__':
    print find_id_bysym("/np")
    print find_id_bysym("/sp")
    print find_id_bysym("/ap")
    print find_sym_byid(0)
    print find_sym_byid(1)

