

def min_thrown_out(a1, a2, k1, k2, cards):
    # Calculate the max cards given out for no rejections
    buffer = a1 * (k1 - 1) + a2 * (k2 - 1)
    return cards - buffer

def max_thrown_out(a1, a2, k1, k2, cards):
    team_1_cards = min(cards, a1 * k1)
    team_2_cards = cards - team_1_cards

    team_1_thrown = team_1_cards // k1
    team_2_thrown = team_2_cards // k2

    return min(team_1_thrown + team_2_thrown, a1 + a2)

def main():
    a1 = int(input())
    a2 = int(input())
    k1 = int(input())
    k2 = int(input())
    cards = int(input())

    # WLOG, let the first team be the one with lower k
    if k1 > k2:
        tmp = k1
        k1 = k2
        k2 = tmp
        tmp = a1
        a1 = a2
        a2 = tmp

    min = min_thrown_out(a1, a2, k1, k2, cards)
    max = max_thrown_out(a1, a2, k1, k2, cards)

    print(min, max)




if __name__ == '__main__':
    main()