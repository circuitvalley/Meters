/*
 * main.c
 */
#include <msp430g2231.h>

#include <intrinsics.h>
long adcCalibrated;
long adcMeasured[8];
long adcAverage;
unsigned char count ;
unsigned char i;

unsigned char digits[3] = {0x0f,0x0f,0x0f};
unsigned char digit;

void configureAdc(void);
void InitializeClocks(void);
void initPort(void);
void initTimer(void);
void display(void );


// Timer A0 interrupt service routine
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{

	 display();
}

void main(void) {
		float x;
		int vol;
		WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
		InitializeClocks();
		initPort();

		initTimer();

		configureAdc();

	  	  while(1)
	  	  	  {
	  		  ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	  		  /* Moving average filter out of 8 values to somewhat stabilize sampled ADC */
	  		  adcMeasured[count++] = ADC10MEM;
	  		  if (count == 8)
	  			  count = 0;

	  		  adcAverage = 0;
	  		  for (i = 0; i < 8; i++)
	  			  adcAverage += adcMeasured[i];

	  		  adcAverage >>= 3;                      // Divide by 8 to get average

	  		  x=adcAverage;
	  		  x = (x*30)/1023;
	  		  vol =x*10;
	  		  digits[0]= 0xE0 | vol%10;
	  		  vol=vol/10;
	  		  digits[1]= 0xD0 | vol%10;
	  		  vol=vol/10;
	  		  digits[2]= 0xB0 | vol;
	  		  __delay_cycles(9999);
	  		  __delay_cycles(9999);
	  		  __delay_cycles(9999);
	  	  	  }
}

void display(void )
{

        P1OUT |=0x70;  //switch off segment 1 segment 2  segment 3
		if (digit>=3)
		digit=0;
		P1OUT = digits[digit] ;
		digit++;
}

void initTimer(void)
{

	TACCR0=810;
	TACCTL0 = CCIE;
	TACTL = MC_1|ID_3|TASSEL_2|TACLR;
	__enable_interrupt();
	__bis_SR_register(GIE);

}
void configureAdc(void)
{
  unsigned char i;
  /* Configure ADC Temp Sensor Channel */
  ADC10CTL1 = INCH_7 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON  + REF2_5V;
  __delay_cycles(1000);                     // Wait for ADC Ref to settle
  ADC10AE0 |= BIT7;
  ADC10CTL0 |= ENC + ADC10SC;               // Sampling and conversion start

  adcCalibrated = ADC10MEM;
  for (i=0; i < 8; i++)
    adcMeasured[i] = adcCalibrated;
  adcAverage = adcCalibrated;
}

void InitializeClocks(void)
{

  BCSCTL1 = CALBC1_1MHZ;                    // Set range
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_3);                         // SMCLK = DCO / 8 = 1MHz
}

void initPort(void)
{
	P1DIR = 0x7F;
}
