import sys
import time
import os

timeMultiplier = 5

DOT_TIME = 0.01 * timeMultiplier
DASH_TIME = DOT_TIME * 3
SPACE_TIME = DASH_TIME * 2
PAUSE_TIME = DASH_TIME 
CODE = {' ': ' ', "'": '.----.', 
        '(': '-.--.-', ')': '-.--.-', ',': '--..--', '-': '-....-', 
        '.': '.-.-.-', '/': '-..-.', '0': '-----', '1': '.----', 
        '2': '..---', '3': '...--', '4': '....-', '5': '.....', 
        '6': '-....', '7': '--...', '8': '---..', '9': '----.', 
        ':': '---...', ';': '-.-.-.', '?': '..--..', 'A': '.-', 
        'B': '-...', 'C': '-.-.', 'D': '-..', 'E': '.', 
        'F': '..-.', 'G': '--.', 'H': '....', 'I': '..', 
        'J': '.---', 'K': '-.-', 'L': '.-..', 'M': '--', 
        'N': '-.', 'O': '---', 'P': '.--.', 'Q': '--.-', 
        'R': '.-.', 'S': '...', 'T': '-', 'U': '..-', 
        'V': '...-', 'W': '.--', 'X': '-..-', 'Y': '-.--', 
        'Z': '--..', '_': '..--.-'} 

def morseDot(): 
    os.system("echo 1 > /sys/class/leds/led0/brightness")
    time.sleep(DOT_TIME)
    os.system("echo 0 > /sys/class/leds/led0/brightness")

def morseDash():
    os.system("echo 1 > /sys/class/leds/led0/brightness")
    time.sleep(DASH_TIME)
    os.system("echo 0 > /sys/class/leds/led0/brightness")

def morseSpace():
    time.sleep(SPACE_TIME)

def morseOut(morseLetter):
    for letter in morseLetter:
        if letter == '.':
            morseDot()
        elif letter == '-':
            morseDash()
        elif letter == ' ':
            morseSpace()
        else:
            print('error')
        time.sleep(DOT_TIME)

def convertStringToMorse(msg):
    print '> '+msg
    for letter in msg:
        morseLetter = CODE[letter.upper()]
        morseOut(morseLetter)
        sys.stdout.write(letter)
        sys.stdout.flush()
        time.sleep(PAUSE_TIME)
    sys.stdout.write('\n')
    sys.stdout.flush()

def cleanup():
    os.system("echo mmc0 > /sys/class/leds/led0/trigger")

def setup():
    os.system("echo none > /sys/class/leds/led0/trigger")

if __name__ == "__main__":
    try:
        setup()
        if len(sys.argv[1:]) != 0:
            words =  ' '.join(sys.argv[1:])
            convertStringToMorse(words)
        else:
            words =  sys.stdin.read().replace('\n','  ')
            convertStringToMorse(words)
        cleanup()
    except KeyboardInterrupt:
        cleanup()
