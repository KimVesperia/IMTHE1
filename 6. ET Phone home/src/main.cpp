/**
* Opdracht 6: ET Phone home
* LED Display toont naam + studentnummer. Maakt gebruik van de HD44780 library
*
* Auteur: Kim Phung | S1102710
* Versie: 2.0
* Aangemaakt: 6 oktober 2019
* Laatste wijziging: 20 oktober 2019
*/
#include <avr/io.h>
#include <util/delay.h>
//library is included in the same folder
//andere instellingen en comments in hd44780_settings.h
#include "hd44780.h"

int main(void) {

	while(1) {
		//Library codes
		//init the display
  	lcd_init();
		//clear the screen
    lcd_clrscr();
		//String zetten output
    lcd_puts("Kim Phung");
		//To move the cursor to a specific location:
		//0x40 is often the beginning of the second line
    lcd_goto(0x40);
		//String zetten output
    lcd_puts("S1102710");
	}
	return 0;
}
