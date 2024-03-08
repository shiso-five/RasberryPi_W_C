#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define I2CBUS      1
#define PCF8574_ADDR 0x27

struct I2CLCD {
  int LCD_CLR               ;      /* DB0: clear display                  */
  int LCD_HOME              ;      /* DB1: return to home position        */
  int LCD_ENTRY_MODE        ;      /* DB2: set entry mode                 */
  int LCD_ENTRY_INC         ;      /*   DB1: 1=increment, 0=decrement     */
  int LCD_ENTRY_SHIFT       ;      /*   DB2: 1=display shift on           */
  int LCD_ON                ;      /* DB3: turn lcd/cursor on             */
  int LCD_ON_DISPLAY        ;      /*   DB2: turn display on              */
  int LCD_ON_CURSOR         ;      /*   DB1: turn cursor on               */
  int LCD_ON_BLINK          ;      /*     DB0: blinking cursor ?          */
  int LCD_SHIFT             ;      /* DB4: move cursor/display            */
  int LCD_SHIFT_DISP        ;      /*   DB3: move display (0-> cursor) ?  */
  int LCD_SHIFT_RIGHT       ;      /*   DB2: move right (0-> left) ?      */
  int LCD_FUNCTION          ;      /* DB5: function set                   */
  int LCD_FUNCTION_8BIT     ;      /*   DB4: set 8BIT mode (0->4BIT mode) */
  int LCD_FUNCTION_2LINES   ;      /*   DB3: two lines (0->one line)      */
  int LCD_FUNCTION_10DOTS   ;      /*   DB2: 5x10 font (0->5x7 font)      */
  int LCD_CGRAM             ;      /* DB6: set CG RAM address             */
  int LCD_DDRAM             ;      /* DB7: set DD RAM address             */
  int LCD_BUSY              ;      /* DB7: LCD is busy                    */

  int i2cHandle;
  uint16_t slaveAddr;
  uint8_t PIN_PCF8574;
  int RS;
  int RW;
  int E;
  int BL; //backlight
  int dataLine[4]; //0: D4, 1: D5, 2: D6, 3: D7
};

void    I2CLCDInit        (struct I2CLCD*);
void    I2CLCDTerm        (struct I2CLCD*);

void    I2CLCDCommand     (struct I2CLCD*, uint8_t);
void    I2CLCDClear       (struct I2CLCD*);
void    I2CLCDHome        (struct I2CLCD*);
void    I2CLCDEntryModeSet(struct I2CLCD*, uint8_t, uint8_t);
void    I2CLCDDispOn      (struct I2CLCD*, uint8_t, uint8_t, uint8_t);
void    I2CLCDShift       (struct I2CLCD*, uint8_t, uint8_t);
void    I2CLCDFuncSet     (struct I2CLCD*, uint8_t, uint8_t, uint8_t);
void    I2CLCDSetCGRAMAddr(struct I2CLCD*, uint8_t);
void    I2CLCDSetDDRAMAddr(struct I2CLCD*, uint8_t);

void    I2CLCDEToggle     (struct I2CLCD*);
void    I2CLCDWrite       (struct I2CLCD*, uint8_t, uint8_t);
uint8_t I2CLCDRead        (struct I2CLCD*, uint8_t);
uint8_t I2CLCDWaitBusy    (struct I2CLCD*);

void    I2CLCDRSLow       (struct I2CLCD*);
void    I2CLCDRSHigh      (struct I2CLCD*);
void    I2CLCDRWLow       (struct I2CLCD*);
void    I2CLCDRWHigh      (struct I2CLCD*);
void    I2CLCDELow        (struct I2CLCD*);
void    I2CLCDEHigh       (struct I2CLCD*);
void    I2CLCDBLLow       (struct I2CLCD*);
void    I2CLCDBLHigh      (struct I2CLCD*);

void    I2CLCDPutChar     (struct I2CLCD*, char);
void    I2CLCDPrint       (struct I2CLCD*, char*);
void    I2CLCDGoToXY      (struct I2CLCD*, uint8_t, uint8_t);
