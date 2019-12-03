import time
import random
import sys, pygame

import os
from socket import *

#TODO(bask): put frames counter using cpu clock
#TODO(bask): prevent a pixel from getting out of the borders
#TODO(bask): provide correct exit from the game
host = ""
server_addr = "192.168.0.108"  # set to IP address of target computer
send_data_port = 2323
recieve_data_port = 2424
buf = 1024
local_addr = (host, recieve_data_port)
target_addr = (server_addr, send_data_port)
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.bind(local_addr)


pygame.init()

SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT = 950, 640
CLEAR_SCREEN = 0, 0, 0
HERO_PIXEL_COLOR = 0, 0, 255
GAME_SCREEN = pygame.display.set_mode(SCREEN_SIZE)

GAME_IS_RUNNING = True

pixel_pos_x = 100
pixel_pos_y = 100
pixel_h = 50
pixel_w = 50

l_is_down = False
r_is_down = False
u_is_down = False
d_is_down = False


GAME_SCREEN.fill(CLEAR_SCREEN)

data = ""
x = 0
y = 0


def parse_position(data):
    x = ""
    y = ""
    separation_flag = False
    for i in str(data):
        if(separation_flag):
            y += i
            continue
        if(i == ","):
            separation_flag = True
            continue
        x += i
    return int(x), int(y)


print("Waiting to receive messages...")
while True:
    UDPSock.sendto(bytes("b", "utf-8"), target_addr)
    print("Received message: " + data)
    if(data == "exit"):
        print("IN GAME LOOP 1")
        UDPSock.close()
        os._exit(0)
        break
    else:
        print("IN GAME LOOP 2")
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RIGHT:
                    r_is_down = True
                if event.key == pygame.K_LEFT:
                    l_is_down = True
                if event.key == pygame.K_UP:
                    u_is_down = True
                if event.key == pygame.K_DOWN:
                    d_is_down = True
                if event.key == pygame.K_e:
                    GAME_IS_RUNNING = False
            if event.type == pygame.KEYUP:
                if event.key == pygame.K_RIGHT:
                    r_is_down = False
                if event.key == pygame.K_LEFT:
                    l_is_down = False
                if event.key == pygame.K_UP:
                    u_is_down = False
                if event.key == pygame.K_DOWN:
                    d_is_down = False
        print("IN GAME LOOP 3")
        if(not GAME_IS_RUNNING):
            UDPSock.sendto(bytes("exit", "utf-8"), target_addr)
            break
        if(l_is_down):
            pixel_pos_x -= 10
        if(r_is_down):
            pixel_pos_x += 10
        if(u_is_down):
            pixel_pos_y -= 10
        if(d_is_down):
            pixel_pos_y += 10

        print("IN GAME LOOP")

        #data = bytes("[ " + str(pixel_pos_x) + ", " + str(pixel_pos_y) + " ]", "utf-8")
        send_x = bytes(str(pixel_pos_x), "utf-8")
        send_y = bytes(str(pixel_pos_y), "utf-8")

        UDPSock.sendto(send_x + bytes(",", "utf-8") + send_y, target_addr)
        x, y = parse_position(data)
        GAME_SCREEN.fill(CLEAR_SCREEN)
        pygame.draw.rect(GAME_SCREEN, HERO_PIXEL_COLOR, [
                         pixel_pos_x + x, pixel_pos_y + y, pixel_w, pixel_h])
        pygame.display.flip()

    pygame.time.wait(16)
    #if(len(data) > 6):
    #    x = int(data[0] + data[1] + data[2])
    #    y = int(data[4] + data[5] + data[6])
    print(x, y)

    if data == "exit":
        break
UDPSock.close()
os._exit(0)
