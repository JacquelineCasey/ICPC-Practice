
if __name__ == '__main__':
    n = int(input())
    vals = [int(i) for i in input().split(' ')]
    vals.sort()
    
    print(sum(vals[(len(vals) + 1)//2:]))
