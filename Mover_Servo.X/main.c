/*
 * Temporizacion = 20ms = 4/Fosc * Prescaler * x+1 
 * 20ms = 4/20MHz * 8 * Y
 *  Y = 12500 
 * 65535 - 12500 = 53035 
 * 
 * 18ms: 0?
 * 18ms = 4/Fosc * Prescaler * x+1 
 * Y = 11250
 * 65535 - 11250 = 54285
 * 
 * 19ms: 180?
 * 19ms = 4/Fosc * Prescaler * x+1 
 * Y = 11875
 * 65535-11875 = 53660
 * 
 * 
 * 18,5ms: 90?
 * 18,5ms = 4/Fosc * Prescaler * x+1 
 * Y = 11562.5
 * 65535-11562.5 = 53972.5
 */

#include <stdio.h>
#include <xc.h>
#include "configuration.h"

unsigned int contador=0;
unsigned int Radc=0;
float LDR=0;
unsigned long resistencia=0;

void Timer0_Init(void);

void initPort(void){
    ADCON1bits.PCFG = 0x0F;
    LATD = 0x00;
    LATB = 0x00;
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    INTCON2bits.RBPU = 0;
    TRISD = 0x00;
}

void main(void) {
    initPort();
    TMR0L = 0x2B;
    TMR0H = 0xCF;
    TRISAbits.RA0=1;
    TRISD=0x00;
    
    //conf ADC
    ADCON1bits.PCFG=0b1110;
    ADCON1bits.VCFG=0b00;
    ADCON2bits.ADCS=0b001;
    ADCON2bits.ACQT=0b010;
    ADCON2bits.ADFM=1;
    ADCON0bits.ADON=1;
    ADCON0bits.CHS=0b0000;
    
    __delay_ms(200);
    Timer0_Init();
    while(1){
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        Radc=ADRESH;
        Radc=Radc<<8;
        Radc|=ADRESL;
        LDR=(48.8758*Radc)/(5.0-(0.00488758*Radc));
        resistencia=LDR;
        if(resistencia>3000){
            LATDbits.LATD0=1;
        }else{
            LATDbits.LATD0=0;
        }
    __delay_ms(500);
    }
}

void Timer0_Init(void){
    INTCONbits.GIE = 0;
    T0CONbits.T0CS = 0; // Temporizador
    T0CONbits.PSA = 0; // Habilitamos Pre escaler
    T0CONbits.T0PS = 0b010; //8 Pre escaler
    T0CONbits.T08BIT = 0; // 16 bits de cuenta 
    INTCONbits.TMR0IF = 0; //Flag del Timer 0 apagado
    INTCONbits.TMR0IE = 1; // Permitir el desbordamiento del Timer0
    INTCONbits.PEIE = 1; // Interrupciones de perifericos
    INTCONbits.GIE = 1;
    T0CONbits.TMR0ON = 1; // Tmr0 empieza
}

void __interrupt() Timer_INT(void){
    if(INTCONbits.TMR0IF){
        if(contador<2){
        if(PORTBbits.RB0 != 1){
            contador++;
            LATDbits.LATD1 = 1;
            __delay_ms(2);
            LATDbits.LATD1 = 0;
            TMR0L = 0x0D;
            TMR0H = 0xD4;
            INTCONbits.TMR0IF = 0;
            
            __delay_ms(4000);
            
            LATDbits.LATD1 = 1;
            __delay_ms(1.5);
            LATDbits.LATD1 = 0;
            TMR0L = 0xD4;
            TMR0H = 0xD2;
            INTCONbits.TMR0IF = 0;
    
        }
        else{
            LATDbits.LATD1 = 1;
            __delay_ms(1.5);
            LATDbits.LATD1 = 0;
            TMR0L = 0xD4;
            TMR0H = 0xD2;
            INTCONbits.TMR0IF = 0;
        }
    
        if(PORTBbits.RB1 != 1){
            contador--;
            LATDbits.LATD2 = 1;
            __delay_ms(2);
            LATDbits.LATD2 = 0;
            TMR0L = 0x0D;
            TMR0H = 0xD4;
            INTCONbits.TMR0IF = 0;
            
            __delay_ms(4000);
            
            LATDbits.LATD2 = 1;
            __delay_ms(1.5);
            LATDbits.LATD2 = 0;
            TMR0L = 0xD4;
            TMR0H = 0xD2;
            INTCONbits.TMR0IF = 0;
    
        }
        else{
            LATDbits.LATD2 = 1;
            __delay_ms(1.5);
            LATDbits.LATD2 = 0;
            TMR0L = 0xD4;
            TMR0H = 0xD2;
            INTCONbits.TMR0IF = 0;
        }
        }else{
            if(PORTBbits.RB1 != 1){
            contador--;
            LATDbits.LATD2 = 1;
            __delay_ms(2);
            LATDbits.LATD2 = 0;
            TMR0L = 0x0D;
            TMR0H = 0xD4;
            INTCONbits.TMR0IF = 0;
            
            __delay_ms(4000);
            
            LATDbits.LATD2 = 1;
            __delay_ms(1.5);
            LATDbits.LATD2 = 0;
            TMR0L = 0xD4;
            TMR0H = 0xD2;
            INTCONbits.TMR0IF = 0;
    
        }
            
        }
    }
}
