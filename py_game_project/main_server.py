import os
from socket import *
host = ""
client_address = "192.168.0.104"
recieve_data_port = 13040
send_data_port = 13041
buf = 1024
local_addr = (host, recieve_data_port)
target_addr = (client_address, send_data_port)
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.bind(local_addr)
UDPSock.bind(target_addr)

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


GAME_SCREEN.fill(CLEAR_SCREEN)

data = []
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


print "Waiting to receive messages..."
while True:
    (data, addr) = UDPSock.recvfrom(buf)
    print "Received message: " + data
    if(data == "exit"):
        UDPSock.close()
        os._exit(0)
        break
    else:
        x, y = parse_position(data)
        GAME_SCREEN.fill(CLEAR_SCREEN)
        pygame.draw.rect(GAME_SCREEN, HERO_PIXEL_COLOR, [pixel_pos_x + x, pixel_pos_y + y, pixel_w, pixel_h])
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
