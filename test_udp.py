import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

for i in range(50):
    msg = f'IMU,{i*10},{0.02*i:.2f},-0.01,0.98,1.2,-0.3,9.7'
    s.sendto(msg.encode(), ('127.0.0.1', 5005))
    print(f"Sent: {msg}")
    time.sleep(0.05)

print("Done.")
