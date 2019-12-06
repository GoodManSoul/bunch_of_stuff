import os
import time
import random
import sys
import pygame

from socket import *

client_ip = ""
client_recieve_port = 4031
client_data_buffer = 4096

client_address = (client_ip, client_recieve_port)
print(client_address)
UDPSocket = socket(AF_INET, SOCK_DGRAM)
UDPSocket.bind(client_address)

server_ip = "192.168.0.108"
server_recieve_port = 1546

server_address = (server_ip, server_recieve_port)


SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT = 950, 640
CLEAR_SCREEN = 0, 0, 0


PLAYER_INFO = PLAYER_X, PLAYER_Y, PLAYER_W, PLAYER_H, COLOR_R, COLOR_G, COLOR_B = 120, 10, 5, 5, 255, 255, 255


def Connect_to_server():
    global PLAYER_INFO
    print("[...]Connecting to server[...]")
    UDPSocket.sendto(bytes("HELLO", "utf-8"), server_address)
    for i in range (len(PLAYER_INFO)):
        print(PLAYER_INFO[i])
        UDPSocket.sendto(bytes([PLAYER_INFO[i]]), server_address)
    print("[!]Connect successfull[!]")

def Check_status():
    print("RECV_STATUS")
    (recieved_data, incoming_ip) = UDPSocket.recvfrom(client_data_buffer)
    recieved_data = bool(recieved_data)
    if(recieved_data):
        print("WAIT_STATUS_RECIEVED")
    else:
        print("STILL_RUNNING...")
    print("CHECK_STATUS")

def Send_player_position():
    global PLAYER_INFO
    UDPSocket.sendto(bytes([PLAYER_X]), server_address)
    UDPSocket.sendto(bytes([PLAYER_Y]), server_address)

Connect_to_server()
Check_status()


while True:
    data = bytes(input("Enter message to send or type 'exit': "), "utf-8")
    UDPSocket.sendto(data, server_address)
    if data == "exit":
        UDPSocket.close()
        os._exit(0)
        break
UDPSocket.close()
os._exit(0)
