#include <xc.inc>
; CONFIG1H
  CONFIG  FOSC = HS             ; Oscillator Selection bits (HS oscillator (HS))
; CONFIG2L
  CONFIG  PWRT = ON            ; Power-up Timer Enable bit (PWRT disabled)
; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
  CONFIG  PBADEN = OFF          ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)

PSECT _main, CLASS = CODE, reloc=2
 
 _main:
    goto STARTMAIN
    
  PSECT CODE
STARTMAIN:
    ;Configuracion de puerto D como salidas digitales
    CLRF PORTD
    CLRF LATD
    CLRF TRISD
    ;Configuracion de puerto C como salidas digitales
    CLRF PORTC
    CLRF LATC
    SETF TRISC
     ;Configuracion de puerto E como salidas digitales
    CLRF PORTE
    CLRF LATE
    SETF TRISE
    ;Configuracion de puerto B como entrada digitales
    CLRF PORTB
    CLRF LATB
    CLRF TRISB
    ;configuracion de puerto A como entrada digital
    CLRF PORTA
    CLRF LATA
    MOVLW 0x0F
    MOVWF ADCON1
    MOVLW 0b00000111
    MOVWF CMCON
    SETF TRISA
    
LOOP:

    BTFSC PORTC, 1        ; Comprueba si RA0 es 0
    GOTO ENCENDER_LED1    ; Si no es 0 (es 1), va a ENCENDER_LED1
    GOTO ENCENDER_LED2    ; Si es 0, va a ENCENDER_LED2
    
ENCENDER_LED1:
    BSF PORTD, 0          
    BCF PORTD, 1          
    GOTO REVISAR_S2
    
ENCENDER_LED2:	
    BCF PORTD, 0          
    BSF PORTD, 1  
    GOTO REVISAR_S2
    
REVISAR_S2:
    BTFSC PORTA, 1        
    GOTO ENCENDER_LED3    
    GOTO ENCENDER_LED4	       
    
ENCENDER_LED3:	
    BSF PORTD, 2         
    BCF PORTD, 3
    GOTO REVISAR_S3
      
ENCENDER_LED4:
    BCF PORTD, 2         
    BSF PORTD, 3
    GOTO REVISAR_S3
    
REVISAR_S3:
    BTFSC PORTC, 0        
    GOTO ENCENDER_LED5    
    GOTO ENCENDER_LED6	       
    
ENCENDER_LED5:	
    BSF PORTD, 4         
    BCF PORTD, 5
    GOTO REVISAR_S4
      
ENCENDER_LED6:
    BCF PORTD, 4         
    BSF PORTD, 5
    GOTO REVISAR_S4

REVISAR_S4:
    BTFSC PORTA, 3        
    GOTO ENCENDER_LED7    
    GOTO ENCENDER_LED8	       
    
ENCENDER_LED7:	
    BSF PORTD, 6         
    BCF PORTD, 7
    GOTO REVISAR_S5
      
ENCENDER_LED8:
    BCF PORTD, 6         
    BSF PORTD, 7
    GOTO REVISAR_S5
    
REVISAR_S5:
    BTFSC PORTE, 2         
    GOTO ENCENDER_LED9    
    GOTO ENCENDER_LED10	       
    
ENCENDER_LED9:	
    BSF PORTB, 0         
    BCF PORTB, 1
    GOTO REVISAR_S6
      
ENCENDER_LED10:
    BCF PORTB, 0         
    BSF PORTB, 1
    GOTO REVISAR_S6
    
REVISAR_S6:
    BTFSC PORTA, 5        
    GOTO ENCENDER_LED11    
    GOTO ENCENDER_LED12	       
    
ENCENDER_LED11:	
    BSF PORTB, 2         
    BCF PORTB, 3
    GOTO REVISAR_S7
      
ENCENDER_LED12:
    BCF PORTB, 2         
    BSF PORTB, 3
    GOTO REVISAR_S7
    
REVISAR_S7:
    BTFSC PORTE, 0        
    GOTO ENCENDER_LED13    
    GOTO ENCENDER_LED14	       
    
ENCENDER_LED13:	
    BSF PORTB, 4         
    BCF PORTB, 5
    GOTO REVISAR_S8
      
ENCENDER_LED14:
    BCF PORTB, 4         
    BSF PORTB, 5
    GOTO REVISAR_S8
    
REVISAR_S8:
    BTFSC PORTE, 1        
    GOTO ENCENDER_LED15    
    GOTO ENCENDER_LED16	       
    
ENCENDER_LED15:	
    BSF PORTB, 6         
    BCF PORTB, 7
    GOTO LOOP
      
ENCENDER_LED16:
    BCF PORTB, 6         
    BSF PORTB, 7
    GOTO LOOP
    
    END


