
# This is pretty much what we submitted

def submission(N, M, chars):
    total_unknown = len(['?' for line in chars for ch in line if ch == '?'])

    DP = [[0 for _ in range(M - 1)] for _ in range(N - 1)]
    # DP[r][c] represents the number of ways to set the flag where the 'first' advertisement
    # has upper left corner at position (r, c). First means lowest r, then lowest c.

    for r in range(N - 1):
        for c in range(M - 1):
            if chars[r][c] in ['I', '?'] and chars[r][c+1] in ['C', '?'] and chars[r+1][c] in ['P', '?'] and chars[r+1][c+1] in ['C', '?']:
                local_unknown = len(['?' for line in chars[r:r+2] for ch in line[c:c+2] if ch == '?'])
                DP[r][c] = 3**(total_unknown - local_unknown)
                
                possible_double_count = 0

                # Now we get rid of duplicates.
                for old_r in range(N-1):
                    for old_c in range(M-1):
                        if old_r > r or (old_r == r and old_c >= c):
                            continue

                        # if old_r in [r-1, r] and old_c in [c-1, c, c+1]:
                        #     continue

                        possible_double_count += DP[old_r][old_c]

                DP[r][c] -= possible_double_count // 3**local_unknown

    print(DP)
    return sum([sum(row) for row in DP]) % 998_244_353
                

# This is a brute force approach

def has_icpc(N, M, chars):
    for r in range(N - 1):
        for c in range(M - 1):
            if chars[r][c] in ['I', '?'] and chars[r][c+1] in ['C', '?'] and chars[r+1][c] in ['P', '?'] and chars[r+1][c+1] in ['C', '?']:
                return True, r, c
            
    return False, -1, -1


def brute_force(N, M, chars):
    chars = [[ch for ch in line] for line in chars] # deep copy
    unknown_locations = [(r, c) for r in range(N) for c in range(M) if chars[r][c] == '?']
    unknown_count = len(unknown_locations)

    # We also deduce the DP table
    DP = [[0 for _ in range(M - 1)] for _ in range(N - 1)]
    count = 0
    for i in range(3**unknown_count):
        for r,c in unknown_locations:
            chars[r][c] = ['I','C','P'][i % 3]
            i = i // 3

        found, r, c = has_icpc(N, M, chars)
        if found:
            count += 1
            DP[r][c] += 1

    print(DP)
    return count % 998_244_353
            

# Now we generate grids until the two functions diverge...

if __name__ == '__main__':
    N, M = [int(i) for i in input().split(' ')]

    chars = [list(input()) for i in range(N)]

    print('Expected: ')
    print(brute_force(N, M, chars))
    print('Actual: ')
    print(submission(N, M, chars))
