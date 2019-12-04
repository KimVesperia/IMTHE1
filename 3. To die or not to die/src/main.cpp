/**
* Opdracht 3: To die or not to die
* Dobbelsteen met 6 (of9) leds, druk op de knop voor een
* random getal op de dobbelsteen in de vorm van led lichten
*
* Auteur: Kim Phung | S1102710
* Versie: 2.0
* Aangemaakt: 4 oktober 2019
* Laatste wijziging: 20 oktober 2019
*/
#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>

//knop begint op false
bool pressed = false;
//led beginnen uit
int power = 0;

int main(void) {

  //D en B registers aan voor de leds(output)
  DDRD = 0xFF;
  DDRB = 0xFF;

  //Button aan
  PORTC|= 1 << PC0;

  while(1) {
    //knop is niet ingedrukt
    if(!(PINC& 1<<PC0)) {
      //delay voor het dender gedrag
      _delay_ms(50);
      //check again
      if(!(PINC& 1<<PC0)) {
        //Als je tot hier komt dan..
        if(!pressed) {
          //..ingedrukt!
          pressed = true;

          if (pressed == true) {
            //kleine rng functie variable tussen 1 en 6
            int randomNumber = (rand() % 6) + 1;

            //checkt of een led al brandt en zet hem uit anders direct in de else
            if (power == 1) {
              //off
              PORTD = 0x00;
              PORTB = 0x00;
              //power off
              power = 0;
            } else {
                //als de leds uit staan kom je hierin
                //via deze if word de correcte aantal leds aangestuurd en alleen als ze al uit zijn
                if (randomNumber == 1 & power == 0) {
                  //middelste led voor number 1
                  PORTD ^= (1 << PD3);
                  //power on
                  power = 1;
                }

                if (randomNumber == 2 & power == 0) {
                  //links boven en rechts onder voor number 2
                  PORTD ^= (1 << PD5);
                  PORTB ^= (1 << PB4);
                  //power on
                  power = 1;
                }

                if (randomNumber == 3 & power == 0) {
                  //links boven, middelste en rechts onder voor number 3
                  PORTD ^= (1 << PD3) | (1 << PD5);
                  PORTB ^= (1 << PB4);
                  //power on
                  power = 1;
                }

                if (randomNumber == 4 & power == 0) {
                  //alle 4 leds bij de hoeken voor number 4
                  PORTD ^= (1 << PD5) | (1 << PD7);
                  PORTB ^= (1 << PB2) | (1 << PB4);
                  //power on
                  power = 1;
                }

                if (randomNumber == 5 & power == 0) {
                  //alle 4 leds bij de hoeken en de middelste voor number 5
                  PORTD ^= (1 << PD3) | (1 << PD5) | (1 << PD7);
                  PORTB ^= (1 << PB2) | (1 << PB4);
                  //power on
                  power = 1;
                }

                if (randomNumber == 6 & power == 0) {
                  //6 leds pinnen aan, bij mij opstelling linker en rechter kolom
                  PORTD ^= (1 << PD2) | (1 << PD4) | (1 << PD5) | (1 << PD7);
                  PORTB ^= (1 << PB2) |(1 << PB4);
                  //power on
                  power = 1;
                }

            }
          }
        }
      }
    }
    else {
      //knop niet ingedrukt
      pressed = false;
    }
  }
  return 0;
}
