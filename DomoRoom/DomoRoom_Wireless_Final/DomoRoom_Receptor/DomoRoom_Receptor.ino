#include <VirtualWire.h>

int luz = 2;
int luzSec = 3;

void setup() {
  pinMode(luz, OUTPUT);
  pinMode(luzSec, OUTPUT);
  Serial.begin(9600);
  
  vw_set_rx_pin(12);          // Configura el pin 12 como TX
  vw_setup(4000);
  vw_rx_start();
  
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN]; //Almacenar en buffer los datos recibidos
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Determina el numero de caracteres recibidos
    if (vw_get_message(buf, &buflen)) // Si hay un mensaje recibido ejecuta...
    {
	int i; 
	for (i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido
	{
            char c = (buf[i]); // guarda el caracter recibido para despues imprimirlo
            if (c == 'a')
              digitalWrite(luz, HIGH);
            if (c == 'b')
              digitalWrite(luz, LOW);
            if (c == 'c')
              digitalWrite(luzSec, HIGH);
            if (c == 'd')
              digitalWrite(luzSec, LOW);
               
	}
    }
delay(125);                 // Pausa antes repetir el ciclo
}
