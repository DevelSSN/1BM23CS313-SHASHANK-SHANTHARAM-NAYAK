bsize = int(input("Enter bucket size:"))
rate = int(input("Enter rate:"))
data = list(map(int, input("Enter packet list:").split()))
buf = 0
print("t\t|buf before\t|arrive\t|buf after\t|drop\t|trans\t|buf after|")
for t, packets in enumerate(data):
    print(f"{t}\t|{buf}\t\t|{packets}\t|", end="")
    val = buf+packets
    buf = val if val < bsize else bsize
    drop = max(buf-val, 0)
    print(f"{buf}\t\t|{drop}\t|{rate if buf!=0 else 0}\t|", end="")
    buf = buf-rate if buf > 0 else 0
    print(f"{buf}\t  |")
