#include "A70.h"

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


/*========================================================
* Funckja Inicjalizujaca ekran
*=========================================================*/
void LCD_Init(void)
{
	LCD_RST_SET_OUT;
	LCD_CLK_SET_OUT;
	LCD_DATA_SET_OUT;
	LCD_DC_SET_OUT;
	LCD_CE_SET_OUT;

	LCD_Reset();

	LCD_Command(0x21); // Function set: extended instruction set
	LCD_Command(0x14); // Bias System
	LCD_Command(0x0A); // HV-gen stages
	LCD_Command(0x05); // Temperature Control
	LCD_Command(0xCC); // Contrast
	LCD_Command(0x20); // Function set: standard instruction set
	LCD_Command(0x11); // VLCD programming range: high
	LCD_Command(0x0C); // Display control: normal (inverted = 0x0D)
}

/*========================================================
* Funckja resetujaca ekran
*=========================================================*/
void LCD_Reset(void)
{
	  _delay_us(10);
	  LCD_DATA_LOW;
	  LCD_CLK_LOW;
	  LCD_DC_LOW;
	  _delay_us(10);
	  LCD_RST_HIGH;
	  _delay_us(10);
	  LCD_CE_LOW;
	  _delay_us(10);
	  LCD_RST_LOW;
	  _delay_us(10);
	  LCD_RST_HIGH;
	  LCD_CE_HIGH;
}

/*========================================================
* Funkcja wysylania comendy do ekranu
*=========================================================*/
void LCD_Command(unsigned char data)
{
	unsigned char m; 

	LCD_DATA_LOW;
	LCD_CLK_LOW;
	LCD_CE_LOW;
	LCD_DC_LOW;

	for(m=0x80; m; m>>=1)
	{		
		if(data & m)
			LCD_DATA_HIGH; 
		else 
			LCD_DATA_LOW; 
		
		LCD_CLK_LOW;
		_delay_us(2);
		LCD_CLK_HIGH;
	}
	LCD_CE_HIGH;
}

/*========================================================
* Funckja do wypisywania bajtu na ekran
*=========================================================*/
void LCD_Write(unsigned char data)
{
	unsigned char m; 

	LCD_DATA_LOW;
	LCD_CLK_LOW;
	LCD_CE_LOW;
	LCD_DC_HIGH;

	for(m=0x80; m; m>>=1)
	{		
		if(data & m)
			LCD_DATA_HIGH; 
		else 
			LCD_DATA_LOW; 
		
		LCD_CLK_LOW;
		_delay_us(2);
		LCD_CLK_HIGH;
	}
	LCD_CE_HIGH;
}

/*========================================================
* Funkcja czyszczaca ekran
*=========================================================*/
void LCD_Clear(void)
{
	unsigned int i;
	for(i=0;i<(LCD_X*LCD_Y-1);i++)
	{
		LCD_Write(0x00);
	}
}

/*========================================================
* Funkcja ustawiajca poloznie na ekranie
*=========================================================*/
void LCD_Gotoxy(unsigned int x, unsigned int y)
{
	LCD_Command(0b10000000 | x);
	LCD_Command(0b01000000 | y);
}

/*========================================================
* Funkcja wypisujaca znak ASCI
*=========================================================*/
void LCD_Paint_Char(unsigned char k)
{
	unsigned int i;

	for(i=(k-32)*8;i<((k-32)*8+8);i++)
	{
		LCD_Write(pgm_read_byte(&code8x8[i]));
	}

}

/*========================================================
* Funckja wypisujaca tekst na podstawie znakow ASCI
*=========================================================*/
void LCD_Paint_Text(char data[], unsigned char x, unsigned char y)
{
	unsigned char k,i=0;

	LCD_Gotoxy(x,y);
	while(data[i]!='\0') i++;

	for(k=i-1; data[k]!='\0'; k--)
	{
		LCD_Paint_Char(data[k]);
	}
}
