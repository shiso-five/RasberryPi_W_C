#include "../include/lcd.h"

void LCDInit(struct LCD *lcd){
  int i;

  lcd->LCD_CLR               =0;      /* DB0: clear display                  */
  lcd->LCD_HOME              =1;      /* DB1: return to home position        */
  lcd->LCD_ENTRY_MODE        =2;      /* DB2: set entry mode                 */
  lcd->LCD_ENTRY_INC         =1;      /*   DB1: 1=increment, 0=decrement     */
  lcd->LCD_ENTRY_SHIFT       =0;      /*   DB2: 1=display shift on           */
  lcd->LCD_ON                =3;      /* DB3: turn lcd/cursor on             */
  lcd->LCD_ON_DISPLAY        =2;      /*   DB2: turn display on              */
  lcd->LCD_ON_CURSOR         =1;      /*   DB1: turn cursor on               */
  lcd->LCD_ON_BLINK          =0;      /*     DB0: blinking cursor ?          */
  lcd->LCD_SHIFT              =4;      /* DB4: move cursor/display            */
  lcd->LCD_SHIFT_DISP         =3;      /*   DB3: move display (0-> cursor) ?  */
  lcd->LCD_SHIFT_RIGHT        =2;      /*   DB2: move right (0-> left) ?      */
  lcd->LCD_FUNCTION          =5;      /* DB5: function set                   */
  lcd->LCD_FUNCTION_8BIT     =4;      /*   DB4: set 8BIT mode (0->4BIT mode) */
  lcd->LCD_FUNCTION_2LINES   =3;      /*   DB3: two lines (0->one line)      */
  lcd->LCD_FUNCTION_10DOTS   =2;      /*   DB2: 5x10 font (0->5x7 font)      */
  lcd->LCD_CGRAM             =6;      /* DB6: set CG RAM address             */
  lcd->LCD_DDRAM             =7;      /* DB7: set DD RAM address             */
  lcd->LCD_BUSY              =7;      /* DB7: LCD is busy                    */  
  
  lcd->dataPin[0] = LCD_DATA0_PIN;
  lcd->dataPin[1] = LCD_DATA1_PIN;
  lcd->dataPin[2] = LCD_DATA2_PIN;
  lcd->dataPin[3] = LCD_DATA3_PIN;
  lcd->dataPin[4] = LCD_DATA4_PIN;
  lcd->dataPin[5] = LCD_DATA5_PIN;
  lcd->dataPin[6] = LCD_DATA6_PIN;
  lcd->dataPin[7] = LCD_DATA7_PIN;

  lcd->ctrlPin[0] = LCD_RS_PIN;
  lcd->ctrlPin[1] = LCD_RW_PIN;
  lcd->ctrlPin[2] = LCD_E_PIN;

  gpioInitialise();
  for(i=0;i<8;i++){
    if(lcd->dataPin[i]>0){
      //      gpioSetMode(lcd->dataPin[i], PI_OUTPUT);
      gpioSetMode(lcd->dataPin[i], PI_INPUT);      
    }
  }
  for(i=0;i<3;i++){
    if(lcd->ctrlPin[i]>0){
      gpioSetMode(lcd->ctrlPin[i], PI_OUTPUT);
    }
  }

  time_sleep(0.1); // more than 15 ms
  LCDFuncSet(lcd, 1, 0, 0);
  time_sleep(0.1);  //more than 4.1 ms
  LCDFuncSet(lcd, 1, 0, 0);
  time_sleep(0.1);  //more than 100 us
  LCDFuncSet(lcd, 1, 0, 0);
  
  LCDFuncSet(lcd, 0, 1, 1);
  LCDFuncSet(lcd, 0, 1, 0);
  
  LCDDispOn(lcd, 0, 0, 0);
  LCDClear(lcd);
  LCDHome(lcd);
  LCDEntryModeSet(lcd, 1, 0);

  time_sleep(0.1);
  LCDDispOn(lcd, 1, 1, 1);
  LCDClear(lcd);
  LCDHome(lcd);  

  return;
}

void LCDTerm(struct LCD *lcd){
  LCDHome(lcd);
  LCDClear(lcd);
  gpioTerminate();
  
  return;
}

void LCDCommand(struct LCD* lcd, uint8_t cmd){
  LCDWaitBusy(lcd);
  LCDWrite(lcd, cmd, 0);
  
  return;
}

void LCDClear(struct LCD* lcd){
  LCDCommand(lcd, 1<<lcd->LCD_CLR);
  return;
}

void LCDHome(struct LCD* lcd){
  LCDCommand(lcd, 1<<lcd->LCD_HOME);
  return;
}

void LCDEntryModeSet(struct LCD* lcd, uint8_t IorD, uint8_t S){
  uint8_t cmd=0;
  cmd |= 1<<lcd->LCD_ENTRY_MODE;
  if(IorD){
    cmd |= 1<<lcd->LCD_ENTRY_INC;
  }
  if(S){
    cmd |= 1<<lcd->LCD_ENTRY_SHIFT;
  }
}

void LCDDispOn(struct LCD* lcd, uint8_t D, uint8_t C, uint8_t B){
  uint8_t cmd = 0;
  cmd |= 1<<lcd->LCD_ON;
  if(D){
    cmd |= 1<<lcd->LCD_ON_DISPLAY;
  }
  if(C){
    cmd |= 1<<lcd->LCD_ON_CURSOR;
  }
  if(B){
    cmd |= 1<<lcd->LCD_ON_BLINK;
  }

  LCDCommand(lcd, cmd);
  
  return;
}

