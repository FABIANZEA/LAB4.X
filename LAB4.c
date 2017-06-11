/*
 * File:   LAB4.c
 * Author: FABIAN ZEA Y JHONATAN GOMEZ
 *
 * Created on 14 de mayo de 2017, 11:40 PM
 */


#include <xc.h>
#include "lcd.h"
#include "configuraciones.h"
#include "pic18f4550.h"
#include "delays.h"
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <eeprom_routines.h>
#define _XTAL_FREQ 8000000

//-------------------VARIABLES PARA USAR DENTRO DEL PROGRAMA-----------------------
    int tecla=255,opcion=0,centenas=0,decenas=0,unidades=0,frecuencia=255;
    
//-------------------INTERRUPCION DONDE SE TESTEA EL PUERTO B Y OBTENER EL VALOR DE LA TECLA OPRIMIDA-----------------------
void interrupt ISR(void)
{
    if(INTCONbits.RBIF==1 && INTCONbits.RBIE==1)
    {
        if(PORTB!=0XF0)
        {
        PORTB=0xFE;	// Saca 0 a Fila 1
            if(RB4 == 0){tecla = 1;}	
            if(RB5 == 0){tecla = 2;}	
            if(RB6 == 0){tecla = 3;}	
            if(RB7 == 0){tecla = 11;}	
        PORTB=0xFD;	// Saca 0 a Fila 2
            if(RB4 == 0){tecla = 4;}	
            if(RB5 == 0){tecla = 5;}	
            if(RB6 == 0){tecla = 6;}	
            if(RB7 == 0){tecla = 12;}	
        PORTB=0xFB;	// Saca 0 a Fila 3
            if(RB4 == 0){tecla = 7;}	
            if(RB5 == 0){tecla = 8;}	
            if(RB6 == 0){tecla = 9;}	
            if(RB7 == 0){tecla = 13;}
        PORTB=0xF7;	// Saca 0 a Fila 4
            if(RB4 == 0){tecla = 15;}	
            if(RB5 == 0){tecla = 0;}	
            if(RB6 == 0){tecla = 10;}	
            if(RB7 == 0){tecla = 14;}
        }

        LATB=0XF0;
        INTCONbits.RBIF=0;

    }
    PIE2=0X00;
    PIR2=0X00;
}

//-------------------RUTINA DONDE SE INGRESA Y SE GUARDA LA FRECUENCIA A LA QUE SE VA A TRABAJAR-----------------------
int ingresar_frecuencia(void){
    lcd_clear_display();
    lcd_goto(1,1);
        lcd_print("INGRESE LA     ");
    lcd_goto(1,2);   
        lcd_print("FREC.:    Hz");
        //CENTENAS
        ONE:
        //PRIMERA POSICION PARA INGRESAR EL VALOR DE CENTENA
        lcd_goto(7,2);
        while (tecla>9){
        }
        //GUARDA EL VALOR EN CENTANAS Y MUESTRA
        centenas=tecla;
        _EEREG_EEPROM_WRITE(1,centenas);
        lcd_dato(centenas+48);
        two: 
        tecla=255;
       //DECENAS
        while (tecla>10){
            //key=leer_teclado(); 
        }
        
        if (tecla==10){
            goto ONE;
        }
        //GUARDA EL VALOR EN DECENAS Y MUESTRA
        decenas=tecla;
        _EEREG_EEPROM_WRITE(2,decenas);
        lcd_dato(decenas+48);
        three:
        tecla=255;
        //UNIDADES
        while (tecla>10){
        }
        if (tecla==10){
            lcd_goto(8,2);
            goto two;
        }
        //GUARDA EL VALOR EN UNIDADES Y MUESTRA
        unidades=tecla;
        _EEREG_EEPROM_WRITE(3,unidades);
        lcd_dato(unidades+48);
        
        while (tecla!=15 && tecla!=10){
            //key=leer_teclado(); 
        }
        
        if (tecla==10){
            lcd_goto(9,2);
            goto three;
        }
        frecuencia=unidades+10*decenas+100*centenas;
        _EEREG_EEPROM_WRITE(4,frecuencia);
}

//-------------------FUNCION RAMPA-----------------------

