/*
 * Demo sketch for use with:
 * http://skpang.co.uk/catalog/teensy-40-can-fd-board-with-240x240-ips-lcd-and-usd-holder-p-1584.html
 * 
 * Nominal baudrate 500kbps
 * CAN FD data baudrate 2000kbps
 * 
 * www.skpang.co.uk Jan 2020
 * 
 * 
 * */

#include "Arduino.h"
#include "can_fd_training.h"


TRAINING::TRAINING(uint8_t dummy)
{
  
    
}

int TRAINING::begin(){
  
  pinMode(LED1,OUTPUT);    // Setup output mode
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
        
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
  
  return 1;
  
}

void TRAINING::flash_led()
{
  
   set_led1(HIGH);
   delay(200); 
   set_led1(LOW);

   set_led2(HIGH);
   delay(200); 
   set_led2(LOW);

   set_led3(HIGH);
   delay(200); 
   set_led3(LOW);

   set_led4(HIGH);
   delay(200); 
   set_led4(LOW);      

  
   set_rgb(RED,HIGH);
   delay(200); 
   set_rgb(RED,LOW);

   set_rgb(GREEN,HIGH);
   delay(200); 
   set_rgb(GREEN,LOW);

   set_rgb(BLUE,HIGH);
   delay(200); 
   set_rgb(BLUE,LOW);   
   delay(200);
}

void TRAINING::set_rgb(uint8_t colour,uint8_t state)
{

   if(colour == RED)
   {
      if(state == HIGH)
      {
          digitalWrite(LED_R, LOW);
      }else digitalWrite(LED_R, HIGH);
   }

   if(colour == GREEN)
   {
      if(state == HIGH)
      {
          digitalWrite(LED_G, LOW);
      }else digitalWrite(LED_G, HIGH);
   }

   if(colour == BLUE)
   {
      if(state == HIGH)
      {
          digitalWrite(LED_B, LOW);
      }else digitalWrite(LED_B, HIGH);
   } 
}

void TRAINING::set_led1(uint8_t state)
{

  if(state == 0)
  {
      digitalWrite(LED1, LOW);
  }else
  {
      digitalWrite(LED1, HIGH);
  }
}

void TRAINING::set_led2(uint8_t state)
{

  if(state == 0)
  {
      digitalWrite(LED2, LOW);
  }else
  {
      digitalWrite(LED2, HIGH);
  }
}

void TRAINING::set_led3(uint8_t state)
{

  if(state == 0)
  {
      digitalWrite(LED3,LOW);
  }else
  {
      digitalWrite(LED3, HIGH);
  }
}

void TRAINING::set_led4(uint8_t state)
{

  if(state == 0)
  {
      digitalWrite(LED4, LOW);
  }else
  {
      digitalWrite(LED4, HIGH);
  }
}


uint8_t TRAINING::read_sw1()
{
   return(digitalRead(SW1));
}

uint8_t TRAINING::read_sw2()
{
   return(digitalRead(SW2));
}

uint8_t TRAINING::read_sw3()
{
   return(digitalRead(SW3));
}

uint8_t TRAINING::read_sw4()
{
   return(digitalRead(SW4));
}

uint8_t TRAINING::read_an1()
{
   // Read ADC and scale it to 255. Invent value so it is 0 to 255 when turning clockwise on the pot
   return(255-map(analogRead(AN1), 0, 1023, 0, 255));
 
}

uint8_t TRAINING::read_an2()
{
   // Read ADC and scale it to 255. Invent value so it is 0 to 255 when turning clockwise on the pot  
   return(255-map(analogRead(AN2), 0, 1023, 0, 255));
 
}

uint8_t TRAINING::read_an3()
{
   // Read ADC and scale it to 255. Invent value so it is 0 to 255 when turning clockwise on the pot  
   return(255-map(analogRead(AN3), 0, 1023, 0, 255));
 
}

uint8_t TRAINING::read_an4()
{
   // Read ADC and scale it to 255. Invent value so it is 0 to 255 when turning clockwise on the pot  
   return(255-map(analogRead(AN4), 0, 1023, 0, 255));
 
}
