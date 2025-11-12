import socket

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind(("localhost", 8080))

print(f"{server} listening on port 8080")

while True:
    filename, addr = server.recvfrom(1024)
    filename = filename.decode()
    print(f"Requested {filename}")

    try:
        with open(filename, 'r') as f:
            data = f.read()
        server.sendto(data.encode(), addr)
    except FileNotFoundError:
        server.sendto(b"File not found", addr)
