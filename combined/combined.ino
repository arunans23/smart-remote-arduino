#include <SoftwareSerial.h>
#include <IRremote.h>
SoftwareSerial BTserial(9,10); // RX | TX

int LEDPin = 3;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend;

char current = 'S';

unsigned long currentvalue;

void setup() {
  BTserial.begin(38400); 
  Serial.begin(9600);
  pinMode(LEDPin,OUTPUT);
   irrecv.enableIRIn(); 
  // Start the receiver 
}

char buff[20];
int m = 0;


void loop() {
  
  if (irrecv.decode(&results)){
     
    if (current == 'R'){ 
      BTserial.println(results.value, HEX);
     
      }
     irrecv.resume(); // Receive the next value
     
  }

  
  
  if(BTserial.available())
  {
    char daten = BTserial.read();
    if (daten == '*'){
      current = 'R';
      Serial.println(current);
      delay(200);
    }
    else if (daten == '/'){
      current = 'S';
      Serial.println(current);
    } else{
        if (current == 'S'){
          
        
              
           
          if (daten=='\n'){
            currentvalue = strtoul(buff, NULL, 16);
            m = 0;
            char buff[20];
          for (int i = 0; i < 3; i++) {
            Serial.println(currentvalue, HEX);
            irsend.sendSony(currentvalue, 12);
            delay(40);
          }
            }

           else {
              buff[m] = daten;
              m++;
            }   
            
         //5 second delay between each signal burst
      }
     }
    irrecv.enableIRIn();
    irrecv.resume();
  }
  
  
  

}

