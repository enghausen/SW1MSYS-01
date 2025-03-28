/*********************************
* "LED.H"                        *
* Header file for "LED driver"   *
* Henning Hargaard               *
*********************************/
void initLEDport();
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);

