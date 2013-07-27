import RPi.GPIO as GPIO
import sys
import time

timeMultiplier = 10
pinNum = 12

DOT_TIME = 0.01 * timeMultiplier
DASH_TIME = DOT_TIME * 3
SPACE_TIME = DASH_TIME * 2
PAUSE_TIME = DASH_TIME 

GPIO.setmode(GPIO.BOARD) #numbering scheme that corresponds to breakout board and pin layout
GPIO.setup(pinNum, GPIO.OUT) #replace pinNum with whatever pin you used, this sets up that pin as an output

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
    GPIO.output(pinNum, GPIO.HIGH)
    time.sleep(DOT_TIME)
    GPIO.output(pinNum, GPIO.LOW)

def morseDash():
    GPIO.output(pinNum, GPIO.HIGH)
    time.sleep(DASH_TIME)
    GPIO.output(pinNum, GPIO.LOW)

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

if __name__ == "__main__":
    try:
        if len(sys.argv[1:]) != 0:
            words =  ' '.join(sys.argv[1:])
            convertStringToMorse(words)
        else:
            words =  sys.stdin.read().replace('\n','  ')
            convertStringToMorse(words)
        GPIO.cleanup()
    except KeyboardInterrupt:
        GPIO.cleanup()
