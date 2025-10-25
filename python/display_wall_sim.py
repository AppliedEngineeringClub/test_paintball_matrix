import pygame
from pymathlib import util

VIEW_WIDTH = 800 # pixels
VIEW_HEIGHT = 600 # pixesl

util.width = VIEW_WIDTH
util.height = VIEW_HEIGHT

CANVAS_WIDTH = 3 # meters
CANVAS_HEIGHT = 3 # meters

PAINTBALL_RADIUS = 0.017272 # meters
PAINTBALL_SPLATTER_RADIUS = 0.02 # meters

METERS_PER_PIXEL = VIEW_WIDTH / CANVAS_WIDTH

BACKGROUND_COLOR = (255, 255, 255)

screen = pygame.display.set_mode((VIEW_WIDTH, VIEW_HEIGHT))
pygame.display.set_caption("Wall Simulation")

keep_alive = True
clock = pygame.time.Clock()

while keep_alive:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            keep_alive = False

    screen.fill(BACKGROUND_COLOR)
    # pygame.draw.rect(screen, (0, 0, 200, 200))
    center = util.native_to_cartesian(0, 0)
    pygame.draw.circle(screen, (255, 0, 0), center, 40)

    pygame.display.flip()

    clock.tick(60)

pygame.quit()