/**
* Opdracht 4: ADC baby
* Speaker speelt een geluid tussen de 100hz en 10000hz, stel in met potmeter
*
* Auteur: Kim Phung | S1102710
* Versie: 2.0
* Aangemaakt: 2 oktober 2019
* Laatste wijziging: 20 oktober 2019
*/
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//initialise potentiometer
void initADC0(void) {
  //REFSn: Atmega pagina 317
  /*These bits select the voltage reference for the ADC. If these bits are changed during a conversion, the
  change will not go in effect until this conversion is complete (ADIF in ADCSRA is set). The internal
  voltage reference options may not be used if an external reference voltage is being applied to the AREF
  pin.*/
  //5v
  ADMUX = (1 << REFS0);

  //ADCSRA-ADPSn: Atmega pagina 319
  //These bits determine the division factor between the system clock frequency and the input clock to the ADC.
  //Division Factor 128 door ADPS[2:0] op 111
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  //ADCSRA-ADEN: Atmega pagina 319
  //Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. Turning the ADC off while a conversion is in progress, will terminate this conversion.
  //enable ADC bit
  ADCSRA |= (1 << ADEN);
}

//get ADC readings
uint16_t getADC() {
  //Atmega pagina 319
  //ADSC op 1 = ADC Start Conversion
  ADCSRA |= (1 << ADSC);
  //loop tot het klaar is
  loop_until_bit_is_clear(ADCSRA, ADSC);
  //Return ADC Waarde
  return ADC;
}

//Delay functie, want default delay werken niet met variabelen
void delay(uint16_t ms) {
  for(uint16_t i = 0; i < ms; i++) {
    _delay_ms(1);
  }
}

int main(void) {
  //B register voor de speaker
  DDRB |= (1 << PB0);
  //start functie
  initADC0();

  while(1) {
    //Read the ADC value and set variable
    uint16_t adcValue = getADC();
    //Speaker op D8 (PB0) aanzetten
    PORTB |= (1 << PB0);
    //100 microseconden = 10000hz
    //Converter: https://www.unitjuggler.com/convert-frequency-from-Hz-to-%C2%B5s(p).html?val=10000
    _delay_us(100);
    //Speaker uitzetten
    PORTB &= ~(1 << PB0);
    //Eigen delay functie, anders werken variabelen niet.
    //10 milliseconden = 100hz
    //Converter: https://www.unitjuggler.com/convert-frequency-from-Hz-to-ms(p).html?val=100
    //adcValue heeft een max waarde van 1023
    //Deel adcValue met 102.3 om 10ms(100hz) te krijgen
    delay(adcValue / 102.3);
  }
  return 0;
}
