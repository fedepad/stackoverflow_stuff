def count_evens_2d():
    count = 0
    xss = [[10,13,17],[3,6,1],[13,11,12]]   
    for i in xss:
        for j in i:
            if j%2 == 0:
                count += 1
    print(count)

def min_2d():
    xss = [[10,13,17],[3,6,1],[13,11,12]]
    lowest_val = None
    for i in xss:
        for j in i:
            if lowest_val is None or j < lowest_val:
                lowest_val = j
                print(lowest_val)

count_evens_2d()
min_2d()
