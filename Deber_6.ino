
/*
 * UNIVERSIDAD TECNICA DEL NORTE
 * FACULTAD DE INGENIERIA EN CIENCIAS APLICADAS
 * SISTEMAS EMBEBIDOS
 * STEVEN FLORES
 * 5to Nivel; 
 * Deber 5: Reloj con alarma
 */

#include <MsTimer2.h>                     //Libreria timer
#include <LiquidCrystal.h>                //Libreria LCd
LiquidCrystal lcd (13,12,11,10,9,8);      //Inicio LCD
const int led = 7;                        //Led para alarma
int segundos =0;                        //variable reloj
int minutos =0;                        //variable reloj
int minutoal =0;                        //variable alarma
int horaal = 0;                        //variable alarma
int horas=0;                        //variable reloj
int on1=0;                        //variable axu
int on2=0;                        //variable aux
int aux1=1;                        //variable auxiliar
int aux2=1;                        //variable auxiliar
int valor;                        //variable auxiliar
String dato;                        //variable auxiliar

void setup() {
  pinMode(led,OUTPUT);                //pin 7 como salida         
  Serial.begin(9600);                 //Comunicacion Serial 
  lcd.begin(16,2);                  //LCD Inicio 
  attachInterrupt(0,btnalarma,LOW);                 //Inicio boton interrupcion
  Serial.println("Ingrese el minuto del reloj:");                 //Mensaje de inicio
  MsTimer2::set(1000,reloj);                 //Definir Timer
  MsTimer2::start();                 //Inicio timer
  
}
}
void loop() {
  if(aux1==1){            
    if(Serial.available()>0){                 //Obtencion dato por comunicacion serial
     switch(on1){                 //Activacion mediante switch
         case 0:                 
           dato=Serial.readString();                 //Lectura de dato reloj
           valor=dato.toInt();                 //transofrmar dato reloj
           minutos=valor;                           //Asignar dato reloj
           on1++;
           Serial.println("Ingrese la hora del reloj:");                 //Mensaje de ingreso
         break;
         case 1:
           dato=Serial.readString();                 //Lectura de dato reloj
           valor=dato.toInt();                 //transofrmar dato reloj
           horas=valor;                         //Asignar dato reloj
           on1++;                            
           aux1=0;
           Serial.println("Reloj establecido");//Mensaje de ingreso
         break;
    }
  }
 }
  if(aux2==0){
    if(Serial.available()>0){             //Obtencion dato por comunicacion serial
        switch(on2){
           case 0:
           dato=Serial.readString();             //Lee dato
           valor=dato.toInt();             //Transforma el dato
           minutoal=valor;             //Asigna el dato
           on2++;             //aumenta variable auxiliar
           Serial.println("Ingrese la hora de la alarma:");             //Mensaje de informacion
           break;
           case 1:
           dato=Serial.readString();             //Lee el dato
           valor=dato.toInt();             //Transforma el dato
           horaal=valor;             //Asigna el dato
           on2++;             //Variable Auxiliar
           aux2=1;
           Serial.println("Alarma Establecida");             //Mensaje de informacion
           break;
        }
    }
  }
}
void btnalarma(){             //Metodo alarma
  Serial.println("Ingrese el minuto de la alarma:");             //Mensaje inicial alarma
  aux2=0;             //Reinicia la variable;
  on2=0;             //Reinicia la variable
}
void reloj(){             //Funcion de timer 
  if(segundos<59){             //Segundos de reloj
    segundos++;             //Aumento de segundos de reloj
  }else{
    segundos=0;             //Reinicia segundos
    if(minutos<59){             //limite de minutos 
      minutos++;             //Aumenta minutos
    }else{
      minutos=0;             //Reinicia minutos
      if(horas<23){             //Limite Horas
        horas++;             //Aumenta horas
      }else{
          horas=0;             //Reinicia horas
       }
     }
   }
   lcd.clear();             //Limpia la LCD
   lcd.setCursor(0,0);             //Define ubicacion
   lcd.print("Reloj: ");             //Imprime mensaje
   lcd.setCursor(8,0);             //Define ubicacion
   lcd.print(String(horas)+String(":")+String(minutos)+String(":")+String(segundos));         //Imprime mensaje
   lcd.setCursor(0,1);              //Define ubicacion
   lcd.print("Alarma: ");            //Imprime mensaje
   lcd.setCursor(8,1);            //Define ubicacion
   lcd.print(String(horaal)+String(":")+String(minutoal));           //Imprime mensaje
   if(horas==horaal){                   //Comparacion para alarma
    if(minutos==minutoal){            //Comparacion para alarma
      digitalWrite(led,HIGH);               //Apaga alarma
      }else{
       digitalWrite(led,LOW);                 //Enciende alarma
      }
    }
   
}
