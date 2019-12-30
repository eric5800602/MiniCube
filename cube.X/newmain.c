/*
 * File:   newmain.c
 * Author: User
 *
 * Created on 2019年12月14日, 上午 11:43
 */
// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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
typedef union RGB{
    unsigned char rgb;
    struct {
        unsigned r:1 ;
        unsigned g:1 ;
        unsigned b:1 ;
        unsigned bit3:1 ;
        unsigned bit4:1 ;
        unsigned bit5:1 ;
        unsigned bit6:1 ;
        unsigned bit7:1 ;
    };
}rgbarray;
volatile rgbarray rgb[24];
#define _XTAL_FREQ 35000000
#define TOP 0
#define BOT 1
#define RIGHT 2
#define LEFT 3
#define SIDE_TOP 4
#define SIDE_BOT 5
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
volatile int original[6];
int need_to_check = 0;
void __interrupt () isr (void)
{
    if(PIR1bits.TMR2IF == 1){
        //check correct
        if(need_to_check == 1){
            int i,check = 0;
            rgbarray temp = rgb[0];
            for(i = 1;i < 4;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            temp = rgb[4];
            for(i = 5;i < 8;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            temp = rgb[8];
            for(i = 9;i < 12;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            temp = rgb[12];
            for(i = 13;i < 16;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            temp = rgb[16];
            for(i = 17;i < 20;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            temp = rgb[20];
            for(i = 21;i < 24;i++){
                if(temp.r != rgb[i].r ||temp.g != rgb[i].g || temp.b != rgb[i].b){
                    check = 1;
                    //break;
                }
            }
            if(check == 0){
                LATAbits.LA4 = 0;
                need_to_check = 0;
            }
        }
        if(RCIF)
        {
            if(RCSTAbits.OERR)
            {
                CREN = 0;
                Nop();
                CREN = 1;
            }
            MyusartRead();
            if(lenStr > 5){
                UART_Write_Text("Clear\t");
                ClearBuffer();
            }
            if(strcmp(mystring,"os") == 0){
                int k;
                char str[50] = "";
                for(k = 0;k < 24;k++){
                    if(rgb[k].r == 0 && rgb[k].g == 0 && rgb[k].b == 0){
                        sprintf(str,"%s 5",str);
                    }
                    else if(rgb[k].r == 1 && rgb[k].g == 0 && rgb[k].b == 1){
                        sprintf(str,"%s 4",str);
                    }
                    else if(rgb[k].r == 0 && rgb[k].g == 1 && rgb[k].b == 0){
                        sprintf(str,"%s 3",str);
                    }
                    else if(rgb[k].r == 0 && rgb[k].g == 0 && rgb[k].b == 1){
                        sprintf(str,"%s 2",str);
                    }
                    else if(rgb[k].r == 1 && rgb[k].g == 1 && rgb[k].b == 0){
                        sprintf(str,"%s 1",str);
                    }
                    else if(rgb[k].r == 0 && rgb[k].g == 1 && rgb[k].b == 1){
                        sprintf(str,"%s 0",str);
                    }
                }
                UART_Write_Text(str);
                ClearBuffer();
            }
        }
        PIR1bits.TMR2IF = 0;
    }
    
    return;
}
void ADC_Initialize(void) {
    
    TRISA = 0xff;		// Set as input port
    ADCON1 = 0x00;  	// Ref vtg is VDD & Configure pin as analog pin 
    ADCON2 = 0x90;
    ADFM = 1 ;          // Right Justifie
    ADCON2bits.ADCS = 0; // 
    ADRESH=0;  			// Flush ADC output Register
    ADRESL=0;
}
int ADC_Read(int channle)
{
    volatile int digital;
    if(channle == 2)channle = 6;
    if(channle == 3)channle = 7;
    ADCON0bits.CHS =  channle; 
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1;
    
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);
    return(digital);
}
void initial(void){
    int i;
    LATAbits.LA4 = 1;
    need_to_check = 0;
    for(i = 0;i < 4;i++){
        rgb[i].r = 0;
        rgb[i].g = 0;
        rgb[i].b = 1;//橘
    }
    for(i = 4;i < 8;i++){
        rgb[i].r = 1;
        rgb[i].g = 0;
        rgb[i].b = 1;//green
    }
    for(i = 8;i < 12;i++){
        rgb[i].r = 0;
        rgb[i].g = 0;
        rgb[i].b = 0;//白
    }
    for(i = 12;i < 16;i++){
        rgb[i].r = 1;
        rgb[i].g = 1;
        rgb[i].b = 0;//藍
    }
    for(i = 16;i < 20;i++){
        rgb[i].r = 0;
        rgb[i].g = 1;
        rgb[i].b = 1;//紅
    }
    for(i = 20;i < 24;i++){
        rgb[i].r = 0;
        rgb[i].g = 1;
        rgb[i].b = 0;//靛
    }
}
void rr(){
    rgbarray tempa = rgb[2];
    rgbarray tempb = rgb[3];
    rgb[2].r = rgb[6].r;rgb[3].r = rgb[7].r;
    rgb[2].g = rgb[6].g;rgb[3].g = rgb[7].g;
    rgb[2].b = rgb[6].b;rgb[3].b = rgb[7].b;
    rgb[6].r = rgb[10].r;rgb[7].r = rgb[11].r;
    rgb[6].g = rgb[10].g;rgb[7].g = rgb[11].g;
    rgb[6].b = rgb[10].b;rgb[7].b = rgb[11].b;
    rgb[10].r = rgb[14].r;rgb[11].r = rgb[15].r;
    rgb[10].g = rgb[14].g;rgb[11].g = rgb[15].g;
    rgb[10].b = rgb[14].b;rgb[11].b = rgb[15].b;
    rgb[14].r = tempa.r;rgb[15].r = tempb.r;
    rgb[14].g = tempa.g;rgb[15].g = tempb.g;
    rgb[14].b = tempa.b;rgb[15].b = tempb.b;
    rgbarray tempc = rgb[20];
    rgb[20].r = rgb[21].r;rgb[21].r = rgb[22].r;
    rgb[20].g = rgb[21].g;rgb[21].g = rgb[22].g;
    rgb[20].b = rgb[21].b;rgb[21].b = rgb[22].b;
    rgb[22].r = rgb[23].r;rgb[23].r = tempc.r;
    rgb[22].g = rgb[23].g;rgb[23].g = tempc.g;
    rgb[22].b = rgb[23].b;rgb[23].b = tempc.b;
    return;
}
void rr_u(){
    rgbarray tempc = rgb[14];
    rgbarray tempd = rgb[15];
    rgb[14].r = rgb[10].r;rgb[15].r = rgb[11].r;
    rgb[14].g = rgb[10].g;rgb[15].g = rgb[11].g;
    rgb[14].b = rgb[10].b;rgb[15].b = rgb[11].b;
    rgb[10].r = rgb[6].r;rgb[11].r = rgb[7].r;
    rgb[10].g = rgb[6].g;rgb[11].g = rgb[7].g;
    rgb[10].b = rgb[6].b;rgb[11].b = rgb[7].b;
    rgb[6].r = rgb[2].r;rgb[7].r = rgb[3].r;
    rgb[6].g = rgb[2].g;rgb[7].g = rgb[3].g;
    rgb[6].b = rgb[2].b;rgb[7].b = rgb[3].b;
    rgb[2].r = tempc.r;rgb[3].r = tempd.r;
    rgb[2].g = tempc.g;rgb[3].g = tempd.g;
    rgb[2].b = tempc.b;rgb[3].b = tempd.b;
    rgbarray tempf = rgb[23];
    rgb[23].r = rgb[22].r;rgb[22].r = rgb[21].r;
    rgb[23].g = rgb[22].g;rgb[22].g = rgb[21].g;
    rgb[23].b = rgb[22].b;rgb[22].b = rgb[21].b;
    rgb[21].r = rgb[20].r;rgb[20].r = tempf.r;
    rgb[21].g = rgb[20].g;rgb[20].g = tempf.g;
    rgb[21].b = rgb[20].b;rgb[20].b = tempf.b;
}
void rotate_r(int val){//轉右邊
    if(val > 3){
        val = 3;
    }
    if(val>original[RIGHT]){
        int buf = val-original[RIGHT];
        while(buf>0){
            rr();
            buf--;
        }
    }
    else if(original[RIGHT]>val){
        int buf = original[RIGHT]-val;
        while(buf>0){
            rr_u();
            buf--;
        }
         
    }
}
void rl(){
    rgbarray tempa = rgb[0];
    rgbarray tempb = rgb[1];
    rgb[0].r = rgb[4].r;rgb[1].r = rgb[5].r;
    rgb[0].g = rgb[4].g;rgb[1].g = rgb[5].g;
    rgb[0].b = rgb[4].b;rgb[1].b = rgb[5].b;
    rgb[4].r = rgb[8].r;rgb[5].r = rgb[9].r;
    rgb[4].g = rgb[8].g;rgb[5].g = rgb[9].g;
    rgb[4].b = rgb[8].b;rgb[5].b = rgb[9].b;
    rgb[8].r = rgb[12].r;rgb[9].r = rgb[13].r;
    rgb[8].g = rgb[12].g;rgb[9].g = rgb[13].g;
    rgb[8].b = rgb[12].b;rgb[9].b = rgb[13].b;
    rgb[12].r = tempa.r;rgb[13].r = tempb.r;
    rgb[12].g = tempa.g;rgb[13].g = tempb.g;
    rgb[12].b = tempa.b;rgb[13].b = tempb.b;
    rgbarray tempf = rgb[16];
    rgb[16].r = rgb[19].r;rgb[19].r = rgb[18].r;
    rgb[16].g = rgb[19].g;rgb[19].g = rgb[18].g;
    rgb[16].b = rgb[19].b;rgb[19].b = rgb[18].b;
    rgb[18].r = rgb[17].r;rgb[17].r = tempf.r;
    rgb[18].g = rgb[17].g;rgb[17].g = tempf.g;
    rgb[18].b = rgb[17].b;rgb[17].b = tempf.b;
}
void rl_u(){
    rgbarray tempc = rgb[12];
    rgbarray tempd = rgb[13];
    rgb[12].r = rgb[8].r;rgb[13].r = rgb[9].r;
    rgb[12].g = rgb[8].g;rgb[13].g = rgb[9].g;
    rgb[12].b = rgb[8].b;rgb[13].b = rgb[9].b;
    rgb[8].r = rgb[4].r;rgb[9].r = rgb[5].r;
    rgb[8].g = rgb[4].g;rgb[9].g = rgb[5].g;
    rgb[8].b = rgb[4].b;rgb[9].b = rgb[5].b;
    rgb[4].r = rgb[0].r;rgb[5].r = rgb[1].r;
    rgb[4].g = rgb[0].g;rgb[5].g = rgb[1].g;
    rgb[4].b = rgb[0].b;rgb[5].b = rgb[1].b;
    rgb[0].r = tempc.r;rgb[1].r = tempd.r;
    rgb[0].g = tempc.g;rgb[1].g = tempd.g;
    rgb[0].b = tempc.b;rgb[1].b = tempd.b; 
    rgbarray tempf = rgb[16];
    rgb[16].r = rgb[17].r;rgb[17].r = rgb[18].r;
    rgb[16].g = rgb[17].g;rgb[17].g = rgb[18].g;
    rgb[16].b = rgb[17].b;rgb[17].b = rgb[18].b;
    rgb[18].r = rgb[19].r;rgb[19].r = tempf.r;
    rgb[18].g = rgb[19].g;rgb[19].g = tempf.g;
    rgb[18].b = rgb[19].b;rgb[19].b = tempf.b;
}
void rotate_l(int val){//轉左邊
    //used to rotate left line
    if(val > 3){
        val = 3;
    }
    if(val>original[LEFT]){
        int buf = val-original[LEFT];
        while(buf>0){
            rl();
            buf--;
        }
    }
    else if(original[LEFT]>val){
        int buf = original[LEFT]-val;
        while(buf>0){
            rl_u();
            buf--;
        }        
    }
}
void rt(){
    rgbarray tempa = rgb[0];
    rgbarray tempb = rgb[3];
    rgb[0].r = rgb[17].r;rgb[3].r = rgb[16].r;
    rgb[0].g = rgb[17].g;rgb[3].g = rgb[16].g;
    rgb[0].b = rgb[17].b;rgb[3].b = rgb[16].b;
    rgb[17].r = rgb[10].r;rgb[16].r = rgb[9].r;
    rgb[17].g = rgb[10].g;rgb[16].g = rgb[9].g;
    rgb[17].b = rgb[10].b;rgb[16].b = rgb[9].b;
    rgb[10].r = rgb[23].r;rgb[9].r = rgb[22].r;
    rgb[10].g = rgb[23].g;rgb[9].g = rgb[22].g;
    rgb[10].b = rgb[23].b;rgb[9].b = rgb[22].b;
    rgb[23].r = tempa.r;rgb[22].r = tempb.r;
    rgb[23].g = tempa.g;rgb[22].g = tempb.g;
    rgb[23].b = tempa.b;rgb[22].b = tempb.b;
    rgbarray tempc = rgb[13];
    rgb[13].r = rgb[12].r;rgb[12].r = rgb[15].r;
    rgb[13].g = rgb[12].g;rgb[12].g = rgb[15].g;
    rgb[13].b = rgb[12].b;rgb[12].b = rgb[15].b;
    rgb[15].r = rgb[14].r;rgb[14].r = tempc.r;
    rgb[15].g = rgb[14].g;rgb[14].g = tempc.g;
    rgb[15].b = rgb[14].b;rgb[14].b = tempc.b;
}
void rt_u(){
    rgbarray tempc = rgb[0];
    rgbarray tempd = rgb[3];
    rgb[0].r = rgb[23].r;rgb[3].r = rgb[22].r;
    rgb[0].g = rgb[23].g;rgb[3].g = rgb[22].g;
    rgb[0].b = rgb[23].b;rgb[3].b = rgb[22].b;
    rgb[23].r = rgb[10].r;rgb[22].r = rgb[9].r;
    rgb[23].g = rgb[10].g;rgb[22].g = rgb[9].g;
    rgb[23].b = rgb[10].b;rgb[22].b = rgb[9].b;
    rgb[10].r = rgb[17].r;rgb[9].r = rgb[16].r;
    rgb[10].g = rgb[17].g;rgb[9].g = rgb[16].g;
    rgb[10].b = rgb[17].b;rgb[9].b = rgb[16].b;
    rgb[17].r = tempc.r;rgb[16].r = tempd.r;
    rgb[17].g = tempc.g;rgb[16].g = tempd.g;
    rgb[17].b = tempc.b;rgb[16].b = tempd.b;
    rgbarray tempa = rgb[13];
    rgb[13].r = rgb[14].r;rgb[14].r = rgb[15].r;
    rgb[13].g = rgb[14].g;rgb[14].g = rgb[15].g;
    rgb[13].b = rgb[14].b;rgb[14].b = rgb[15].b;
    rgb[15].r = rgb[12].r;rgb[12].r = tempa.r;
    rgb[15].g = rgb[12].g;rgb[12].g = tempa.g;
    rgb[15].b = rgb[12].b;rgb[12].b = tempa.b;
}
void rotate_top(int val){//轉上面
    //used to rotate left line
    if(val > 3){
        val = 3;
    }
    if(val>original[TOP]){
        int buf = val-original[TOP];
        while(buf>0){
            rt();
            buf--;
        }
    }
    else if(original[TOP]>val){
        int buf = original[TOP]-val;
        while(buf>0){
            rt_u();
            buf--;
        }        
    }
}

void rb(){
    rgbarray tempa = rgb[1];
    rgbarray tempb = rgb[2];
    rgb[1].r = rgb[18].r;rgb[2].r = rgb[19].r;
    rgb[1].g = rgb[18].g;rgb[2].g = rgb[19].g;
    rgb[1].b = rgb[18].b;rgb[2].b = rgb[19].b;
    rgb[18].r = rgb[11].r;rgb[19].r = rgb[8].r;
    rgb[18].g = rgb[11].g;rgb[19].g = rgb[8].g;
    rgb[18].b = rgb[11].b;rgb[19].b = rgb[8].b;
    rgb[11].r = rgb[20].r;rgb[8].r = rgb[21].r;
    rgb[11].g = rgb[20].g;rgb[8].g = rgb[21].g;
    rgb[11].b = rgb[20].b;rgb[8].b = rgb[21].b;
    rgb[20].r = tempa.r;rgb[21].r = tempb.r;
    rgb[20].g = tempa.g;rgb[21].g = tempb.g;
    rgb[20].b = tempa.b;rgb[21].b = tempb.b;
    rgbarray tempc = rgb[4];
    rgb[4].r = rgb[5].r;rgb[5].r = rgb[6].r;
    rgb[4].g = rgb[5].g;rgb[5].g = rgb[6].g;
    rgb[4].b = rgb[5].b;rgb[5].b = rgb[6].b;
    rgb[6].r = rgb[7].r;rgb[7].r = tempc.r;
    rgb[6].g = rgb[7].g;rgb[7].g = tempc.g;
    rgb[6].b = rgb[7].b;rgb[7].b = tempc.b;
}
void rb_u(){
   rgbarray tempc = rgb[1];
    rgbarray tempd = rgb[2];
    rgb[1].r = rgb[20].r;rgb[2].r = rgb[21].r;
    rgb[1].g = rgb[20].g;rgb[2].g = rgb[21].g;
    rgb[1].b = rgb[20].b;rgb[2].b = rgb[21].b;
    rgb[20].r = rgb[11].r;rgb[21].r = rgb[8].r;
    rgb[20].g = rgb[11].g;rgb[21].g = rgb[8].g;
    rgb[20].b = rgb[11].b;rgb[21].b = rgb[8].b;
    rgb[11].r = rgb[18].r;rgb[8].r = rgb[19].r;
    rgb[11].g = rgb[18].g;rgb[8].g = rgb[19].g;
    rgb[11].b = rgb[18].b;rgb[8].b = rgb[19].b;
    rgb[18].r = tempc.r;rgb[19].r = tempd.r;
    rgb[18].g = tempc.g;rgb[19].g = tempd.g;
    rgb[18].b = tempc.b;rgb[19].b = tempd.b;
    rgbarray tempa = rgb[4];
    rgb[4].r = rgb[7].r;rgb[7].r = rgb[6].r;
    rgb[4].g = rgb[7].g;rgb[7].g = rgb[6].g;
    rgb[4].b = rgb[7].b;rgb[7].b = rgb[6].b;
    rgb[6].r = rgb[5].r;rgb[5].r = tempa.r;
    rgb[6].g = rgb[5].g;rgb[5].g = tempa.g;
    rgb[6].b = rgb[5].b;rgb[5].b = tempa.b;
}
void rotate_bot(int val){//轉上面
    //used to rotate left line
    if(val > 3){
        val = 3;
    }
    if(val>original[BOT]){
        int buf = val-original[BOT];
        while(buf>0){
            rb();
            buf--;
        }
    }
    else if(original[BOT]>val){
        int buf = original[BOT]-val;
        while(buf>0){
            rb_u();
            buf--;
        }        
    }
}
void rst(){
    rgbarray tempa = rgb[4];
    rgbarray tempb = rgb[7];
    rgb[4].r = rgb[16].r;rgb[7].r = rgb[19].r;
    rgb[4].g = rgb[16].g;rgb[7].g = rgb[19].g;
    rgb[4].b = rgb[16].b;rgb[7].b = rgb[19].b;
    rgb[16].r = rgb[14].r;rgb[19].r = rgb[13].r;
    rgb[16].g = rgb[14].g;rgb[19].g = rgb[13].g;
    rgb[16].b = rgb[14].b;rgb[19].b = rgb[13].b;
    rgb[14].r = rgb[20].r;rgb[13].r = rgb[23].r;
    rgb[14].g = rgb[20].g;rgb[13].g = rgb[23].g;
    rgb[14].b = rgb[20].b;rgb[13].b = rgb[23].b;
    rgb[20].r = tempa.r;rgb[23].r = tempb.r;
    rgb[20].g = tempa.g;rgb[23].g = tempb.g;
    rgb[20].b = tempa.b;rgb[23].b = tempb.b;
    rgbarray tempc = rgb[1];
    rgb[1].r = rgb[0].r;rgb[0].r = rgb[3].r;
    rgb[1].g = rgb[0].g;rgb[0].g = rgb[3].g;
    rgb[1].b = rgb[0].b;rgb[0].b = rgb[3].b;
    rgb[3].r = rgb[2].r;rgb[2].r = tempc.r;
    rgb[3].g = rgb[2].g;rgb[2].g = tempc.g;
    rgb[3].b = rgb[2].b;rgb[2].b = tempc.b;
}
void rst_u(){
    rgbarray tempc = rgb[4];
    rgbarray tempd = rgb[7];
    rgb[4].r = rgb[20].r;rgb[7].r = rgb[23].r;
    rgb[4].g = rgb[20].g;rgb[7].g = rgb[23].g;
    rgb[4].b = rgb[20].b;rgb[7].b = rgb[23].b;
    rgb[20].r = rgb[14].r;rgb[23].r = rgb[13].r;
    rgb[20].g = rgb[14].g;rgb[23].g = rgb[13].g;
    rgb[20].b = rgb[14].b;rgb[23].b = rgb[13].b;
    rgb[14].r = rgb[16].r;rgb[13].r = rgb[19].r;
    rgb[14].g = rgb[16].g;rgb[13].g = rgb[19].g;
    rgb[14].b = rgb[16].b;rgb[13].b = rgb[19].b;
    rgb[16].r = tempc.r;rgb[19].r = tempd.r;
    rgb[16].g = tempc.g;rgb[19].g = tempd.g;
    rgb[16].b = tempc.b;rgb[19].b = tempd.b;
    rgbarray tempa = rgb[1];
    rgb[1].r = rgb[2].r;rgb[2].r = rgb[3].r;
    rgb[1].g = rgb[2].g;rgb[2].g = rgb[3].g;
    rgb[1].b = rgb[2].b;rgb[2].b = rgb[3].b;
    rgb[3].r = rgb[0].r;rgb[0].r = tempa.r;
    rgb[3].g = rgb[0].g;rgb[0].g = tempa.g;
    rgb[3].b = rgb[0].b;rgb[0].b = tempa.b;
}
void rotate_sidetop(int val){//轉上面
    //used to rotate left line
    if(val > 3){
        val = 3;
    }
    if(val>original[SIDE_TOP]){
        int buf = val-original[SIDE_TOP];
        while(buf>0){
            rst();
            buf--;
        }
    }
    else if(original[SIDE_TOP]>val){
        int buf = original[SIDE_TOP]-val;
        while(buf>0){
            rst_u();
            buf--;
        }        
    }
}
void rsb(){
    rgbarray tempa = rgb[5];
    rgbarray tempb = rgb[6];
    rgb[5].r = rgb[17].r;rgb[6].r = rgb[18].r;
    rgb[5].g = rgb[17].g;rgb[6].g = rgb[18].g;
    rgb[5].b = rgb[17].b;rgb[6].b = rgb[18].b;
    rgb[17].r = rgb[15].r;rgb[18].r = rgb[12].r;
    rgb[17].g = rgb[15].g;rgb[18].g = rgb[12].g;
    rgb[17].b = rgb[15].b;rgb[18].b = rgb[12].b;
    rgb[15].r = rgb[21].r;rgb[12].r = rgb[22].r;
    rgb[15].g = rgb[21].g;rgb[12].g = rgb[22].g;
    rgb[15].b = rgb[21].b;rgb[12].b = rgb[22].b;
    rgb[21].r = tempa.r;rgb[22].r = tempb.r;
    rgb[21].g = tempa.g;rgb[22].g = tempb.g;
    rgb[21].b = tempa.b;rgb[22].b = tempb.b;
    rgbarray tempc = rgb[8];
    rgb[8].r = rgb[9].r;rgb[9].r = rgb[10].r;
    rgb[8].g = rgb[9].g;rgb[9].g = rgb[10].g;
    rgb[8].b = rgb[9].b;rgb[9].b = rgb[10].b;
    rgb[10].r = rgb[11].r;rgb[11].r = tempc.r;
    rgb[10].g = rgb[11].g;rgb[11].g = tempc.g;
    rgb[10].b = rgb[11].b;rgb[11].b = tempc.b;
}
void rsb_u(){
    rgbarray tempc = rgb[5];
    rgbarray tempd = rgb[6];
    rgb[5].r = rgb[21].r;rgb[6].r = rgb[22].r;
    rgb[5].g = rgb[21].g;rgb[6].g = rgb[22].g;
    rgb[5].b = rgb[21].b;rgb[6].b = rgb[22].b;
    rgb[21].r = rgb[15].r;rgb[22].r = rgb[12].r;
    rgb[21].g = rgb[15].g;rgb[22].g = rgb[12].g;
    rgb[21].b = rgb[15].b;rgb[22].b = rgb[12].b;
    rgb[15].r = rgb[17].r;rgb[12].r = rgb[18].r;
    rgb[15].g = rgb[17].g;rgb[12].g = rgb[18].g;
    rgb[15].b = rgb[17].b;rgb[12].b = rgb[18].b;
    rgb[17].r = tempc.r;rgb[18].r = tempd.r;
    rgb[17].g = tempc.g;rgb[18].g = tempd.g;
    rgb[17].b = tempc.b;rgb[18].b = tempd.b;
    rgbarray tempa = rgb[8];
    rgb[8].r = rgb[11].r;rgb[11].r = rgb[10].r;
    rgb[8].g = rgb[11].g;rgb[11].g = rgb[10].g;
    rgb[8].b = rgb[11].b;rgb[11].b = rgb[10].b;
    rgb[10].r = rgb[9].r;rgb[9].r = tempa.r;
    rgb[10].g = rgb[9].g;rgb[9].g = tempa.g;
    rgb[10].b = rgb[9].b;rgb[9].b = tempa.b;
}
void rotate_sidebot(int val){//轉上面
    //used to rotate left line
    if(val > 3){
        val = 3;
    }
    if(val>original[SIDE_BOT]){
        int buf = val-original[SIDE_BOT];
        while(buf>0){
            rsb();
            buf--;
        }
    }
    else if(original[SIDE_BOT]>val){
        int buf = original[SIDE_BOT]-val;
        while(buf>0){
            rsb_u();
            buf--;
        }        
    }
}
void random_cube(){
    int j;
    initial();
    need_to_check = 1;
    for(j = 0;j < 8;j++){
        int r = (rand()%6);
        switch(r){
            case 0:
                rr();
                break;
            case 1:
                rl();
                break;
            case 2:
                rt();
                break;
            case 3:
                rb();
                break;
            case 4:
                rst();
                break;
            case 5:
                rsb();
                break;
        }
    }
}
void main(void) {
    initial();
    ADC_Initialize();
    UART_Initialize();
    TRISD =0;
    LATD = 0;
    TRISB =0;
    TRISC = 0;
    LATB = 0;
    LATC = 0;
    TRISAbits.RA4 = 0;
    LATA = 0;
    LATAbits.LA4 = 1;
    TRISAbits.RA6 = 1;
    TRISAbits.RA7 = 1;
    PORTA = 0;
    OSCCONbits.IRCF = 6;
    LATDbits.LATD0 = 1;
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
    PR2 = 255;
    int i = 0;
    int j;
    for(j=0; j<6; j++){
        //int init_adc = ADC_Read(j);
        //original[j] = init_adc/300;
        original[j] = 0;
    }
    int turn = 0;
    while(1){
        if(PORTAbits.RA6 == 0){
            initial();
            PORTAbits.RA6 = 1;
        }
        if(PORTAbits.RA7 == 0){
            random_cube();
            PORTAbits.RA7 = 1;
        }
        //for(turn=0; turn<6; turn++){
            if(turn == TOP) {
                int val = ADC_Read(0);
                rotate_top(val/300);
                original[TOP] = val/300;
            }
            else if(turn == BOT) {
                int val = ADC_Read(1);
                rotate_bot(val/300);
                original[BOT] = val/300;
            }
            else if(turn == RIGHT) {
                int val = ADC_Read(6);
                rotate_r(val/300);
                original[RIGHT] = val/300;
            }    
            else if(turn == LEFT) {
                int val = ADC_Read(7);
                rotate_l(val/300);
                original[LEFT] = val/300;
            }
            else if(turn == SIDE_TOP) {
                int val = ADC_Read(4);
                rotate_sidetop(val/300);
                original[SIDE_TOP] = val/300;
            }
            else if(turn == SIDE_BOT) {
                int val = ADC_Read(5);
                rotate_sidebot(val/300);
                original[SIDE_BOT] = val/300;
            }
        switch(i){
            case 0:
                LATBbits.LATB0 = rgb[4].r;
                LATBbits.LATB1 = rgb[4].g;
                LATBbits.LATB2 = rgb[4].b;
                LATBbits.LATB3 = rgb[7].r;
                LATBbits.LATB4 = rgb[7].g;
                LATBbits.LATB5 = rgb[7].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 1:
                LATBbits.LATB0 = rgb[5].r;
                LATBbits.LATB1 = rgb[5].g;
                LATBbits.LATB2 = rgb[5].b;
                LATBbits.LATB3 = rgb[6].r;
                LATBbits.LATB4 = rgb[6].g;
                LATBbits.LATB5 = rgb[6].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 2:
                LATCbits.LATC0 = rgb[20].r;
                LATCbits.LATC1 = rgb[20].g;
                LATCbits.LATC2 = rgb[20].b;
                LATCbits.LATC3 = rgb[19].r;
                LATCbits.LATC4 = rgb[19].g;
                LATCbits.LATC5 = rgb[19].b;
                LATBbits.LATB0 = rgb[1].r;
                LATBbits.LATB1 = rgb[1].g;
                LATBbits.LATB2 = rgb[1].b;
                LATBbits.LATB3 = rgb[2].r;
                LATBbits.LATB4 = rgb[2].g;
                LATBbits.LATB5 = rgb[2].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 3:
                LATCbits.LATC0 = rgb[23].r;
                LATCbits.LATC1 = rgb[23].g;
                LATCbits.LATC2 = rgb[23].b;
                LATCbits.LATC3 = rgb[16].r;
                LATCbits.LATC4 = rgb[16].g;
                LATCbits.LATC5 = rgb[16].b;
                LATBbits.LATB0 = rgb[0].r;
                LATBbits.LATB1 = rgb[0].g;
                LATBbits.LATB2 = rgb[0].b;
                LATBbits.LATB3 = rgb[3].r;
                LATBbits.LATB4 = rgb[3].g;
                LATBbits.LATB5 = rgb[3].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 4:
                LATCbits.LATC0 = rgb[21].r;
                LATCbits.LATC1 = rgb[21].g;
                LATCbits.LATC2 = rgb[21].b;
                LATCbits.LATC3 = rgb[18].r;
                LATCbits.LATC4 = rgb[18].g;
                LATCbits.LATC5 = rgb[18].b;
                LATBbits.LATB0 = rgb[8].r;
                LATBbits.LATB1 = rgb[8].g;
                LATBbits.LATB2 = rgb[8].b;
                LATBbits.LATB3 = rgb[11].r;
                LATBbits.LATB4 = rgb[11].g;
                LATBbits.LATB5 = rgb[11].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 5:
                LATCbits.LATC0 = rgb[22].r;
                LATCbits.LATC1 = rgb[22].g;
                LATCbits.LATC2 = rgb[22].b;
                LATCbits.LATC3 = rgb[17].r;
                LATCbits.LATC4 = rgb[17].g;
                LATCbits.LATC5 = rgb[17].b;
                LATBbits.LATB0 = rgb[9].r;
                LATBbits.LATB1 = rgb[9].g;
                LATBbits.LATB2 = rgb[9].b;
                LATBbits.LATB3 = rgb[10].r;
                LATBbits.LATB4 = rgb[10].g;
                LATBbits.LATB5 = rgb[10].b;
                __delay_us(200);
                LATB = 255;
                LATC = 255;
                break;
            case 6:
                LATBbits.LATB0 = rgb[13].r;
                LATBbits.LATB1 = rgb[13].g;
                LATBbits.LATB2 = rgb[13].b;
                LATBbits.LATB3 = rgb[14].r;
                LATBbits.LATB4 = rgb[14].g;
                LATBbits.LATB5 = rgb[14].b;
                __delay_us(200);
                
                LATB = 255;
                LATC = 255;
                break;
            case 7:
                LATBbits.LATB0 = rgb[12].r;
                LATBbits.LATB1 = rgb[12].g;
                LATBbits.LATB2 = rgb[12].b;
                LATBbits.LATB3 = rgb[15].r;
                LATBbits.LATB4 = rgb[15].g;
                LATBbits.LATB5 = rgb[15].b;
                __delay_us(100);
                LATB = 255;
                LATC = 255;
                break;
        }
        if(i < 8){
            
            int temp = LATDbits.LATD7;
            LATDbits.LATD7 = LATDbits.LATD6;
            LATDbits.LATD6 = LATDbits.LATD5;
            LATDbits.LATD5 = LATDbits.LATD4;
            LATDbits.LATD4 = LATDbits.LATD3;
            LATDbits.LATD3 = LATDbits.LATD2;
            LATDbits.LATD2 = LATDbits.LATD1;
            LATDbits.LATD1 = LATDbits.LATD0;
            LATDbits.LATD0 = temp;
            
        }
        i++;
        if(i == 8){
            i = 0;
        }
        turn++;
        if(turn == 6) turn = 0;
    }
    return;
}
