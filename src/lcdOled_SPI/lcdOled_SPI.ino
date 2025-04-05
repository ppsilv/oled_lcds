/**************************************************************************
  Escrito por Limor Fried/Ladyada para Adafruit Industries.
  Modificado por Gedeane Kenshima
  Data: 04/07/2021

VCC: Provides power to the OLED module, typically 3.3V or 5V. 
GND: Ground connection for the module. 
D0/SCLK: SPI clock pin (for SPI communication) or I2C clock pin (for I2C communication). 
D1/MOSI/SDA: SPI data in pin (for SPI communication) or I2C data pin (for I2C communication). 
DC: Data/Command pin, used to tell the display whether the data being sent is a command or data. 
RES: Reset pin, used to reset the OLED display. 
CS: (Chip Select): (SPI only) Used to select the OLED module for communication. 

 **************************************************************************/
 
#include <Adafruit_GFX.h>	// Biblioteca gráfica Adafruit
#include <Adafruit_ST7735.h> // Biblioteca específica para ST7735
#include <Adafruit_ST7789.h> // Biblioteca específica para ST7789
#include <SPI.h>         	// Biblioteca para comunicação SPI
 
// Definição dos pinos SPI
#define TFT_CS        10  
#define TFT_RST        9
#define TFT_DC         8
// Pinos SDA em 11 e SCL em 13
/*
SDA/MOSI/D1 = 11
CLK/D0      = 13 

*/ 


// Criação do objeto tft para displays com ST7735:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
// Variável p com valor de pi
float p = 3.1415926;
 
void setup(void) {
  // Início da comunicação Serial com 9600 bits por segundo
  Serial.begin(9600);
  // Mensagem inicial exibida no Monitor Serial
  Serial.println(F("Ola! Teste para TFT ST77xx"));
 
  // Inicialização do display IPS LCD 0.96" 160x80:
  tft.initR(INITR_MINI160x80);
 
  Serial.println(F("Inicializado"));
 
  // Usa millis para contagem de tempo
  uint16_t time = millis();
  // Preenche a tela com a cor preta
  tft.fillScreen(ST77XX_BLACK);
  // Realiza contagem de tempo atual
  time = millis() - time;
 
  // Exibe tempo atual em decimal
  Serial.println(time, DEC);
  // Aguarda 500 ms
  delay(500);
 
  // Gira tela para melhor exibição
  // Valores podem ser 0 (default), 1, 2 ou 3
  tft.setRotation(3);
  // Preenche a tela com a cor preta
  tft.fillScreen(ST77XX_BLACK);
  // Escreve texto longo com letras em cor branca
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  // Aguarda 2s
  delay(2000);
 
  // Chama função tftPrintTest
  tftPrintTest();
  // Aguarda 4s
  delay(4000);
  // Gira tela para posição inicial
  tft.setRotation(0);
  // Desenha um pixel na tela em verde
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  // Aguarda 500 ms
  delay(500);
 
  // Teste de linhas
  testlines(ST77XX_YELLOW);
  delay(1000);
 
  // Linhas otimizadas
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(1000);
 
  testdrawrects(ST77XX_GREEN);
  delay(1000);
 
  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(1000);
 
  // Preenche a tela com a cor preta
  tft.fillScreen(ST77XX_BLACK);
  // Teste de círculos preenchidos em azul
  testfillcircles(10, ST77XX_BLUE);
  // Teste de círculos desenhados em branco
  testdrawcircles(10, ST77XX_RED);
  delay(1000);
 
  testroundrects();
  delay(1000);
 
  testtriangles();
  delay(1000);
 
  mediabuttons();
  delay(1000);
 
  // Exibe mensagem de Fim no Monitor Serial
  Serial.println("Fim");
  // Aguarda 1s
  delay(1000);
}
 
void loop() {
  // Inverte cores no display
  tft.invertDisplay(true);
  // Aguarda 500 ms
  delay(500);
  // Volta às cores originais no display
  tft.invertDisplay(false);
  // Aguarda 500 ms
  delay(500);
}
 
// Sub-rotina testlines
void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
	tft.drawLine(0, 0, x, tft.height()-1, color);
	delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
	tft.drawLine(0, 0, tft.width()-1, y, color);
	delay(0);
  }
 
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
	delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
	delay(0);
  }
 
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
	tft.drawLine(0, tft.height()-1, x, 0, color);
	delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
	tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
	delay(0);
  }
 
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
	delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
	delay(0);
  }
}
 
// Sub-rotina testdrawtest com texto e cor como parâmetros
void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
 
// Sub-rotina testfastlines com color1 e color2 como parâmetros
void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}
 
void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}
 
void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}
// Sub-rotina testfillcircles com radius (raio) e cor como parâmetros
void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
	for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
	}
  }
}
 
// Sub-rotina testdrawcircles com radius (raio) e cor como parâmetros
void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
	for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
	}
  }
}
 
// Sub-rotina testtriangles
void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
	x-=4;
	y+=4;
	z-=4;
	color+=100;
  }
}
 
// Sub-rotina testroundrects
void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
	int x = 0;
	int y = 0;
	int w = tft.width()-2;
	int h = tft.height()-2;
	for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
  	x+=2;
  	y+=3;
  	w-=4;
  	h-=6;
  	color+=1100;
	}
	color+=100;
  }
}
//Sub-rotina tftPrintTest
void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}
//Sub-rotina mediabuttons
void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}
