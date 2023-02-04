
def all_combinations(a, b):
    result = [a+b, a-b, a*b]
    if b != 0 and a % b == 0:
        result.append(a // b)

    return result


def main():
    a, b, c = map(int, input().split(' '))

    result = []
    for d in all_combinations(a, b):
        result = result + all_combinations(d, c)

    print(min([i for i in result if i >= 0]))


if __name__ == '__main__':
    main()