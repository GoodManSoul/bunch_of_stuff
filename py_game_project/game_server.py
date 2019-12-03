import os
import time
import random
import sys
import pygame

from socket import *

SERVER_IS_RUNNING = True
server_shutdown_command = ""

server_host_ip = ""
server_recieve_port = 1497
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
    while 1:
        # if(len(PLAYER_1_MACHINE_ADDRESS) > 0 & len(PLAYER_2_MACHINE_ADDRESS) > 0):
        #     print("[!]All players has been connected[!]")
        #     break
        if(len(PLAYER_1_MACHINE_ADDRESS) == 0):
            print("[...]Waiting Player 1 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            PLAYER_1_MACHINE_ADDRESS = client_address
            new_data = int.from_bytes(recieved_data, "little")
            print(new_data)
            Get_player_info(recieved_data, 1)
            print("[*]Player 1 has been connected[*]")
            print("Player 1 ID: " + str(PLAYER_1_MACHINE_ADDRESS[1]))
            #print("Player 1 color: " + str(PLAYER_1_CUBE_COLOR))
        else:
            print("[...]Waiting Player 2 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            if(client_address[1] != PLAYER_1_MACHINE_ADDRESS[1]):
                PLAYER_2_MACHINE_ADDRESS = client_address
                print(recieved_data)
                Get_player_info(recieved_data, 2)
                print("[*]Player 2 has been connected[*]")
                print("Player 2 ID: " + str(PLAYER_2_MACHINE_ADDRESS[1]))
               # print("Player 2 color: " + str(PLAYER_2_CUBE_COLOR))

                print("[!]All players has been connected[!]")
                break
    return None

def Get_player_info(data, player_number):
    
    global PLAYER_1_MACHINE_ADDRESS
    global PLAYER_2_MACHINE_ADDRESS
    global PLAYER_1_INFO
    global PLAYER_2_INFO

    if(player_number == 1):
        
    if(player_number == 2):
        PLAYER_2_X = tuple(data[0])
    return None

Get_player_address()


while 1:
    (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
    print(PLAYER_1_X)
    print(PLAYER_2_X)
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
