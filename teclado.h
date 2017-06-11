/* 
 * File:   teclado.h
 * Author: Fabian
 *
 * Created on 14 de mayo de 2017, 11:46 PM
 */

#ifndef TECLADO_H
#define	TECLADO_H
#define _XTAL_FREQ 8000000			

int leer_teclado(void){ 
    int tecla;

	PORTB=0xFE;	// Saca 0 a Fila 1
	if(RB4 == 0){tecla = 7;}	
	if(RB5 == 0){tecla = 8;}	
	if(RB6 == 0){tecla = 9;}	
	if(RB7 == 0){tecla = 11;}	
	PORTB=0xFD;	// Saca 0 a Fila 2
	if(RB4 == 0){tecla = 4;}	
	if(RB5 == 0){tecla = 5;}	
	if(RB6 == 0){tecla = 6;}	
	if(RB7 == 0){tecla = 12;}	
	PORTB=0xFB;	// Saca 0 a Fila 3
	if(RB4 == 0){tecla = 1;}	
	if(RB5 == 0){tecla = 2;}	
	if(RB6 == 0){tecla = 3;}	
	if(RB7 == 0){tecla = 13;}
	PORTB=0xF7;	// Saca 0 a Fila 4
	if(RB4 == 0){tecla = 15;}	
	if(RB5 == 0){tecla = 0;}	
	if(RB6 == 0){tecla = 10;}	
	if(RB7 == 0){tecla = 14;}	
    return(tecla);
	}

#endif	/* TECLADO_H */

