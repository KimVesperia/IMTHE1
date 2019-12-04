/**
* Opdracht 1: Blink once to accept
* 2 led lampjes knipperen om en om
*
* Auteur: Kim Phung | S1102710
* Versie: 2.0
* Aangemaakt: 1 oktober 2019
* Laatste wijziging: 20 oktober 2019
*/
#include<avr/io.h>
#include<util/delay.h>

int main(void) {
  //Hele B register aanzetten als output. Niet echt nodig om alles aan te zetten, maar voor deze opdracht maakt niet echt uit
  //PB5 en PB4 zitten de ledjes
  DDRB = 0xFF;

  while(1) {
    //bitshift een 1 naar PB5
    PORTB = (1 << PB5);
    //1seconden delay
    _delay_ms(1000);
    //bitshift een 1 naar PB4
    PORTB = (1 << PB4);
    //1seconden delay
    _delay_ms(1000);
  }
  return 0;
}
