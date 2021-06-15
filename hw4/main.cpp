#include "mbed.h"

#include "bbcar.h"

#include "bbcar_rpc.h"

#include "parallax_encoder.h"


Ticker servo_ticker;
Ticker encoder_ticker;

PwmOut pin5(D5), pin6(D6);

DigitalIn pin11(D11);

BufferedSerial xbee(D1, D0);

parallax_encoder encoder(pin11, encoder_ticker);

BBCar car(pin5, pin6, servo_ticker);


int main() {

   char buf[256], outbuf[256];

   FILE *devin = fdopen(&xbee, "r");

   FILE *devout = fdopen(&xbee, "w");

   while (1) {

      memset(buf, 0, 256);

      for( int i = 0; ; i++ ) {

         char recv = fgetc(devin);

         if(recv == '\n') {

            printf("\r\n");

            break;

         }

         buf[i] = fputc(recv, devout);

      }

   RPC::call(buf, outbuf);

   }

}