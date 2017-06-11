/* 
 * File:   teclado.h
 * Author: Fabian
 *
 * Created on 14 de mayo de 2017, 11:46 PM
 */
#ifndef LCD_H
#define	LCD_H

#define RS        LATEbits.LATE1     //Se debe de definir el Pin Usado para RS
#define EN        LATEbits.LATE2       //Se debe de definir el pin Usado para E
#define TRISRS    TRISEbits.TRISE1    //Se define el Tris para el RS Para poderlo configurar como Salida
#define TRISEN    TRISEbits.TRISE2    //Se define el Tris para el E Para poderlo configurar como Salida
#define PUERTOTRS TRISD// Se define el TRIS del puerto que se usa como interfaz en este caso el Puerto C
#define PUERTO    LATD    // Se define El LAT del puerto que se usa como interfaz en este caso el D
#define _XTAL_FREQ 8000000
void lcd_init();
void lcd_control(char);
void lcd_dato(char);
void lcd_clear_diplay();
void lcd_cursor_home();
void lcd_print(char*);
void lcd_print_with_position(int, int, char*);
void lcd_goto(int, int);
void lcd_put_caracter(char, char[]);
void lcd_time_control();

/*
 * Configuracion de Puertos
 * Iniciliaza el los puertos requeridos para el LCD
 * Ademas lo inicializa a 4 Bits


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pic18f4550.h"
#include "delays.h"
*/
#endif	/* LCD_H */