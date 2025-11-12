import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(("localhost", 8080))

filename = input("Enter file name to request:")
client.send(filename.encode())

data = client.recv(4096).decode()

print("\n--- File Content ---")
print(data)


client.close()
