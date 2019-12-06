import os
import time
import random
import sys
import pygame

from socket import *

SERVER_IS_RUNNING = True
server_shutdown_command = ""

server_host_ip = ""
server_recieve_port = 1546
server_data_buffer = 4096

server_address = (server_host_ip, server_recieve_port)


UDPSocket = socket(AF_INET, SOCK_DGRAM)
UDPSocket.bind(server_address)
##########################################################
PLAYERS_COUNT = 2

PLAYER_1_MACHINE = []
PLAYER_1_RECIEVE_PORT = 4030
PLAYER_1_ADDRESS = ()

PLAYER_1_WAITING_STATUS = False

##########################################################

PLAYER_2_MACHINE = []
PLAYER_2_RECIEVE_PORT = 4031
PLAYER_2_ADDRESS = ()

PLAYER_2_WAITING_STATUS = False

##########################################################

PLAYER_1_INFO = PLAYER_1_X, PLAYER_1_Y, PLAYER_1_W, PLAYER_1_H, PLAYER_1_CUBE_COLOR_R, PLAYER_1_CUBE_COLOR_G, PLAYER_1_CUBE_COLOR_B = 0, 0, 0, 0, 0, 0, 0
PLAYER_2_INFO = PLAYER_2_X, PLAYER_2_Y, PLAYER_2_W, PLAYER_2_H, PLAYER_2_CUBE_COLOR_R, PLAYER_2_CUBE_COLOR_G, PLAYER_2_CUBE_COLOR_B = 0, 0, 0, 0, 0, 0, 0

PLAYER_1_POSITION = PLAYER_1_X, PLAYER_1_Y
PLAYER_2_POSITION = PLAYER_2_X, PLAYER_2_Y

PLAYER_1_CUBE_COLOR = 255, 255, 255
PLAYER_2_CUBE_COLOR = 255, 255, 255
##########################################################


def Get_player_address():
    global PLAYER_1_MACHINE
    global PLAYER_2_MACHINE
    global PLAYER_1_ADDRESS
    global PLAYER_2_ADDRESS

    global PLAYER_1_INFO
    global PLAYER_2_INFO
    while 1:
        # if(len(PLAYER_1_MACHINE) > 0 & len(PLAYER_2_MACHINE
        # ) > 0):
        #     print("[!]All players has been connected[!]")
        #     break
        if(len(PLAYER_1_MACHINE) == 0):
            print("[...]Waiting Player 1 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            PLAYER_1_MACHINE = client_address
            PLAYER_1_ADDRESS = str(PLAYER_1_MACHINE[0]), PLAYER_1_RECIEVE_PORT
            Get_player_info(1)
            print(PLAYER_1_ADDRESS)
            print("[*]Player 1 has been connected[*]")
            print("Player 1 ID: " + str(PLAYER_1_MACHINE[1]))
        else:
            print("[...]Waiting Player 2 to connect[...]")
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            if(client_address[1] != PLAYER_1_MACHINE[1]):
                PLAYER_2_MACHINE = client_address
                PLAYER_2_ADDRESS = str(
                    PLAYER_2_MACHINE[0]), PLAYER_2_RECIEVE_PORT
                Get_player_info(2)
                print("[*]Player 2 has been connected[*]")
                print("Player 2 ID: " + str(PLAYER_2_MACHINE[1]))

                print("[!]All players has been connected[!]")
                break
    return None


def Get_player_info(player_number):
    global PLAYER_1_INFO
    global PLAYER_2_INFO

    player_1_list = list(PLAYER_1_INFO)
    player_2_list = list(PLAYER_2_INFO)

    if(player_number == 1):
        for i in range(len(player_1_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_1_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_1_INFO = tuple(player_1_list)
    if(player_number == 2):
        for i in range(len(player_2_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_2_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_2_INFO = tuple(player_2_list)


def Get_player_position(player_number):
    global PLAYER_1_INFO
    global PLAYER_2_INFO
    global PLAYER_1_POSITION
    global PLAYER_2_POSITION

    player_1_list = list(PLAYER_1_POSITION)
    player_2_list = list(PLAYER_2_POSITION)

    if(player_number == 1):
        for i in range(len(player_1_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_1_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_1_POSITION = tuple(player_1_list)
        print(PLAYER_1_POSITION)
    if(player_number == 2):
        for i in range(len(player_2_list)):
            (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
            player_2_list[i] = int.from_bytes(recieved_data, "little")
        PLAYER_2_POSITION = tuple(player_2_list)


def Set_client_status(player_number, status):
    global PLAYER_1_WAITING_STATUS
    global PLAYER_2_WAITING_STATUS

    if(player_number == 1):
        if(status == "wait"):
            PLAYER_1_WAITING_STATUS = True
        else:
            PLAYER_1_WAITING_STATUS = False
        print("t_send")    
        UDPSocket.sendto(bytes(PLAYER_1_WAITING_STATUS), PLAYER_1_ADDRESS)
        print("success_send")
    else:
        if(status == "wait"):
            PLAYER_2_WAITING_STATUS = True
        else:
            PLAYER_2_WAITING_STATUS = False
        UDPSocket.sendto(bytes(PLAYER_2_WAITING_STATUS), PLAYER_2_ADDRESS)

Get_player_address()
Set_client_status(1, "wait")
Set_client_status(2, "sss")
while 1:

    (recieved_data, client_address) = UDPSocket.recvfrom(server_data_buffer)
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
