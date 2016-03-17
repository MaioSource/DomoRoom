#include <SPI.h>
#include <Ethernet.h>
#include <DHT11.h>


String readString;

//Definimos una MAC y una IP para el arduino
byte mac[] = { 0xDE,0xAD,0xBE,0xFF,0xFE,0xED };
byte ip[] = { 192, 168, 0, 50 };
byte gateway[] = { 192, 168, 0, 1 };                  
byte subnet[] = { 255, 255, 255, 0 }; 

DHT11 dht11(9);

int luz = 2;
int estadoLuz = 0;
int luzSec = 3;
int estadoLuzSec = 0;
int cortinaAbrir = 14;
int cortinaCerrar = 19;

EthernetServer server(80);

void setup() {
  pinMode(luz, OUTPUT);
  pinMode(luzSec, OUTPUT);
  pinMode(cortinaAbrir, OUTPUT);
  pinMode(cortinaCerrar, OUTPUT);
  Serial.begin(9600);
  //Iniciamos el servidor
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
}

void loop() {

  ethernet();
  luzFN();
  luzSecFN();
  
}

//Hacemos conexion con el servidor
void ethernet ()
{

//float temperatura = T();
//int humedad = H();
 // Serial.println(humedad);
 // Serial.println(temperatura);


  EthernetClient client = server.available();

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  
          client.println("Refresh: 1");  
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<center>");
          client.print("25");
          client.println("C");
          client.print("48");
          client.println("%");
          client.println("</center>");
          client.println("</html>");
  if (client) 
  {
  
    boolean newLine = true;
    String line = "";
    while (client.connected() && client.available()) 
    {
      char c = client.read();
      
        if (c == '\n')
        {
          newLine = true;
          programa(line);
          line = "";
        } 
        else if (c != '\r') 
        {
          newLine = false;
          line += c; 
        }

    }
    programa(line);
    delay(1);
    client.stop();   
  }
}

//Hacemos conexion con la app 
void programa(String line)
{  
  if (line.startsWith("tag", 0)) {
    String android = line.substring(4, line.length());
    Serial.println(android);
//////////////////////Luz Principal/////////////////////////////
//////////////////////Luz Principal/////////////////////////////
//////////////////////Luz Principal/////////////////////////////
    if (android == "luzON") 
      estadoLuz = 1;
    if (android == "luzOFF") 
      estadoLuz = 0;
//////////////////////CORTINA////////////////////////////////////
    if (android == "DOWN") 
    {
        digitalWrite(cortinaCerrar,1);
        digitalWrite(cortinaAbrir,0);
        delay(1000);
        digitalWrite(cortinaAbrir, 0);
        digitalWrite(cortinaCerrar,0);
    }
    if (android == "UP") 
      {
        digitalWrite(cortinaAbrir, 1);
        digitalWrite(cortinaCerrar,0); 
        delay(1000);
        digitalWrite(cortinaAbrir, 0);
        digitalWrite(cortinaCerrar,0);
      }
//////////////////////LuzSecundaria//////////////////////////////
//////////////////////LuzSecundaria//////////////////////////////
//////////////////////LuzSecundaria//////////////////////////////
    if (android == "luzSecON") 
      estadoLuzSec = 1;
    if (android == "luzSecOFF") 
      estadoLuzSec = 0;
  }
}
//Control de la luz principal
void luzFN()
{
  if (estadoLuz == 1)
  {
  digitalWrite(luz, HIGH);
  }
  if (estadoLuz == 0)
  {
  digitalWrite(luz, LOW);   
  }
}  

//Control de la luz Secundaria
void luzSecFN()
{
  if (estadoLuzSec == 1)
  {
  digitalWrite(luzSec, HIGH);
  }
  if (estadoLuzSec == 0)
  {
  digitalWrite(luzSec, LOW);   
  }
}
int T()
{
  int estadoT=0;
  float temp, hum;
  if((estadoT = dht11.read(hum, temp)) == 0)   
          {
          //   Serial.print(temp);
         //     Serial.println(" C");
         //    Serial.print(hum);
         //   Serial.println(" %");
          }
         
    
       return temp;
}
int H()
{
  int estadoH;
  float temp, hum;
  if((estadoH = dht11.read(hum, temp)) == 0)   
          {
          //   Serial.print(temp);
         //    Serial.println(" C");
         //    Serial.print(hum);
         //    Serial.println(" %");
          }
         
    
       return hum;
}
