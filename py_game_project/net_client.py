import os
from socket import *
host = "192.168.0.108"  # set to IP address of target computer
port = 1497
addr = (host, port)
UDPSock = socket(AF_INET, SOCK_DGRAM)
while True:
    data = bytes(input("Enter message to send or type 'exit': "), "utf-8")
    UDPSock.sendto(data, addr)
    if data == "exit":
        UDPSock.close()
        os._exit(0)
        break
UDPSock.close()
os._exit(0)
