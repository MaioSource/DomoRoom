#include <SPI.h>
#include <Ethernet.h>

String readString;

byte mac[] = { 0xDE,0xAD,0xBe,0x4d4,0x44,0x55 };
byte ip[] = { 192, 168, 0, 50 };
byte gateway[] = { 192, 168, 0, 1 };                  
byte subnet[] = { 255, 255, 255, 0 }; 

int luz = 2;
int luzSec = 3;
int cortina = 4;

EthernetServer server(80);

void setup() {
  pinMode(luz, OUTPUT);
  pinMode(luzSec, OUTPUT);
  pinMode(cortina, OUTPUT);
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
}

void loop() {
  EthernetClient client= server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        if (readString.length() < 100) {
          readString += c;
         }

         if (c == '\n') {
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<TITLE>DomoHouse</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
        
           client.println("<a href=\"/?luzON\"\"> Prender luz principal</a> ");
           client.println(" / ");
           client.println("<a href=\"/?luzOFF\"\"> Apagar luz principal</a><br /> ");   
           client.println("<br />");
           
           client.println("<a href=\"/?luzON\"\"> Prender luz secundaria</a> ");
           client.println(" / ");
           client.println("<a href=\"/?luzOFF\"\"> Apagar luz secundaria</a><br /> ");   
           client.println("<br />");
           
           client.println("<a href=\"/?luzON\"\"> Subir cortina</a> ");
           client.println(" / ");
           client.println("<a href=\"/?luzOFF\"\"> Bajar cortina</a><br /> ");   
           client.println("<br />");
                      
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           client.stop();
                                       
           if (readString.indexOf("?luzON") >0){
               digitalWrite(luz, HIGH);
           }
           if (readString.indexOf("?luzOFF") >0){
               digitalWrite(luz, LOW);
           }
           if (readString.indexOf("?luzSecON") >0){
               digitalWrite(luzSec, HIGH);
           }
           if (readString.indexOf("?luzSecOFF") >0){
               digitalWrite(luzSec, LOW);
           }
           if (readString.indexOf("?cortinaUP") >0){
               digitalWrite(cortina, HIGH);
           }
           if (readString.indexOf("?cortinaDOWN") >0){
               digitalWrite(cortina, LOW);
           }
           
           readString="";  
           
         }
       }
    }
}
}
