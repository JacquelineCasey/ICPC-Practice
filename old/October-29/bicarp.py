

def main():
    N = int(input())
    ticket = input()

    left_sum = 0
    right_sum = 0


    for i in range(N // 2):
        if ticket[i] == "?":
            left_sum += 4.5
        else:
            left_sum += int(ticket[i])

    for i in range(N // 2, N):
        if ticket[i] == "?":
            right_sum += 4.5
        else:
            right_sum += int(ticket[i])

    if left_sum == right_sum:
        print("Bicarp")
    else:
        print("Monocarp")
    


if __name__ == '__main__':
    main()