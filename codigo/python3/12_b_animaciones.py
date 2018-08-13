# Programa adaptado de: http://inventwithpython.com/chapter17.html

import time
import sys
import pygame
from pygame.locals import QUIT

# set up pygame
pygame.init()

# set up the window
WINDOWWIDTH  = 500
WINDOWHEIGHT = 400
windowSurface = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
pygame.display.set_caption('Animation')

# set up direction variables (mire el teclado numérico!!!)
DOWNLEFT  = 1
DOWNRIGHT = 3
UPLEFT    = 7
UPRIGHT   = 9

MOVESPEED = 4 # pixeles/frame

# set up the colors
BLACK = (  0,   0,   0)
RED   = (255,   0,   0)
GREEN = (  0, 255,   0)
BLUE  = (  0,   0, 255)

# set up the block data structure
b1 = {'rect':pygame.Rect(300, 80, 50, 100), 'color':RED,   'dir':UPRIGHT}
b2 = {'rect':pygame.Rect(200, 200, 20, 20), 'color':GREEN, 'dir':UPLEFT}
b3 = {'rect':pygame.Rect(100, 150, 60, 60), 'color':BLUE,  'dir':DOWNLEFT}
blocks = [b1, b2, b3]

# run the game loop
while True:
    # check for the QUIT event
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    # draw the black background onto the surface
    windowSurface.fill(BLACK)

    for b in blocks:
        # move the block data structure
        if b['dir'] == DOWNLEFT:
            b['rect'].left -= MOVESPEED
            b['rect'].top += MOVESPEED
        elif b['dir'] == DOWNRIGHT:
            b['rect'].left += MOVESPEED
            b['rect'].top += MOVESPEED
        elif b['dir'] == UPLEFT:
            b['rect'].left -= MOVESPEED
            b['rect'].top -= MOVESPEED
        elif b['dir'] == UPRIGHT:
            b['rect'].left += MOVESPEED
            b['rect'].top -= MOVESPEED

        # check if the block has move out of the window
        if b['rect'].top < 0:
            # block has moved past the top
            if b['dir'] == UPLEFT:    b['dir'] = DOWNLEFT
            if b['dir'] == UPRIGHT:   b['dir'] = DOWNRIGHT
        if b['rect'].bottom > WINDOWHEIGHT:
            # block has moved past the bottom
            if b['dir'] == DOWNLEFT:  b['dir'] = UPLEFT
            if b['dir'] == DOWNRIGHT: b['dir'] = UPRIGHT
        if b['rect'].left < 0:
            # block has moved past the left side
            if b['dir'] == DOWNLEFT:  b['dir'] = DOWNRIGHT
            if b['dir'] == UPLEFT:    b['dir'] = UPRIGHT
        if b['rect'].right > WINDOWWIDTH:
            # block has moved past the right side
            if b['dir'] == DOWNRIGHT: b['dir'] = DOWNLEFT
            if b['dir'] == UPRIGHT:   b['dir'] = UPLEFT

        # draw the block onto the surface
        pygame.draw.rect(windowSurface, b['color'], b['rect'])

    # draw the window onto the screen
    pygame.display.update()
    time.sleep(0.02) # stop for 20 miliseconds
