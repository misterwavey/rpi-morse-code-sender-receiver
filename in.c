#include <bcm2835.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


#define PIN RPI_GPIO_P1_11 /*GPIO 17 = real pin position 11*/

void decodeLetter(char *letter) {
	if(strcmp(letter, ".----.") == 0) {
		printf("'");	
	} else if(strcmp(letter, "-.--.-") == 0) {
		printf("(");
	} else if(strcmp(letter, "-.--.-") == 0) {
		printf(")");
	} else if(strcmp(letter, "--..--") == 0) {
		printf(",");
	} else if(strcmp(letter, "-....-") == 0) {
		printf("-");
	} else if(strcmp(letter, ".-.-.-") == 0) {
		printf(".");
	} else if(strcmp(letter, "-..-.") == 0) {
		printf("/");
	} else if(strcmp(letter, "---...") == 0) {
		printf(":");
	} else if(strcmp(letter, "-.-.-.") == 0) {
		printf(";");
	} else if(strcmp(letter, "..--..") == 0) {
		printf("?");
	} else if(strcmp(letter, "..--.-") == 0) {
		printf("_");
	} else if(strcmp(letter, "-----") == 0) {
		printf("0");
	} else if(strcmp(letter, ".----") == 0) {
		printf("1");
	} else if(strcmp(letter, "..---") == 0) {
		printf("2");
	} else if(strcmp(letter, "...--") == 0) {
		printf("3");
	} else if(strcmp(letter, "....-") == 0) {
		printf("4");
	} else if(strcmp(letter, ".....") == 0) {
		printf("5");
	} else if(strcmp(letter, "-....") == 0) {
		printf("6");
	} else if(strcmp(letter, "--...") == 0) {
		printf("7");
	} else if(strcmp(letter, "---..") == 0) {
		printf("8");
	} else if(strcmp(letter, "----.") == 0) {
		printf("9");
	} else if(strcmp(letter, ".-") == 0) {
		printf("A");
	} else if(strcmp(letter, "-...") == 0) {
		printf("B");
	} else if(strcmp(letter, "-.-.") == 0) {
		printf("C");
	} else if(strcmp(letter, "-..") == 0) {
		printf("D");
	} else if(strcmp(letter, ".") == 0) {
		printf("E");
	} else if(strcmp(letter, "..-.") == 0) {
		printf("F");
	} else if(strcmp(letter, "--.") == 0) {
		printf("G");
	} else if(strcmp(letter, "....") == 0) {
		printf("H");
	} else if(strcmp(letter, "..") == 0) {
		printf("I");
	} else if(strcmp(letter, ".---") == 0) {
		printf("J");
	} else if(strcmp(letter, "-.-") == 0) {
		printf("K");
	} else if(strcmp(letter, ".-..") == 0) {
		printf("L");
	} else if(strcmp(letter, "--") == 0) {
		printf("M");
	} else if(strcmp(letter, "-.") == 0) {
		printf("N");
	} else if(strcmp(letter, "---") == 0) {
		printf("O");
	} else if(strcmp(letter, ".--.") == 0) {
		printf("P");
	} else if(strcmp(letter, "--.-") == 0) {
		printf("Q");
	} else if(strcmp(letter, ".-.") == 0) {
		printf("R");
	} else if(strcmp(letter, "...") == 0) {
		printf("S");
	} else if(strcmp(letter, "-") == 0) {
		printf("T");
	} else if(strcmp(letter, "..-") == 0) {
		printf("U");
	} else if(strcmp(letter, "...-") == 0) {
		printf("V");
	} else if(strcmp(letter, ".--") == 0) {
		printf("W");
	} else if(strcmp(letter, "-..-") == 0) {
		printf("X");
	} else if(strcmp(letter, "-.--") == 0) {
		printf("Y");
	} else if(strcmp(letter, "--..") == 0) {
		printf("Z");
	}
}

void decodeWord(char word[]) {
	char cpy[1024];
	strcpy(cpy, word);

//	printf("word '%s' (%i)\n", cpy, strlen(cpy));
	char delims[] = "#";
	char *letter = NULL;
	letter = strtok(cpy, delims);
	while(letter != NULL) {
		decodeLetter(letter);
		letter = strtok(NULL, delims);
	}
	printf(" ");
}

void decode(char msg[]) {
	char cpy[1024];
	strcpy(cpy, msg);
//	printf("msg: '%s' (%i)\n", cpy, strlen(cpy));

	char delims[] = " ";
	char *word = NULL;
	char *end_str;

	word = strtok_r(cpy, delims, &end_str);
	while(word != NULL) {
		decodeWord(word);
		word = strtok_r(NULL, delims, &end_str);
	}
	printf("\n");
}

int main(int argc, char**argv) {

	struct timeval tv;
	long secs;
	long tics;
	long litStartTime;
	long litEndTime;
	char msgBuf[100];
	int idx = 0;
	long litDuration;
	long pauseDuration;

	msgBuf[99] = '\0';

	if(!bcm2835_init()) {
 		return 1;
	}

	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_DOWN);
		
	printf("watching...\n");

	while(1) {
		if(bcm2835_gpio_lev(PIN) == HIGH) {
			gettimeofday(&tv, NULL);
			secs = tv.tv_sec;
			tics = tv.tv_usec;
			litStartTime = (secs * 1000000) + tics; 
			if(litEndTime) {
				pauseDuration = litStartTime - litEndTime; 
				//printf("pause between lights: %ld\n", pauseDuration);

				if(pauseDuration > 900000) {
					decode(msgBuf);
					idx = 0; // reset
				} else if(pauseDuration > 400000) {
					msgBuf[idx++] = ' '; // new word 
				} else if(pauseDuration > 100000) {
					msgBuf[idx++] = '#'; // new letter
				}
			}
			while(bcm2835_gpio_lev(PIN) == HIGH);
			gettimeofday(&tv, NULL);
			secs = tv.tv_sec;
			tics = tv.tv_usec;
			litEndTime = (secs * 1000000) + tics; 
			litDuration = litEndTime - litStartTime;
			//printf("Lit duration: %ld usec\n", litDuration );
			if(litDuration > 100000) {
				msgBuf[idx++] = '-';
			} else { 
				msgBuf[idx++] = '.';
			}
			msgBuf[idx] = '\0';
		}
		delay(1);
	}
}

