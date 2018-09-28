#include "application.h"

int motor = D7;
int motor2= A7;



TCPClient client;
byte server[] = { 192,168,43,208 };


int string2int(const char *s){
  int res = 0;
  while (*s){
    res *= 10;
    res += *s - '0';
    *s++;

  }
  return res;}
void pData(char * data){
  Serial.printf("%d ", string2int(data));
  if (string2int(data) > 1000) {
    digitalWrite(motor, LOW);
    digitalWrite(motor2, LOW);
    /* code */
  }else{digitalWrite(motor, HIGH);
  digitalWrite(motor2, HIGH);}

//  analogWrite(led1, string2int(data));

}


void setup()
{ pinMode(motor, OUTPUT);
  pinMode(motor2, OUTPUT);
  // Make sure your Serial Terminal app is closed before powering your device
  Serial.begin(9600);
  // Now open your Serial Terminal, and hit any key to continue!
  while(!Serial.available()) Particle.process();

  Serial.println("connecting...");

  if (client.connect(server, 8080))
  {
    Serial.println("connected");

  }
  else
  {
    Serial.println("connection failed");
  }
}

void loop()
{
  char tmp[3];

  int charPosition = 0;

  while(client.available()){
    char c = client.read();
    if( c == ','){
    pData(tmp);
    Serial.println(c);
    tmp[0];
    charPosition = 0;
  }else{
    tmp[charPosition] = c;
    charPosition++;}

  }
}
