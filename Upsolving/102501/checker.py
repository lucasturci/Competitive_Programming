import sys

mat = [[1 if x == "P" else 0 for x in line.split()] for line in sys.stdin]

moves = [[0, 0], [0, 1], [0, -1], [1, 0], [-1, 0]]

n, m = len(mat), len(mat[0])
for i in range(n):
    for j in range(m):
        tot = 0
        for move in moves:
            p = i + move[0]
            q = j + move[1]

            if p >= 0 and p < n and q >= 0 and q < m and mat[p][q]:
                tot = 1 - tot
        
        print('B' if tot == 1 else 'W', end=' ')

    print()