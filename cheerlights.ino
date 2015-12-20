#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

/*****************************************************************************
  Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // blue
uint8_t clockPin = 3;    // Green

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(50, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();

  // Setup Serial
  Serial.begin(9600);
  delay(100);

  Serial.flush();
  delay(100);
}


void loop()
{
  // Listen to serial commands from RaspPi
  if (Serial.available() > 0)
  {
    delay(100);

    char charIn = 0;
    byte i = 0;
    char stringIn[32] = "";

    while (Serial.available())
    {
      charIn = Serial.read();
      stringIn[i] = charIn;
      i += 1;
    }

    // Echo Received Commands on the Serial Monitor
    //Serial.println("CheerLight Command Received: " + String(stringIn));
    //delay(200);

    // Send matching commands LED
    // Currently it echos the color back to serial for debugging
    
    if (String(stringIn) == "red")
    {
      Serial.println("red");
      colorWipe(Color(255, 0, 0), 50); //MAKE IT RED
    }
    else if (String(stringIn) == "green")
    {
      Serial.println("green");
      colorWipe(Color(0, 255, 0), 50); // MAKE IT GREEN
    }
    else if (String(stringIn) == "blue")
    {
      Serial.println("blue");
      colorWipe(Color(0, 0, 255), 50); //MAKE IT BLUE
    }
    else if (String(stringIn) == "purple")
    {
      Serial.println("puple");
      colorWipe(Color(102, 51, 204), 50); //MAKE IT PURPLE
    }
    else if (String(stringIn) == "cyan")
    {
      Serial.println("cyan");
      colorWipe(Color(0, 255, 255), 50); //MAKE IT CYAN
    }
    else if (String(stringIn) == "magenta")
    {
      Serial.println("magenta");
      colorWipe(Color(255, 0, 255), 50); //MAKE IT MAGENTA
    }
    else if (String(stringIn) == "yellow")
    {
      Serial.println("yellow");
      colorWipe(Color(255, 255, 0), 50); //MAKE IT YELLOW
    }
    else if (String(stringIn) == "orange")
    {
      Serial.println("orange");
      colorWipe(Color(255, 153, 0), 50); //MAKE IT ORANGE
    }
    else if (String(stringIn) == "white" || String(stringIn) == "warmwhite")
    {
      Serial.println("white");
      colorWipe(Color(255, 255, 255), 50); //MAKE IT WHITE
    }
    else if (String(stringIn) == "black" || String(stringIn) == "off")
    {
      Serial.println("black");
      colorWipe((0, 0, 0), 50); //MAKE IT BLACK
    }

  }

} // End loop

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
