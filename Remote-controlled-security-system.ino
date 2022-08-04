#include <IRremote.h>
int IRpin=9;
int btnPin=13;
int sensorPin=7;
int btnRead;
String btnString="off";
int buzzPin=6;
int dt1=10000;
int dt2=2000;
int dt3=100;
int valCondition;
IRrecv IR(IRpin);             
decode_results cmd; 
String entrince1="movement in backdoor entry";
void setup() { 
  Serial.begin(9600);
  IR.enableIRIn();    
  pinMode(sensorPin,INPUT);
  pinMode(btnPin,INPUT);
  pinMode(buzzPin,OUTPUT);
}

void loop() {
  while (IR.decode(&cmd)==0){
  if (btnRead==0 && btnString=="off"){
  btnString="on";
  Serial.println(btnString);
  digitalWrite(buzzPin,HIGH);
  delay(dt3);
  digitalWrite(buzzPin,LOW);
  delay(dt2);

}
btnRead=digitalRead(btnPin);
if (btnRead==0 && btnString=="on"){
  btnString="off";
    Serial.println(btnString);
  digitalWrite(buzzPin,HIGH);
  delay(dt3);
  digitalWrite(buzzPin,LOW);
  delay(dt2);
}
if (btnString=="on"){
    int sensorval=digitalRead(sensorPin);
  if (sensorval==LOW){
    Serial.println("LOW");
  }
  if (sensorval==HIGH){
    digitalWrite(buzzPin,HIGH);
    btnRead=digitalRead(btnPin);
    Serial.println(entrince1);
    delay(dt2);
    btnRead=digitalRead(btnPin);
    digitalWrite(buzzPin,LOW);
    delay(dt1);
    btnRead=digitalRead(btnPin);
  }
  if (sensorval==LOW){
    digitalWrite(buzzPin,LOW);
  }
}
btnRead=digitalRead(btnPin);
}
Serial.println(cmd.value,HEX);
  delay(1500);
  IR.resume(); 
    if  (cmd.value==0xFFA25D){
      if (btnString=="on"){
        valCondition=1;
      }
      if (btnString=="off"){
        valCondition=2;
      }
      if (valCondition==1){
        btnString="off";
      }
      if (valCondition==2){
        btnString="on";
      }
    }
  digitalWrite(buzzPin,HIGH);
  delay(dt3);
  digitalWrite(buzzPin,LOW);
}
