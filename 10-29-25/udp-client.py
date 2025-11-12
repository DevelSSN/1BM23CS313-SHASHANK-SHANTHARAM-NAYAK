
import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

filename = input("Enter file name to request:")
client.sendto(filename.encode(), ("localhost", 8080))

data, _ = client.recvfrom(4096)

print("\n--- File Content ---")
print(data)

client.close()
