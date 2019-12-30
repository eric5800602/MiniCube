/*
 * File:   main.c
 * Author: User
 *
 * Created on 2019年12月19日, 下午 10:49
 */
// CONFIG1H
#pragma config OSC = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>
#include <pic18f4520.h>
#define _XTAL_FREQ 12000000
void Delay_us(int us);
void Data(char Value);           
void Cmd(int Value);            
void Send2Lcd(const char Adr, const char *Lcd);
void LCD_String_xy(char row,char pos,const char *msg);
void MSdelay(unsigned int val);
void LCD_Command(char cmd );
void LCD_Char(char dat);
void LCD_String(const char *msg);

int i = 0,times = 0,run = 0;

void __interrupt () isr (void)
{
    if(PIR1bits.TMR2IF == 1){
        if(run){
            times++;
            if(times == 100){
                i++;
                times = 0;
            }
        }
        if(PORTCbits.RC5 == 0){
            if(run == 1){
                run = 0;
            }
            PORTCbits.RC5 = 1;
        }
        if(PORTCbits.RC4 == 0){
            Cmd(0X38);                   /* Double Line Display Command             */
            Cmd(0X0C);                   /* Display ON Command                      */
            Cmd(0X01);                   /* Clear Display Command                   */
            Cmd(0X06);
            run = 1;
            i = 0;
            times = 0;
            PORTCbits.RC4 = 1;
        }
        if(PORTCbits.RC3 == 0){
            if(run == 1){
                run = 0;
            }
            PORTCbits.RC3 = 1;
        }
        PIR1bits.TMR2IF = 0;
    }
    return;
}
void main()                     
{
    TRISC=0X00;                  /* PORTC(control lines) configured as o/p  */
    TRISD=0X00;                  /* PORTD(data lines) configured as o/p     */
    TRISCbits.RC4 = 1;
    TRISCbits.RC5 = 1;
    TRISCbits.RC3 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;//4
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS3 = 1;
    T2CONbits.T2OUTPS2 = 1;
    T2CONbits.T2OUTPS1 = 1;
    T2CONbits.T2OUTPS0 = 1;//16
    T2CONbits.T2CKPS1 = 1;//16
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    IPR1bits.TMR2IP = 1;
    RCONbits.IPEN = 0x01;
    INTCONbits.GIE = 1;
    PR2 = 39;
    Delay_us(25);              
    Cmd(0X38);                   /* Double Line Display Command             */
    Cmd(0X0C);                   /* Display ON Command                      */
    Cmd(0X01);                   /* Clear Display Command                   */
    Cmd(0X06);                   /* Auto Increment Location Address Command */
    run = 0;
    while(1){
        if(run == 1){         
            Delay_us(1000);
            char s[10];
            sprintf(s,"%d.%d",i,times);
            Send2Lcd(0x80,"------Time:------");  /* Displays string in the first line       */
            Send2Lcd(0xC6,s);     /* Displays string in the second line      */
        }
    }
}

 
/*************************************************************************
* Function    : Cmd                                                      *
*                                                                        *
* Description : Function to send a command to LCD                        *
*                                                                        *
* Parameters  : Value - command to be sent                               *
**************************************************************************/
void Cmd(int Value)
{
 PORTD = Value;               /* Write the command to data lines         */
 RC0   = 0;                   /* RS-0(command register)                  */
 RC1   = 1;                   /* E-1(enable)                             */
 Delay_us(25);                
 RC1   = 0;                   /* E-0(enable)                             */
}
 
/*************************************************************************
* Function    : Data                                                     *
*                                                                        *
* Description : Function to display single character on LCD              *
*                                                                        *
* Parameters  : Value - character to be displayed                        *
**************************************************************************/
void Data(char Value)
{
 volatile char v = Value;
 PORTD = Value;               /* Write the character to data lines       */
 RC0   = 1;                   /* RS-1(data register)                     */
 RC1   = 1;                   /* E-1(enable)                             */
 Delay_us(25);                
 RC1   = 0;                   /* E-0(enable)                             */
}
 
/*************************************************************************
* Function    : Send2LCD                                                 *
*                                                                        *
* Description : Function to display string on LCD                        *
*                                                                        *
* Parameters  : Adr - location                                           *
*               String to be displayed                                   *
**************************************************************************/
void Send2Lcd(const char Adr, const char *Lcd)
{
 Cmd(Adr);                    /* Address of location to display string   */
 while(*Lcd!='\0')            /* Check for termination character         */
 {    
  Data(*Lcd);                 /* Display the character on LCD            */    
  Lcd++;                      /* Increment the pointer                   */
 }
}
 
/*************************************************************************
* Function    : Delay_us                                                 *
*                                                                        *
* Description : Function for 1 microsecond delay                         *
*                                                                        *
* Parameter   : us - delay in microseconds                               *
**************************************************************************/
void Delay_us(int us)
{
 us=us>>1;
 while(us!=1)
 us--;
}
