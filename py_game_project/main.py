import time
import random
import sys, pygame

#TODO(bask): put frames counter using cpu clock
#TODO(bask): prevent a pixel from getting out of the borders

pygame.init()

SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT = 950, 640
CLEAR_SCREEN = 0, 0, 0
HERO_PIXEL_COLOR = 255, 170, 0
GAME_SCREEN = pygame.display.set_mode(SCREEN_SIZE)

pixel_pos_x = 10
pixel_pos_y = 10
pixel_h = 50
pixel_w = 50


GAME_SCREEN.fill(CLEAR_SCREEN)

l_is_down = False
r_is_down = False
u_is_down = False
d_is_down = False

while 1:
   
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
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_RIGHT:
                r_is_down = False
            if event.key == pygame.K_LEFT:
                l_is_down = False
            if event.key == pygame.K_UP:
                u_is_down = False
            if event.key == pygame.K_DOWN:
                d_is_down = False

    if(l_is_down):
        pixel_pos_x -= 10
    if(r_is_down):
        pixel_pos_x += 10
    if(u_is_down):
        pixel_pos_y -= 10
    if(d_is_down):
        pixel_pos_y += 10

    GAME_SCREEN.fill(CLEAR_SCREEN)
    pygame.draw.rect(GAME_SCREEN, HERO_PIXEL_COLOR, [pixel_pos_x, pixel_pos_y, pixel_w, pixel_h])
    #rand_color = random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)
    #GAME_SCREEN.fill(rand_color)
    pygame.display.flip()

        
    pygame.time.wait(16)

pygame.quit()
