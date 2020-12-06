/*
 * COD 18: USO DE TIMER 2;
 * OBJETIVO: REALIZAR UN RELOJ DIGITAL
 * FUNCIONES: 
 *          MsTimer2::set(1000,subrutina); -> 1 segundo 
 *          MsTimer2::start();
 *          MsTimer2::stop();
 */

#include <MsTimer2.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (13,12,11,10,9,8);
const int led = 7;
int segundos =0;
int minutos =0;
int minutoal =0;
int horaal = 0;
int horas=0;
int on1=0;
int on2=0;
int aux1=1;
int aux2=1;
int valor;
String dato;

void setup() {
  pinMode(led,OUTPUT); //pin 7 como salida
  Serial.begin(9600);
  lcd.begin(16,2);
  attachInterrupt(0,btnalarma,LOW);
  Serial.println("Ingrese el minuto del reloj:");
  MsTimer2::set(1000,reloj);
  MsTimer2::start();
  
}
void btnhora(){
  if(horas<23){
    horas++;
  }else{
    horas=0;
  }
}
void loop() {
  if(aux1==1){
    if(Serial.available()>0){
     switch(on1){
         case 0:
           dato=Serial.readString();
           valor=dato.toInt();
           minutos=valor;
           on1++;
           Serial.println("Ingrese la hora del reloj:");
         break;
         case 1:
           dato=Serial.readString();
           valor=dato.toInt();
           horas=valor;
           on1++;
           aux1=0;
           Serial.println("Reloj establecido");
         break;
    }
  }
 }
  if(aux2==0){
    if(Serial.available()>0){
        switch(on2){
           case 0:
           dato=Serial.readString();
           valor=dato.toInt();
           minutoal=valor;
           on2++;
           Serial.println("Ingrese la hora de la alarma:");
           break;
           case 1:
           dato=Serial.readString();
           valor=dato.toInt();
           horaal=valor;
           on2++;
           aux2=1;
           Serial.println("Alarma Establecida");
           break;
        }
    }
  }
}
void btnalarma(){
  Serial.println("Ingrese el minuto de la alarma:");
  aux2=0;
  on2=0;
}
void reloj(){
  if(segundos<59){
    segundos++;
  }else{
    segundos=0;
    if(minutos<59){
      minutos++;
    }else{
      minutos=0;
      if(horas<23){
        horas++;
      }else{
          horas=0;
       }
     }
   }
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Reloj: ");
   lcd.setCursor(8,0);
   lcd.print(String(horas)+String(":")+String(minutos)+String(":")+String(segundos));
   lcd.setCursor(0,1);
   lcd.print("Alarma: ");
   lcd.setCursor(8,1);
   lcd.print(String(horaal)+String(":")+String(minutoal));
   if(horas==horaal){
    if(minutos==minutoal){
      digitalWrite(led,HIGH);
      }else{
       digitalWrite(led,LOW);
      }
    }
   
}
