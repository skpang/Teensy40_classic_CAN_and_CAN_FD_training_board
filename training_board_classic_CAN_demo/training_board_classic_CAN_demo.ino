/*
 * Demo sketch for use with:
 * http://skpang.co.uk/catalog/teensy-40-can-fd-board-with-240x240-ips-lcd-and-usd-holder-p-1584.html
 * 
 * Classic CAN demo
 * Nominal baudrate 500kbps
 * CAN FD data baudrate 2000kbps
 * 
 * www.skpang.co.uk Jan 2020
 * 
 * 
 * */

#include "can_fd_training.h"
#include <FlexCAN_T4.h>
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;

TRAINING t(1);

IntervalTimer timer;

uint8_t an1;
uint8_t an2;
uint8_t an3;  
uint8_t an4;
  
void setup(void) {
 
  t.begin();     // Initialise board
  t.flash_led();
  
  Serial.println("Teensy 4.0 CAN Training board demo. Classic CAN test. www.skpang.co.uk Nov 2020");
 
  can3.begin();
  can3.setBaudRate(500000);   // Data rate 500kbps
  can3.setMaxMB(16);
  can3.enableFIFO();
  can3.enableFIFOInterrupt();
  can3.onReceive(canSniff);
  can3.mailboxStatus();

  timer.begin(sendframe, 500000); // Send frame every 500ms
}

void sendframe()
{

  CAN_message_t msg;
  
  msg.id = 0x7df;

  msg.buf[0] = an1;     // Pot 1 value
  msg.buf[1] = an2;
  msg.buf[2] = an3;
  msg.buf[3] = an4;
  msg.buf[4] = t.read_sw1();  // SW1 value
  msg.buf[5] = t.read_sw2();
  msg.buf[6] = t.read_sw3();
  msg.buf[7] = t.read_sw4();

  msg.len = 8;
  msg.seq = 1;
  can3.write(MB15, msg);
 
}

void loop() {

  can3.events();
   
  an1 = t.read_an1();  // Read pot 1
  an2 = t.read_an2();
  an3 = t.read_an3();
  an4 = t.read_an4();

  Serial.print("Pot values:  ");  
  Serial.print(an1);
  Serial.print("  ");

  Serial.print(an2);
  Serial.print("  ");

  Serial.print(an3);
  Serial.print("  ");

  Serial.print(an4);
  Serial.print("   Switch values ");

  if (t.read_sw1() == LOW)
  {
      Serial.print(" SW1:LOW");
  } else Serial.print(" SW1:HIGH");

  if (t.read_sw2() == LOW)
  {
      Serial.print(" SW2:LOW");
  } else Serial.print(" SW2:HIGH");

  if (t.read_sw3() == LOW)
  {
      Serial.print(" SW3:LOW");
  } else Serial.print(" SW2:HIGH");

  if (t.read_sw4() == LOW)
  {
      Serial.print(" SW4:LOW");
  } else Serial.print(" SW2:HIGH");
   
   Serial.println(" ");
   t.set_rgb(BLUE,HIGH);
   delay(20); 
   t.set_rgb(BLUE,LOW);
   delay(20);
 
  
}

void canSniff(const CAN_message_t &msg) {
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();
}
