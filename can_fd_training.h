



#ifndef can_fd_training_h
#define can_fd_training_h

#include "Arduino.h"


static const int LED1 = 24;
static const int LED2 = 25;
static const int LED3 = 26;
static const int LED4 = 28;

static const int LED_R = 29;
static const int LED_G = 27;
static const int LED_B = 32;

static const int SW1 = 20;
static const int SW2 = 21;
static const int SW3 = 22;
static const int SW4 = 23;

static const int AN1 = 0;
static const int AN2 = 1;
static const int AN3 = 2;
static const int AN4 = 3;

static const int RED = 1;
static const int GREEN = 2;
static const int BLUE = 3;


class TRAINING{
  
  public:
  

  TRAINING(uint8_t dummy);
  int begin();
  void flash_led();
  uint8_t read_sw1();
  uint8_t read_sw2();
  uint8_t read_sw3();
  uint8_t read_sw4(); 
   
  uint8_t read_an1();
  uint8_t read_an2();
  uint8_t read_an3();
  uint8_t read_an4();    

  void set_led1(uint8_t state);
  void set_led2(uint8_t state);
  void set_led3(uint8_t state);
  void set_led4(uint8_t state);   
  
  void set_rgb(uint8_t colour,uint8_t state);   
  
  private:
   
  
};

#endif