void LCDShift (struct LCD* lcd, uint8_t CorD, uint8_t RorL){
  uint8_t cmd=0;

  cmd |= 1<<lcd->LCD_SHIFT;

  if(CorD){
    cmd |= 1<<lcd->LCD_SHIFT_DISP;
  }
  if(RorL){
    cmd |= 1<<lcd->LCD_SHIFT_RIGHT;
  }

  LCDCommand(lcd, cmd);
  
  return;
}

void LCDFuncSet(struct LCD* lcd, uint8_t DL, uint8_t N, uint8_t F){
  uint8_t cmd = 0;
  cmd |= 1<<lcd->LCD_FUNCTION;
  if(DL){ //8-bit mode of 4-bit mode
    cmd |= 1<<lcd->LCD_FUNCTION_8BIT;     
  }
  if(N){ //2lines or 1lines
    cmd |= lcd->LCD_FUNCTION_2LINES;
  }
  if(F){ //dots parameter
    cmd |= lcd->LCD_FUNCTION_10DOTS;
  }
  
  LCDCommand(lcd, cmd);
  //  LCDWrite(lcd, cmd, 0);  
  
  return;
}

void LCDSetCGRAMAddr(struct LCD* lcd, uint8_t addr){
  uint8_t cmd=0;

  cmd |= 1<<lcd->LCD_CGRAM;
  cmd |= addr;

  LCDCommand(lcd, cmd);
  
  return;
}

void LCDSetDDRAMAddr(struct LCD* lcd, uint8_t addr){
  uint8_t cmd=0;

  cmd |= 1<<lcd->LCD_DDRAM;
  cmd |= addr;

  LCDCommand(lcd, cmd);
  
  return;
}

void LCDEToggle(struct LCD* lcd){
  gpioWrite(lcd->ctrlPin[2], ON);
  time_sleep(0.01);
  gpioWrite(lcd->ctrlPin[2], OFF);
  
  return;
}

void LCDWrite(struct LCD* lcd, uint8_t data, uint8_t rs){
  int i;

  //    printf("data is 0x%x \n", data);  
  
  if(rs){
    gpioWrite(lcd->ctrlPin[0], ON);    
  }
  else{
    gpioWrite(lcd->ctrlPin[0], OFF);    
  }
  gpioWrite(lcd->ctrlPin[1], OFF); //rw must be low

  for(i=NDATAPIN-1;i>=0;i--){
    if(lcd->dataPin[i]>0){
      gpioSetMode(lcd->dataPin[i], PI_OUTPUT);
      if(data & 1<<i){
	gpioWrite(lcd->dataPin[i], ON);
	//	printf("data bit %d is on \n", i);
      }
      else{
	gpioWrite(lcd->dataPin[i], OFF);
	//	printf("data bit %d is off \n", i);	
      }
      if(i%4==0){
	LCDEToggle(lcd);
	//	printf("E toggled\n");
      }      
    }
  }
    
  return;
}

uint8_t LCDRead(struct LCD* lcd, uint8_t rs){
  int i;
  uint8_t data = 0;
  
  if(rs){
    gpioWrite(lcd->ctrlPin[0], ON);    
  }
  else{
    gpioWrite(lcd->ctrlPin[0], OFF);    
  }
  gpioWrite(lcd->ctrlPin[1], ON); //rw must be high

  
  for(i=0;i<NDATAPIN;i++){
    gpioSetMode(lcd->dataPin[i], PI_INPUT);
  }

  gpioWrite(lcd->ctrlPin[2], ON);
  time_sleep(0.01);  
  for(i=NDATAPIN-1;i>=0;i--){
    uint8_t rd=0;
    rd = gpioRead(lcd->dataPin[i]);
    data |= rd << i;
    //    printf("bit=%d rd=%u, ", i, rd); 
    if(i%4==0){
      gpioWrite(lcd->ctrlPin[2], OFF);      
    }
  }
  //  printf("\n");

  gpioWrite(lcd->ctrlPin[2], OFF);
  
  return data;
}
  
uint8_t LCDWaitBusy(struct LCD* lcd){
  uint8_t c;

  while( (c=LCDRead(lcd, 0)) & (1<<lcd->LCD_BUSY) ){
    //    printf("now wainting... LCDRead() = %u\n", c);
    time_sleep(0.001);
  }

  time_sleep(0.01);
  
  return LCDRead(lcd, 0);
}

void LCDPutChar(struct LCD* lcd, char c){
  LCDWrite(lcd, c, 1);      
  return;
}

void LCDPrint(struct LCD* lcd, char* str){
  int i;
  
  for(i=0;i<strlen(str);i++){
    LCDPutChar(lcd, str[i]);
  }

  return;
}

void LCDGoToXY(struct LCD* lcd, uint8_t x, uint8_t y){
  if( (0>x) || (x>=40) || (0>y) || (y>=2) ){
    fprintf(stderr, "ERROR: invalid position. must be 0<=x<40 and 0<=y<2\n");
    return;
  }
  if(y==0){
    LCDSetDDRAMAddr(lcd, x);
  }
  else if(y==1){
    LCDSetDDRAMAddr(lcd, x+0x40);
  }
  return;
}
