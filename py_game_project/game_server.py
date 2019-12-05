import os
import time
import random
import sys
import pygame

from socket import *

SERVER_IS_RUNNING = True
server_shutdown_command = ""

server_host_ip = ""
server_recieve_port = 1500
server_data_buffer = 4096

server_address = (server_host_ip, server_recieve_port)

UDPSocket = socket(AF_INET, SOCK_DGRAM)
UDPSocket.bind(server_address)
##########################################################
PLAYERS_COUNT = 2

PLAYER_1_MACHINE_ADDRESS = []
PLAYER_2_MACHINE_ADDRESS = []

PLAYER_1_INFO = PLAYER_1_X, PLAYER_1_Y, PLAYER_1_W, PLAYER_1_H, PLAYER_1_CUBE_COLOR_R, PLAYER_1_CUBE_COLOR_G, PLAYER_1_CUBE_COLOR_B = 0, 0, 0, 0, 0, 0, 0
PLAYER_2_INFO = PLAYER_2_X, PLAYER_2_Y, PLAYER_2_W, PLAYER_2_H, PLAYER_2_CUBE_COLOR_R, PLAYER_2_CUBE_COLOR_G, PLAYER_2_CUBE_COLOR_B = 0, 0, 0, 0, 0, 0, 0

# PLAYER_1_CUBE_COLOR = 255, 255, 255
# PLAYER_2_CUBE_COLOR = 255, 255, 255

# PLAYER_1_X = 0
# PLAYER_1_Y = 0
# PLAYER_1_W = 0
# PLAYER_1_H = 0

# PLAYER_2_X = 0
# PLAYER_2_Y = 0
# PLAYER_2_W = 0
# PLAYER_2_H = 0
##########################################################


def Get_player_address():
    global PLAYER_1_MACHINE_ADDRESS
    global PLAYER_2_MACHINE_ADDRESS
    global PLAYER_1_INFO
    global PLAYER_2_INFO
    while 1:
        # if(len(PLAYER_1_MACHINE_ADDRESS) > 0 & len(PLAYER_2_MACHINE_ADDRESS) > 0):
        #     print("[!]All players has been connected[!]")
        #     break
        if(len(PLAYER_1_MACHINE_ADDRESS) == 0):
            print("[...]Waiting Player 1 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            PLAYER_1_MACHINE_ADDRESS = client_address
            Get_player_info(1)
            print(PLAYER_1_INFO)
            print("[*]Player 1 has been connected[*]")
            print("Player 1 ID: " + str(PLAYER_1_MACHINE_ADDRESS[1]))
        else:
            print("[...]Waiting Player 2 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            if(client_address[1] != PLAYER_1_MACHINE_ADDRESS[1]):
                PLAYER_2_MACHINE_ADDRESS = client_address
                Get_player_info(2)
                print(PLAYER_2_INFO)
                print("[*]Player 2 has been connected[*]")
                print("Player 2 ID: " + str(PLAYER_2_MACHINE_ADDRESS[1]))
        
                print("[!]All players has been connected[!]")
                break
    return None

def Get_player_info(player_number):  
    global PLAYER_1_INFO
    global PLAYER_2_INFO

    player_1_list = list(PLAYER_1_INFO)
    player_2_list = list(PLAYER_2_INFO)

    recieved_data = bytes(1)
    if(player_number == 1):
        for i in range (len(player_1_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_1_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_1_INFO = tuple(player_1_list)
    if(player_number == 2): 
        for i in range(len(player_2_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_2_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_2_INFO = tuple(player_2_list)



Get_player_address()
while 1:
    (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
    print(PLAYER_1_INFO)
    print(PLAYER_2_INFO)
    recieved_data = str(recieved_data, "utf-8")
    if(recieved_data == "exit"):
        print("[!]SERVER HAS BEEN STOPED[!]")
        UDPSocket.close()
        os._exit(0)
        break
    else:
        print("CLIENT address: " + str(client_address))
        print("CLIENT says: " + recieved_data)

UDPSocket.close()
os._exit(0)
