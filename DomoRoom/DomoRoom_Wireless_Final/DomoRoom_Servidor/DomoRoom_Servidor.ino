#include <SPI.h>
#include <Ethernet.h>
#include <DHT11.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial_2 (2, 3);

String readString;

//Definimos una MAC y una IP para el arduino
byte mac[] = { 0xDE,0xAD,0xBE,0xFF,0xFE,0xED };
byte ip[] = { 192, 168, 0, 50 };
byte gateway[] = { 192, 168, 0, 1 };                  
byte subnet[] = { 255, 255, 255, 0 }; 

DHT11 dht11(9);

EthernetServer server(80);

void setup() {
  
  Serial.begin(9600);
  Serial_2.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

}

void loop() {

  ethernet();  
  
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
//////////////////////Luz Principal/////////////////////////////
//////////////////////Luz Principal/////////////////////////////
//////////////////////Luz Principal/////////////////////////////
    if (android == "luzON") 
      {
         Serial_2.write('a');
      }
    if (android == "luzOFF") 
        Serial_2.write('b');
        
//////////////////////CORTINA////////////////////////////////////
    if (android == "DOWN") 
    {
        Serial.println(3);

    }
    if (android == "UP") 
      {
        Serial.println(4);
      }
//////////////////////LuzSecundaria//////////////////////////////
//////////////////////LuzSecundaria//////////////////////////////
//////////////////////LuzSecundaria//////////////////////////////
    if (android == "luzSecON") 
      Serial_2.write('c');
    if (android == "luzSecOFF") 
      Serial_2.write('d');
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
