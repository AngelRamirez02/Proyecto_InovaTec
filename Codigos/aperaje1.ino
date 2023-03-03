#include <ESP8266WiFi.h>

String ssid     = "TI ISC";
String password = "Qwerty*2022";
String host ="192.168.100.16";

byte cont = 0;
byte max_intentos = 50;

String dato;
float aux=35;
WiFiClient cliente;

void setup() {
  Serial.begin(115200);
  Serial.println("\n");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

Serial.println("");

  if (cont < max_intentos) {  //Si se conectó      
      Serial.println("********************************************");
      Serial.print("Conectado a la red WiFi: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("macAdress: ");
      Serial.println(WiFi.macAddress());
      Serial.println("*********************************************");
  }
  else { //No se conectó
      Serial.println("------------------------------------");
      Serial.println("Error de conexion");
      Serial.println("------------------------------------");
  }
}

void loop() {

  if(!cliente.connect(host,80)){//conexion al host 
    Serial.println("Conexion fallida");
    return;
  }
  
  float Irms=get_corriente(); //Corriente eficaz (A)
  
  float P=Irms*220.0; // P=IV (Watts)
  float error_relativo;

  error_relativo = abs(Irms - aux)/ aux;
  
  if(error_relativo > 0.05){
      Serial.print("Irms: ");
      
      if(Irms >30){
        Serial.print(0.0);
      }else{
      Serial.print(Irms,2);
      }
      
      Serial.print("A, Potencia: ");
      
      if(Irms >30){
        Serial.print(0.0);
      }else{
      Serial.print(P,2);
      }  
      
      Serial.println("W");
      //delay(100);
      aux = Irms;

      
      if(Irms>30){
        dato="corriente=0&potencia=0";  
      }else{
        dato="corriente="+String(Irms,2)+"&potencia="+String(P, 2);
      }
      cliente.print("GET /pruebaESP/esp.php?"+dato+"\r\n");
      cliente.print("Host: "+host+"\r\n");
      
  }
}

float get_corriente()
{
  float voltajeSensor;
  float corriente=0;
  float Sumatoria=0;
  long tiempo=millis();
  int N=0;
  while(millis()-tiempo<500)//Duración 0.5 segundos(Aprox. 30 ciclos de 60Hz)
  { 
    voltajeSensor = analogRead(A0) * (3.3 / 1023.0);////voltaje del sensor
    corriente=voltajeSensor*30.0; //corriente=VoltajeSensor*(30A/1V)
    Sumatoria=Sumatoria+sq(corriente);//Sumatoria de Cuadrados
    N=N+1;
    delay(1);
  }
  Sumatoria=Sumatoria*2;//Para compensar los cuadrados de los semiciclos negativos.
  corriente=sqrt((Sumatoria)/N); //ecuación del RMS
  //String c = String(corriente,2);
  //corriente= c.toFloat();

  if(corriente > 30){
    corriente = 35;
  }

  return(corriente);
}