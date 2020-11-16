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

#include "can_fd_training.h" 
#include <FlexCAN_T4.h>
FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
TRAINING t(1);

IntervalTimer timer;

uint8_t an1;
uint8_t an2;
uint8_t an3;  
uint8_t an4;

void setup(void) {
  
  t.begin();      // Initialise board
  t.flash_led();
  
  Serial.println("Teensy 4.0 CAN Training board demo. CAN FD test. www.skpang.co.uk Nov 2020");
 
  FD.begin();
  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate =   500000;     // 500kbps Nominal data rate
  config.baudrateFD = 2000000;    // 2000kpbs Data rate
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 75;
  FD.setRegions(64);
  FD.setBaudRate(config);


  FD.setMBFilter(ACCEPT_ALL);
  FD.setMBFilter(MB13, 0x1);
  FD.setMBFilter(MB12, 0x1, 0x3);
  FD.setMBFilterRange(MB8, 0x1, 0x04);
  FD.enableMBInterrupt(MB8);
  FD.enableMBInterrupt(MB12);
  FD.enableMBInterrupt(MB13);
  FD.enhanceFilter(MB8);
  FD.enhanceFilter(MB10);
  FD.distribute();
  FD.mailboxStatus();
  

  timer.begin(sendframe, 500000); // Send frame every 500ms
}

void sendframe()
{
  CANFD_message_t msg;
  msg.len = 64;           // Set frame length to 64 bytes
  msg.id = 0x321;
  msg.seq = 1;
  msg.buf[0] = an1;       // Pot 1 value
  msg.buf[1] = an2;
  msg.buf[2] = an3;
  msg.buf[3] = an4;
  msg.buf[4] = t.read_sw1();  // SW1 value
  msg.buf[5] = t.read_sw2();
  msg.buf[6] = t.read_sw3();
  msg.buf[7] = t.read_sw4();
  FD.write( msg);
}

void loop() {
  
  FD.events(); /* needed for sequential frame transmit and callback queues */
  CANFD_message_t msg;

  an1 = t.read_an1();    // Read pot 1
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

  if(FD.readMB(msg)){   // check if we received a CAN frame 
      Serial.print("MB: "); Serial.print(msg.mb);
      Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
      Serial.print("  ID: 0x"); Serial.print(msg.id, HEX );
      Serial.print("  EXT: "); Serial.print(msg.flags.extended );
      Serial.print("  LEN: "); Serial.print(msg.len);
      Serial.print("  BRS: "); Serial.print(msg.brs);
      Serial.print(" DATA: ");
      for ( uint8_t i = 0; i <msg.len ; i++ ) {
        Serial.print(msg.buf[i]); Serial.print(" ");
      }
      Serial.print("  TS: "); Serial.println(msg.timestamp);
  }

}
