import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(("localhost", 8080))

server.listen(1)
print(f"{server} listening on port 8080")

while True:
    conn, addr = server.accept()
    print(f"Connected by {addr}")

    filename = conn.recv(1024).decode()

    try:
        with open(filename, 'r') as f:
            data = f.read()
        conn.send(data.encode())
    except FileNotFoundError:
        conn.send(b"File not found")

    conn.close()
