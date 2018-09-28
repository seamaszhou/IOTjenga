

#include "application.h"
//plug motor by the number order
int motor = D1;
int motor2 = D2;




TCPClient client;
byte server[] = { 192,168,43,208 }; // Google


int string2int(const char *s){
  int res = 0;
  while (*s){
    res *= 10;
    res += *s - '0';
    *s++;

  }
  return res;}

void pData(char * data){
  Serial.printf("data we get:");
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

  Serial.begin(9600);
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
//Getting BPM data by NodeJS(tcpNodeJSserver.js)
void loop()
{
  char tmp[255];
  int charPosition = 0;


  while(client.available()){
    char c = client.read();
    if( c == ','){
    pData(tmp);

    //tmp[0];
    charPosition = 0;
    break;
  }else{
    if (charPosition > 200) {
      Serial.println("Something is wrong");
      break;

      /* code */
    }

    tmp[charPosition] = c;
    charPosition++;}

  }
  //delay(20);

}
