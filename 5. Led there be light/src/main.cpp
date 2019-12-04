/**
* Opdracht 5: Led there be light
* Druk 'r', 'g' of 'b' in om de kleur van de RGB led te veranderen
*
* Auteur: Kim Phung | S1102710
* Versie: 2.0
* Aangemaakt: 10 oktober 2019
* Laatste wijziging: 20 oktober 2019
*/
#define F_CPU 16000000UL
#define BAUD 9600

#define PORT_RED PB1
#define PORT_GREEN PB2
#define PORT_BLUE PB3

#define RED OCR1A
#define GREEN OCR1B
#define BLUE OCR2A

#include <avr/delay.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

//Seriele communicatie start
void initUSART(void) {

  //BAUDRATE registers worden met de juiste waarde berekend
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  //enable usart
  //Atmega pagina 247
  //UCSR0B-TXEN0:
  /*Writing this bit to one enables the USART Transmitter. The Transmitter will override normal port operation
  for the TxD0 pin when enabled. The disabling of the Transmitter (writing TXEN0 to zero) will not become
  effective until ongoing and pending transmissions are completed, i.e., when the Transmit Shift Register
  and Transmit Buffer Register do not contain data to be transmitted. When disabled, the Transmitter will no
  longer override the TxD0 port.*/
  //UCSR0B-RXEN0:
  /*Writing this bit to one enables the USART Receiver. The Receiver will override normal port operation for
  the RxDn pin when enabled. Disabling the Receiver will flush the receive buffer invalidating the FE0,
  DOR0, and UPE0 Flags.*/
  //UCSR0B-RXCIE0:
  /*Writing this bit to one enables interrupt on the RXC0 Flag. A USART Receive Complete interrupt will be
  generated only if the RXCIE0 bit is written to one, the Global Interrupt Flag in SREG is written to one and
  the RXC0 bit in UCSR0A is set.*/
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

  //Atmega pagina 250
  //UCSZ0[2:0] = 011 = 8-bit
  UCSR0C = ( 1 << UCSZ01) | ( 1 << UCSZ00);
}

//Send byte door seriele communicatie
void transmitByte(uint8_t data) {
  //UDRE0 = 1 = empty buffer
  loop_until_bit_is_set(UCSR0A, UDRE0);
  //Set in variable
  UDR0 = data;
}

//Print string door via de seriele communicatie
void transmitString(const char data[]) {
  uint8_t i = 0;
  while(data[i]) {
    transmitByte(data[i]);
    i++;
  }
}

//Read incoming byte
uint8_t receiveByte(void) {
  //RXC0 = 1 = contains readable data
  loop_until_bit_is_set(UCSR0A, RXC0);
  //Return contains
  return UDR0;
}

void initTimer0Overflow() {
  //Atmega pagina 142
  //clkI/O/1024 (From prescaler) CA0[2:0] = 101
  TCCR0B |= (1 << CS02) | (1 << CS00);

  //Atmega pagina 143
  //Enable Timer/Counter0, Overflow Interrupt
  //TIMSK0-TOIE:
  /*When the TOIE0 bit is written to one, and the I-bit in the Status Register is set, the Timer/Counter0
  Overflow interrupt is enabled. The corresponding interrupt is executed if an overflow in Timer/Counter0
  occurs, i.e., when the TOV0 bit is set in TIFR0.*/
  TIMSK0 |= (1 << TOIE0);

  //enable interrupt
  sei();
}

void initTimer2PWM() {
  //Atmega pagina 170-172
  //Pinnen: OC1A = PB1 = RED && OC1B = PB2 = GREEN
  //WGM12 en WGM10 op 1 = Fast PWM, 8-bit
  TCCR1A |= (1 << WGM12) | (1 << WGM10);
  //Atmega pagina 173
  //CS11 = 1 = clkI/O/8 (From prescaler), 8 bit
  TCCR1B |= (1 << CS11);

  //Atmega pagina 205
  //Pin: OC2A = PB3 = BLUE
  //WGM21 en WGM20 op 1 = Fast PWM
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  //Atmega pagina 206 (Er staat in de datasheet CAxx, maar moet CSxx zijn)
  //CS21 = 1 = clkI/O/8 (From prescaler), 8 bit
  TCCR2B |= (1 << CS21);

  //Atmega pagina 170-171
  //COM1A1 en COM1B1 op 1 en Fast PWM = Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

  //Atmega pagina 203
  //COM2A1 op 1 en Fast PWM = Clear OC2A on Compare Match, set OC2A at BOTTOM (non-inverting mode)
  TCCR2A |= (1 << COM2A1);

  //enable interrupt
  sei();
}

//default color when startup
char color = 'r';
//pulse start at 0
int pulse = 0;

//Atmega pagina 82
//ISR USART_RX
ISR(USART_RX_vect) {
  //incoming byte in variable input for reading
  char input = receiveByte();

  //if incoming byte is equals to: r = RED LIGHT
  if(input == 'r') {
    //Pulse weer op 0 anders begint die fell
    pulse = 0;
    //sla op voor ISR functie
    color = 'r';
    //Print text in serial monitor
    transmitString("Red\n");
  }
  //if incoming byte is equals to: g = GREEN LIGHT
  if(input == 'g') {
    //Pulse weer op 0 anders begint die fell
    pulse = 0;
    //sla op voor ISR functie
    color = 'g';
    //Print text in serial monitor
    transmitString("Green\n");
  }
  //if incoming byte is equals to: b = BLUE LIGHT
  if(input == 'b') {
    //Pulse weer op 0 anders begint die fell
    pulse = 0;
    //sla op voor ISR functie
    color = 'b';
    //Print text in serial monitor
    transmitString("Blue\n");
  }
}

//Atmega pagina 82
//ISR Timer/Counter0 Overflow
ISR(TIMER0_OVF_vect) {
  //Pulse speed
  pulse+=2;
  //RED = OCR1A = PB1 = PORT_RED
  //GREEN = OCR1B = PB2 = PORT_GREEN
  //BLUE = OCR2A = PB3 = PORT_BLUE
  if(color == 'r') {
    //RED LIGHT pulses
    RED = ~(pulse);
    //GREEN LIGHT OFF
    GREEN = ~(0 << PORT_GREEN);
    //BLUE LIGHT OFF
    BLUE = ~(0 << PORT_BLUE);
  }
  if(color == 'g') {
    //RED LIGHT OFF
    RED = ~(0 << PORT_RED);
    //GREEN LIGHT pulses
    GREEN = ~(pulse);
    //BLUE LIGHT OFF
    BLUE = ~(0 << PORT_BLUE);
  }
  if(color == 'b') {
    //RED LIGHT OFF
    RED = ~(0 << PORT_RED);
    //GREEN LIGHT OFF
    GREEN = ~(0 << PORT_GREEN);
    //BLUE LIGHT pulses
    BLUE = ~(pulse);
  }
}

int main(void) {
  //RGB pinnen initialiseren | PB1, PB2 en PB3
  DDRB = (1 << PORT_RED) | (1 << PORT_GREEN) | (1 << PORT_BLUE);
  //Start functies
  initUSART();
  initTimer0Overflow();
  initTimer2PWM();

  while(1) {
    //empty
  }
  return 0;
}
