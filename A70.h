#ifndef A70_H
#define A70_H

/*=======================================================================
*
*	Autor: Mateusz Rrozmus, mt.rozmus@wp.pl, https://github.com/mt-rozi
*
*	Z biblioteki mozna korzystac na zasadzie wolnego oprogramowania,
*	jedyna prosba to jest nie usuwanie informacji o autorze.
*	
*	Biblioteka ta umozliwia obsulge ekranu LCD z telefonu Siemens A70,
*	posiada wbudowany sterownik PCF8812.
*
*=======================================================================*/


#include <avr/io.h>
#include <compat/deprecated.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "font_A70.h"


/*---------------------------------------------------------
* Definicja wielkosci LCD
*---------------------------------------------------------*/
#define LCD_X	102
#define LCD_Y	9

/*========================================================
* Definicje Portów
*=========================================================*/

/* CE-chip enable */
#define LCD_CE_HIGH			PORTD	 |=  (1<<PD0)
#define LCD_CE_LOW			PORTD	 &= ~(1<<PD0)
#define LCD_CE_SET_OUT		DDRD 	 |=  (1<<PD0)

/* RST-reset */
#define LCD_RST_HIGH		PORTD	 |=  (1<<PD1)
#define LCD_RST_LOW			PORTD	 &= ~(1<<PD1)
#define LCD_RST_SET_OUT		DDRD 	 |=  (1<<PD1)

/* DC-data or command */
#define LCD_DC_HIGH			PORTD	 |=  (1<<PD2)
#define LCD_DC_LOW			PORTD	 &= ~(1<<PD2)
#define LCD_DC_SET_OUT		DDRD 	 |=  (1<<PD2)

/* CLK-clock */
#define LCD_CLK_HIGH		PORTD	 |=  (1<<PD3)
#define LCD_CLK_LOW 		PORTD	 &= ~(1<<PD3)
#define LCD_CLK_SET_OUT		DDRD	 |=  (1<<PD3)

/* DATA-data input */
#define LCD_DATA_HIGH		PORTD	 |=  (1<<PD4)
#define LCD_DATA_LOW 		PORTD	 &= ~(1<<PD4)
#define LCD_DATA_SET_OUT	DDRD	 |=  (1<<PD4)

/*========================================================
* Definicje funkcji
*=========================================================*/
void LCD_Init(void);					// Inizjalizacja LCD
void LCD_Reset(void);					// Reset LCD
void LCD_Command(unsigned char data);	// Wyslanie komendy do LCD
void LCD_Write(unsigned char data);		// Wyslanie bajtu do wyswietlenia
void LCD_Clear(void);					// Czyszczenie LCD

/*=========================================================
 * Funckje wyswietlajace znaki, napisy
 *=========================================================*/
/*---------------------------------------------------------
 * 0 < x < 101		0 < y < 8
 *--------------------------------------------------------*/
void LCD_Gotoxy(unsigned int x, unsigned int y);	// Ustawienie w ktorym punkcie wyswietlic napis
void LCD_Paint_Char(unsigned char k);				//Wypisuje znak o numerze jak w ASCI, ale tylko od numeru dec(32)
void LCD_Paint_Text(char data[], unsigned char x, unsigned char y); //Wypisuje napis

#endif
