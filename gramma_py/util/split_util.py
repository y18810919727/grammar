import itertools
'''

'''
def test():
    li = range(1,10)
    li2 = itertools.product(li)
    for i in li2:
        print list(i)


def judge(li):
    la = 1
    for x in li:
        if(x<=la):
            return 0
        la=x
    return 1


def split_seg(l,r,seg_cnt):
    li=[]
    if seg_cnt == 1:
        li.append([])
    elif seg_cnt == 2:
        for i in range(l,r):
            li.append([i])
    else:
        li = range(l,r)
        s=""
        seg_cnt=seg_cnt-1
        while seg_cnt!=0:
            if s=="":
                s="li"
            else:
                s=s+",li"
            seg_cnt=seg_cnt-1
        print s
        print eval(s)
        li = itertools.product(*eval(s))
        li = map(list,li)
    res=[]
    for i in li:
        if judge(i)==1:
            i.insert(0,l)
            i.append(r)
            res.append(i)
    return res

if __name__ == '__main__':
    res = split_seg(1,5,2)
    print res
    #test()




