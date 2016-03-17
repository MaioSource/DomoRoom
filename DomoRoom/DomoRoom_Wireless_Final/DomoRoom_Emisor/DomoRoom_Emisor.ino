#include <VirtualWire.h>

int luz = 2;
int estadoLuz = 0;
int luzSec = 3;
int estadoLuzSec = 0;

void setup() {
  pinMode(luz, OUTPUT);
  pinMode(luzSec, OUTPUT);
  Serial.begin(9600);
  vw_set_tx_pin(12);          // Configura el pin 12 como TX
  vw_set_rx_pin(11);
  vw_set_ptt_inverted(true);  // Requerido para DR3100
  vw_setup(4000);
  vw_rx_start();
  
}

void loop() {

  emisor();
  receptor();
  
}

void emisor() {
   char estado = Serial.read();
   if (estado == 'a')
      {
      digitalWrite(13,1);
      char msg[] = "a";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx();
      }
   if (estado == 'b')
      {
      digitalWrite(13,0);
      char msg[] = "b";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx();
      }
   if (estado == 'c')
      {
      digitalWrite(12,1);
      char msg[] = "c";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx();
      }
   if (estado == 'd')
      {
      digitalWrite(12,0);
      char msg[] = "d";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx();
      }
}

