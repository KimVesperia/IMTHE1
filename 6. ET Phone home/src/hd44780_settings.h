#ifndef HD44780_SETTINGS_H
#define HD44780_SETTINGS_H

// #define F_CPU                    1000000     // Set Clock Frequency

#define USE_ADELAY_LIBRARY       0           // Set to 1 to use my ADELAY library, 0 to use internal delay functions
//4bit en niet 8
#define LCD_BITS                 4           // 4 for 4 Bit I/O Mode, 8 for 8 Bit I/O Mode
#define RW_LINE_IMPLEMENTED      0           // 0 for no RW line (RW on LCD tied to ground), 1 for RW line present
//gaat naar ground dus blijft 0
#define WAIT_MODE                0           // 0=Use Delay Method (Faster if running <10Mhz)
                                             // 1=Use Check Busy Flag (Faster if running >10Mhz) ***Requires RW Line***
#define DELAY_RESET              15          // in mS

#if (LCD_BITS==8)                            // If using 8 bit mode, you must configure DB0-DB7
  #define LCD_DB0_PORT           PORTC
  #define LCD_DB0_PIN            0
  #define LCD_DB1_PORT           PORTC
  #define LCD_DB1_PIN            1
  #define LCD_DB2_PORT           PORTC
  #define LCD_DB2_PIN            2
  #define LCD_DB3_PORT           PORTC
  #define LCD_DB3_PIN            3
#endif

//Maak gebruik van 4 bits dus alleen deze instellen
//bij staat de b register, maar ik had de d register gebruikt. Maakt opzich niet uit als ik de define namen met rust laat
#define LCD_DB4_PORT             PORTD      // If using 4 bit omde, yo umust configure DB4-DB7
#define LCD_DB4_PIN              PD5
#define LCD_DB5_PORT             PORTD
#define LCD_DB5_PIN              PD4
#define LCD_DB6_PORT             PORTD
#define LCD_DB6_PIN              PD3
#define LCD_DB7_PORT             PORTD
#define LCD_DB7_PIN              PD2
//RS poort instellen
#define LCD_RS_PORT              PORTB       // Port for RS line
#define LCD_RS_PIN               PB4           // Pin for RS line
//niet nodig want RW ging naar ground
// #define LCD_RW_PORT              PORTC       // Port for RW line (ONLY used if RW_LINE_IMPLEMENTED=1)
// #define LCD_RW_PIN               6           // Pin for RW line (ONLY used if RW_LINE_IMPLEMENTED=1)

#define LCD_DISPLAYS             1	         // Up to 4 LCD displays can be used at one time
                                             // All pins are shared between displays except for the E
                                             // pin which each display will have its own

//E line instellen                           // Display 1 Settings - if you only have 1 display, YOU MUST SET THESE
#define LCD_DISPLAY_LINES        2           // Number of Lines, Only Used for Set I/O Mode Command
#define LCD_E_PORT               PORTB       // Port for E line
#define LCD_E_PIN                PB3           // Pin for E line

#if (LCD_DISPLAYS>=2)                        // If you have 2 displays, set these and change LCD_DISPLAYS=2
  #define LCD_DISPLAY2_LINES     2           // Number of Lines, Only Used for Set I/O Mode Command
  #define LCD_E2_PORT            PORTC       // Port for E line
  #define LCD_E2_PIN             5           // Pin for E line
#endif

#if (LCD_DISPLAYS>=3)                        // If you have 3 displays, set these and change LCD_DISPLAYS=3
  #define LCD_DISPLAY3_LINES     2           // Number of Lines, Only Used for Set I/O Mode Command
  #define LCD_E3_PORT            PORTC       // Port for E line
  #define LCD_E3_PIN             5           // Pin for E line
#endif

#if (LCD_DISPLAYS>=4)                        // If you have 4 displays, set these and change LCD_DISPLAYS=4
  #define LCD_DISPLAY4_LINES     2           // Number of Lines, Only Used for Set I/O Mode Command
  #define LCD_E4_PORT            PORTC       // Port for E line
  #define LCD_E4_PIN             5           // Pin for E line
#endif

#endif
