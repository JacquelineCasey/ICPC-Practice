
def main():
    n, m = map(int, input().split(' '))

    items = list(range(1, n+1))
    rungs = [int(input()) for _ in range(m)]

    for i in rungs:
        items[i-1], items[i] = items[i], items[i-1]

    for i in items:
        print(i)


if __name__ == '__main__':
    main()
