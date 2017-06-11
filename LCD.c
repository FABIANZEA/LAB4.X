/*
 * File:   LCD.c
 * Author: Liliana
 *
 * Created on 30 de mayo de 2017, 10:20 PM
 */


#include <xc.h>
#include "lcd.h"
#define _XTAL_FREQ 8000000


void lcd_init() {
    TRISRS = 0; //Configuramos el Pin RS como salida
    TRISEN = 0; //Configuramos el Pin E como salida
    PUERTOTRS = 0; //Configuramos El nibble mas significativo como Salidas (Bus de 4 Bits))
    RS = 0; //Aseguramos RS en 0            
    EN = 0; //Aseguramos E en 0
    PUERTO = 0; //Aseguramos el Puerto de datos en 0
    /*
     * Configuracion del control del LCD
     */
    __delay_ms(50); // Tiempo de espera a que se estabilicen los puertos
    lcd_control(0x38); //Configura el LCD a 8 Bits, 2 Lineas Y Fuente de 5*8; Lineas Esto se llama el function set
    lcd_control(0x0D); //LCD Prendido, Cursor Apagado, Destello Cursor apagado; Esto se Llama Diplay on/off Control
    lcd_control(0x06); //No rota el mensaje Y se incrementa el contador de direccion. Esto se Llama Entry Mode Set
    lcd_control(0x01);
}

/*
 * Esta rutina se encarga de tomar un dato y ponerlo en el puerto de datos
 * teniendo en cuenta que es a 4 bits, por lo tanto tiene que hacer cambio de ninbles
 * primer se envia el nible mas significativo y luego se envia el menos significativo
 */
void lcd_control(char dato) {
    RS = 0;
    PUERTO =dato;
    lcd_time_control();
    __delay_ms(10);
    RS=1;
}

/*
 * Está rutina se encarga de tomar un dato y ponerlo sobre el puerto de datos
 * especificamente para escribir un caracter sobre el LCD
 * 
 */
void lcd_dato(char dato) {
    RS = 1;
    PUERTO =dato;
    lcd_time_control();
    __delay_ms(10);
}

/*
 * Rutina encargada de limpiar el LCD
 */
void lcd_clear_display() {
    lcd_control(0x01);
}

/*
 * El puntero regresa al inicio sin modificar los datos del LCD
 */
void lcd_cursor_home() {
    lcd_control(0x02);
}

/*
 * Imprime una cadena de caractres en el LCD
 */
void lcd_print(char *dato) {
    while (*dato) // Mientras no sea Null
    {
        lcd_dato(*dato); // Envio el dato al LCD
        dato++; // Incrementa el buffer de dato
    }
}

/*
 * Imprime una cadena de caracteres en la pisicion X y Y que se le pasen
 */
void lcd_print_with_position(int x, int y, char *dato) {
    char posicion;
    switch (y) {
        case 1: posicion = 0x80 + x;
            break;
        case 2: posicion = 0xC0 + x;
            break;
        default: posicion = 0x80 + x;
            break;
    }
    lcd_control(posicion);
    lcd_print(dato);
}

/*
 * Pone el puntero en la posicion deseada
 */
void lcd_goto(int x, int y) {
    char posicion;
    switch (y) {
        case 1: posicion = 0x80 + x;
            break;
        case 2: posicion = 0xC0 + x;
            break;
        default: posicion = 0x80 + x;
            break;
    }
    lcd_control(posicion);
}

/*
 * Guardar caracteres especiales. en la CGRAM
 */
void lcd_put_caracter(char adress, char caracter[]) {
    int i;
    lcd_control(0x40 + (adress * 8));
    for (i = 0; i < 8; i++) {
        lcd_dato(caracter[i]);
    }
}

/*
 * Genera un Pulso de control Ese pulso es un pulso de E a 1 milisegundos
 */
void lcd_time_control() {
    EN = 1;
    __delay_ms(10);
    EN = 0;
    __delay_ms(10);
}
