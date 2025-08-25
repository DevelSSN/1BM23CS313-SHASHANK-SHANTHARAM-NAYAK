import random


def init():
    global rooms
    print("1=dirty 0=clean")
    n, m = int(input("Enter n, m:")), int(input())
    print("Enter the status of rooms")
    rooms = [[int(input()) for x in range(m)] for y in range(n)]
    global posx
    global posy
    posx, posy = int(input("Enter init room:")), int(input())


def searchDirty():
    li = []
    for i in range(len(rooms)):
        for j in range(len(rooms[i])):
            if rooms[i][j] == 1:
                li.append((i, j))
    return li


def searchAdj(i, j):
    n = len(rooms)
    m = len(rooms[0])
    # Initialising a list where adjacent elements will be stored
    ans = []
    # Checking for all the possible adjacent positions
    if isValidPos(i - 1, j, n, m):
        ans.append((i-1, j))
    if isValidPos(i, j - 1, n, m):
        ans.append((i, j-1))
    if isValidPos(i, j + 1, n, m):
        ans.append((i, j+1))
    if isValidPos(i + 1, j, n, m):
        ans.append((i+1, j))

    # Returning the list
    return ans


def isValidPos(i, j, n, m):
    if i < 0 or j < 0 or i >= n or j >= m:
        return 0
    return 1 and rooms[i][j] == 1


def clean(posx, posy):
    print(f"Cleaned {posx}, {posy}")
    rooms[posx][posy] = 0


def isClean():
    for room in rooms:
        for cell in room:
            if cell == 1:
                return False
    return True


init()
count = 0
while not isClean():
    count += 1
    clean(posx, posy)
    li = searchDirty()
    if (len(li) == 0):
        print(f"All rooms are clean. Cost={count}")
        exit(0)
    adj = searchAdj(posx, posy)
    posx, posy = random.choice(adj)
    print(f"Moved to {posx}, {posy}")