int rampa(int frecu){
    
    
    if (frecu>=20){
       int j=0;
        j=9140.8*pow(frecu,-1.43); 
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=255;i++){
                LATA=i;
                LATC=i;
                Delay1TCYx(j);

            } 
        }
    }
    if (frecu < 20 && frecu >= 2){
        int q=0;
        q=261.5*pow(frecu,-1.175);
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=255;i++){
                LATA=i;
                LATC=i;
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
                Delay1TCYx(q);
            }       
}
    
    }
    if (frecu =1){
        int q=0;
        q=261.5*pow(frecu,-1.175);
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=255;i++){
                LATA=i;
                LATC=i;
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
                Delay10TCYx(75);
            }       
}
    
    }
}
//-------------------FUNCION CUADRADA-----------------------

int cuadrada(int frec){
    if (frec >=50){
        int z=0;
        z=11051/pow(frec,1.034);
        while (tecla!=11 && tecla!=12){
              LATA=0;
              LATC=0;
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              LATA=255;
              LATC=255;
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
              Delay10TCYx(z);
        }
    }
    if (frec <50 && frec >=6){
    int h=0;
        h=1076.7/pow(frec,0.966);
    while (tecla!=11 && tecla!=12){
    LATA=0;
    LATC=0;
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    LATA=255;
    LATC=255;
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    Delay100TCYx(h);
    }
    }
    
    if (frec <6){
    int x=0;
        x=124.81/frec;
    while (tecla!=11 && tecla!=12){
    LATA=0;
    LATC=0;
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    LATA=255;
    LATC=255;
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    Delay1KTCYx(x);
    }
    }
}
//-------------------FUNCION SENO-----------------------
int seno[36]={127,147,166,184,201,217,232,246,255,
              255,255,246,232,217,201,184,166,147,127,
              107,88,70,53,37,22,8,0,0,0,8,22,37,53,
              70,88,107};


int sen(int frecuen){

    if (frecuen >=40){
        int b=0;
        b=12686*pow(frecuen,-1.59);
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=35;i++){
                LATA =seno[i];
                LATC =seno[i]; 
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
                Delay1TCYx(b);
            }
        }
    }
    if (frecuen <40 && frecuen >= 3){
        int t=0;
        t=571.24*pow(frecuen,-1.061);
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=35;i++){
                LATA =seno[i];
                LATC =seno[i];    
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
                Delay10TCYx(t);
            }
        }
    }
    if (frecuen <3){
        while (tecla!=11 && tecla!=12){
            for(int i=0;i<=35;i++){
                LATA =seno[i];
                LATC =seno[i];    
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
                Delay100TCYx(68/frecuen);
            }
        }
    }
}
//--------------------PROGRAMA PRINCIPAL----------------------------------------------

