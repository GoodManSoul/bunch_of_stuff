import os
import time
import random
import sys
import pygame

from socket import *

server_ip = "192.168.0.108"
server_recieve_port = 1500

server_address = (server_ip, server_recieve_port)

UDPSocket = socket(AF_INET, SOCK_DGRAM)

SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT = 950, 640
CLEAR_SCREEN = 0, 0, 0


PLAYER_INFO = PLAYER_X, PLAYER_Y, PLAYER_W, PLAYER_H, COLOR_R, COLOR_G, COLOR_B = 100, 10, 5, 5, 255, 255, 255


def Connect_to_server():
    global PLAYER_INFO
    print("[...]Connecting to server[...]")
    UDPSocket.sendto(bytes("HELLO", "utf-8"), server_address)
    pygame.time.delay(16)
    for i in range (len(PLAYER_INFO)):
        print(PLAYER_INFO[i])
        UDPSocket.sendto(bytes([PLAYER_INFO[i]]), server_address)
    print("[!]Connect successfull[!]")


Connect_to_server()

while True:
    data = bytes(input("Enter message to send or type 'exit': "), "utf-8")
    UDPSocket.sendto(data, server_address)
    if data == "exit":
        UDPSocket.close()
        os._exit(0)
        break
UDPSocket.close()
os._exit(0)
