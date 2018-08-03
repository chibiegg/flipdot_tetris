import pygame
from pygame.locals import *
from serial import Serial

SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480

pygame.joystick.init()
try:
    j = pygame.joystick.Joystick(0) # create a joystick instance
    j.init() # init instance
    print('Joystickの名称: ' + j.get_name())
    print('ボタン数 : ' + str(j.get_numbuttons()))
except pygame.error:
    print('Joystickが見つかりませんでした。')

def main():
    import sys
    port = sys.argv[1]
    serial = Serial(port, 19200)
    pygame.init()
    screen = pygame.display.set_mode( (SCREEN_WIDTH, SCREEN_HEIGHT) ) # 画面を作る
    pygame.display.set_caption('Joystick') # タイトル
    pygame.display.flip() # 画面を反映

    while 1:
        for e in pygame.event.get(): # イベントチェック
            if e.type == QUIT: # 終了が押された？
                return
            if (e.type == KEYDOWN and
                e.key  == K_ESCAPE): # ESCが押された？
                return
            # Joystick関連のイベントチェック
            elif e.type == pygame.locals.JOYBALLMOTION: # 8
                print('ball motion', e)

            elif e.type == pygame.locals.JOYHATMOTION: # 9
                print('hat motion', e)
                value = e.value
                if value[0] == 1:
                    # Right
                    print("d")
                    serial.write('d'.encode("ascii"))
                if value[0] == -1:
                    # Left
                    print("a")
                    serial.write('a'.encode("ascii"))
                if value[1] == 1:
                    # Up
                    print("w")
                    serial.write('w'.encode("ascii"))
                if value[1] == -1:
                    # Down
                    print("s")
                    serial.write('s'.encode("ascii"))


            elif e.type == pygame.locals.JOYBUTTONDOWN: # 10
                print(str(e.button)+'番目のボタンが押された')
                if e.button == 0:
                    print("p")
                    serial.write('p'.encode("ascii"))

            elif e.type == pygame.locals.JOYBUTTONUP: # 11
                print(str(e.button)+'番目のボタンが離された')

if __name__ == '__main__':
    main()
