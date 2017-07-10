/* 
 * File:   main.c
 * Author:  Gaurav
 * website: www.circuitvalley.com 
 * Created on JULY 10, 2017, 1:33 AM
 *	This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *	Email: mailchaduarygaurav@gmail.com
************************************************************************/


#include <xc.h>
#include <stdint.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV // CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF       // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)




#define isThisAnalogCapable(anselpin) anselpin


#define TRIS_M(port_name,bit) TRIS ## port_name ## bits.TRIS ## port_name## bit  =0 ;

#define LAT_M(port_name,bit,value) LAT ## port_name ## bits.LAT ## port_name## bit  =!value ;


#define set_Digit0_pin_output  TRIS_M(C,6) 
#define set_Digit1_pin_output  TRIS_M(B,4) 
#define set_Digit2_pin_output  TRIS_M(B,7) 
#define set_Digit3_pin_output  TRIS_M(B,6) 

#define digit_0(value) LAT_M(C,6,value)
#define digit_1(value) LAT_M(B,4,value)
#define digit_2(value) LAT_M(B,7,value)
#define digit_3(value) LAT_M(B,6,value)

#define set_segment_a_pin_output TRIS_M(C,5) 
#define set_segment_b_pin_output TRIS_M(C,2)  
#define set_segment_c_pin_output TRIS_M(C,7)  
#define set_segment_d_pin_output TRIS_M(C,3) 
#define set_segment_e_pin_output TRIS_M(A,5) 
#define set_segment_f_pin_output TRIS_M(C,4) 
#define set_segment_g_pin_output TRIS_M(B,5)  

#define segment_a(value) LAT_M(C,5,value)
#define segment_b(value) LAT_M(C,2,value)
#define segment_c(value) LAT_M(C,7,value)
#define segment_d(value) LAT_M(C,3,value)
#define segment_e(value) LAT_M(A,5,value)
#define segment_f(value) LAT_M(C,4,value)
#define segment_g(value) LAT_M(B,5,value)



inline void set_segment_value(uint8_t value) 
{
    
    segment_a(0);
    segment_b(0);
    segment_c(0);
    segment_d(0);
    segment_e(0);
    segment_f(0);
    segment_g(0);
    
    switch(value) 
    {
    case 0: segment_a(1); segment_b(1); segment_c(1);  segment_d(1); segment_e(1); segment_f(1); 
    return;
    case 1: segment_b(1); segment_c(1); 
    return;
    case 2: segment_a(1); segment_b(1); segment_d(1);  segment_e(1); segment_g(1); 
    return;
    case 3: segment_a(1); segment_b(1); segment_c(1);  segment_d(1); segment_g(1); 
    return;
    case 4: segment_b(1); segment_c(1); segment_f(1);  segment_g(1); 
    return;
    case 5: segment_a(1); segment_c(1); segment_d(1);  segment_f(1); segment_g(1); 
    return;
    case 6: segment_a(1); segment_c(1); segment_d(1);  segment_e(1); segment_f(1); segment_g(1); 
    return;
    case 7: segment_a(1); segment_b(1); segment_c(1);  
    return;
    case 8: segment_a(1); segment_b(1); segment_c(1);  segment_d(1); segment_e(1); segment_f(1); segment_g(1);  
    return;
    case 9: segment_a(1); segment_b(1); segment_c(1);  segment_d(1); segment_f(1); segment_g(1);
    return;
    }
}

inline void set_digit_value(uint8_t digit,uint8_t value) 
{

    switch(digit) 
    {
    case 0: digit_1(0);digit_2(0);digit_3(0);   digit_0(1); break; 
    case 1: digit_0(0);digit_2(0);digit_3(0);   digit_1(1); break; 
    case 2: digit_0(0);digit_1(0);digit_3(0);   digit_2(1); break; 
    case 3: digit_0(0);digit_1(0);digit_2(0);   digit_3(1); break; 
    } 
    set_segment_value(value);
}                               



void initPortPins()
{
    set_Digit0_pin_output;
    set_Digit1_pin_output;
    set_Digit2_pin_output;
    set_Digit3_pin_output; 
    
    set_segment_a_pin_output;
    set_segment_b_pin_output;
    set_segment_c_pin_output;
    set_segment_d_pin_output;
    set_segment_e_pin_output;
    set_segment_f_pin_output;
    set_segment_g_pin_output;
    ANSELB=0;
    ANSELC=0;
    
}
char digit=0;
uint8_t result_collected=8;
uint32_t gross_adc_value=0;
uint8_t display_word[4]={1,2,3,4};
void interrupt tc_int(void)
{

 if (TMR0IE && TMR0IF) {
        TMR0IF=0;
        set_digit_value( (digit++) & 0x3, display_word[digit&0x3] );
 return;
 }
 
 if(PIR1bits.ADIF )
 {
   uint16_t adc_result;
     adc_result= ADRES;
     result_collected++;
     gross_adc_value = gross_adc_value+adc_result;
     if(result_collected>127)
     {
     gross_adc_value=(gross_adc_value>>7 );
     gross_adc_value=gross_adc_value*333;
     gross_adc_value=gross_adc_value/100;
     display_word[3]=gross_adc_value%10;
     gross_adc_value=gross_adc_value/10;
     display_word[2]=gross_adc_value%10;
     gross_adc_value=gross_adc_value/10;
     display_word[1]=gross_adc_value%10;
     gross_adc_value=gross_adc_value/10;
     display_word[0]=gross_adc_value%10;
      result_collected=0;

     }
     PIR1bits.ADIF=0;
 }
}

void main(void) {
    OSCCONbits.IRCF = 0xF; //16Mhz
    initPortPins();
    OPTION_REGbits.PSA=0;
    OPTION_REGbits.TMR0CS=0;
    OPTION_REGbits.PS=0x7;
    INTCONbits.TMR0IE=1;

    
    T2CONbits.T2CKPS = 2;
    T2CONbits.T2OUTPS = 13;
    T2CONbits.TMR2ON =1;
    PR2=240; // 240 give 60hz interrrupt , ((12M/64)/240) / 13  == 60.096
    PIR1bits.TMR2IF =0;
    //PIE1bits.TMR2IE=1;
    FVRCONbits.ADFVR= 2; //2.048v
    FVRCONbits.FVREN=1;
    
    ADCON0bits.CHS = 3; //AN3
    ADCON0bits.ADON = 1; 
    ADCON0bits.GO_nDONE = 1;
    ADCON1bits.ADFM = 1; //right justified  
    ADCON1bits.ADCS = 5; // 48Mhz clock divided by 16
    ADCON1bits.ADPREF = 3; // select internal ref
    ADCON2bits.TRIGSEL = 5;  //TMR2 Match to PR2
    PIR1bits.ADIF=0;
    PIE1bits.ADIE=1;
    
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    while(1)
    {
     
            } 
    return;
}