void main(void) {
    
//--------------------CONFIGURACION DE PUERTOS----------------------------------------------
	ADCON1=0x06;			        //Hay que configurar PA0-3 como digitales
    OSCCONbits.IRCF =7;
    TRISA=0X00;
    TRISC=0X00;                     //Configura el PORTA como salida de las señales
    TRISB=0xF0; 
	TRISD=0x00; 					//Configura el PORTD como salida para lcd
	TRISE=0X00;                     //Configura el PORTE como salidas para lcd
    					//Configura como salidas RB0-RB3 y como entradas RB4-RB7 para el teclado
	PORTB=0XF0;
    PORTC=0X00;
    PORTA=0X00;
    PORTE=0X00;
    INTCON2bits.nRBPU = 0; 			//Habilita RESIS. De pull-up internas del puerto B.
    INTCONbits.RBIE=1;
    INTCONbits.RBIF=0;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    lcd_init();
    __delay_ms(10);
    lcd_clear_display();
//--------------------MENSAJE DE BIENVENIDA---------------------------------------------- 
        lcd_goto(1,1);
        lcd_print("GENERADOR DE    ");
        lcd_goto(1,2);
        lcd_print("----SENIALES----");
        opcion=_EEREG_EEPROM_READ(0);
        while (tecla!=15){

        }
        
        if(opcion!=255){
            frecuencia=_EEREG_EEPROM_READ(4);
            goto PRINCIPAL;
        }
//--------------------MENU PRINCIPAL---------------------------------------------- 
        MENU_PRINCIPAL:
        
            lcd_clear_display();
        lcd_goto(1,1);
        lcd_print("1.RAMPA 2.CUADRA");
        lcd_goto(1,2);
        lcd_print("3.SENO4.RESET:  ");
        a:
        tecla=255;
        lcd_goto(15,2);
        while (tecla!=1 && tecla!=2 && tecla!=3 && tecla!=4){
        }
        opcion=tecla;
        _EEREG_EEPROM_WRITE(0,opcion);
        lcd_dato(tecla+48);
        while (tecla!=10 && tecla!=15){
        }
        
        if (tecla==10){
            goto a;
        }
        PRINCIPAL:
        //--------------------OPCION PARA GENERAR FUNCION DIENTE DE SIERRA---------------------------------------------- 
        if(opcion==1){
            
            if(frecuencia!=255){
                goto SALIR1;
            }
            opc1:
                ingresar_frecuencia();
            
            SALIR1:               
                lcd_clear_display();
                lcd_goto(1,1);
                lcd_print("SENIAL RAMPA");
                lcd_goto(1,2);
                lcd_print("FREC.=    Hz");
                lcd_goto(7,2);
                centenas=_EEREG_EEPROM_READ(1);
                lcd_dato(centenas+48);
                decenas=_EEREG_EEPROM_READ(2);
                lcd_dato(decenas+48);
                unidades=_EEREG_EEPROM_READ(3);
                lcd_dato(unidades+48);
                frecuencia=_EEREG_EEPROM_READ(4);
                rampa(frecuencia);
                if(tecla==11){
                    goto opc1;
                }
                goto MENU_PRINCIPAL;
        }
        //--------------------OPCION PARA GENERAR FUNCION CUADRADA---------------------------------------------- 
       if(opcion==2){
            
            if(frecuencia!=255){
                goto SALIR2;
            }
            opc2:
                ingresar_frecuencia();
            SALIR2: 
                lcd_clear_display();
                lcd_goto(1,1);
                lcd_print("SENIAL CUADRADA");
                lcd_goto(1,2);
                lcd_print("FREC.=    Hz");
                lcd_goto(7,2);
                centenas=_EEREG_EEPROM_READ(1);
                lcd_dato(centenas+48);
                decenas=_EEREG_EEPROM_READ(2);
                lcd_dato(decenas+48);
                unidades=_EEREG_EEPROM_READ(3);
                lcd_dato(unidades+48);
                frecuencia=_EEREG_EEPROM_READ(4);
                cuadrada(frecuencia);
                if(tecla==11){
                    goto opc2;
                }
                goto MENU_PRINCIPAL;
        }
        //--------------------OPCION PARA GENERAR FUNCION SENO---------------------------------------------- 
       if(opcion==3){
            
            if(frecuencia!=255){
                goto SALIR3;
            }
            opc3:
                ingresar_frecuencia();
            SALIR3:
                lcd_clear_display();
                lcd_goto(1,1);
                lcd_print("SENIAL SENO");
                lcd_goto(1,2);
                lcd_print("FREC.=    Hz");
                lcd_goto(7,2);
                centenas=_EEREG_EEPROM_READ(1);
                lcd_dato(centenas+48);
                decenas=_EEREG_EEPROM_READ(2);
                lcd_dato(decenas+48);
                unidades=_EEREG_EEPROM_READ(3);
                lcd_dato(unidades+48);
                frecuencia=_EEREG_EEPROM_READ(4);
                sen(frecuencia);
                if(tecla==11){
                    goto opc3;
                }
                goto MENU_PRINCIPAL;
        }
         //--------------------OPCION PARA RESETEAR---------------------------------------------- 
        if (opcion==4){
         _EEREG_EEPROM_WRITE(0,255);
         _EEREG_EEPROM_WRITE(1,255);
         _EEREG_EEPROM_WRITE(2,255);
         _EEREG_EEPROM_WRITE(3,255);
         _EEREG_EEPROM_WRITE(4,255);
         frecuencia=255;
         lcd_clear_display();
         lcd_goto(1,1);
         lcd_print("BORRADO EXITOSO");
         tecla=255;
         while(tecla!=15){
         }
         goto MENU_PRINCIPAL;
        }
}
