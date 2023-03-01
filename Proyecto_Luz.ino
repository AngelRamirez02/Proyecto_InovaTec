#include <ESP8266WiFi.h>

String ssid     = "TI ISC";
String password = "Qwerty*2022";
String host ="192.168.100.5";

byte cont = 0;
byte max_intentos = 50;
float corriente=56, potencia= 45;
String dato="corriente="+String(corriente,2)+"&potencia="+String(potencia, 2);
int x=1;


void setup() {
  // Inicia Serial
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
  delay(2000);
 // Serial.print("Conectando a: ");
  //Serial.print(host);
  WiFiClient cliente;
  if(!cliente.connect(host,80)){//conexion al host 
    Serial.println("Conexion fallida");
    return;
  }

  if(x==1){//envia datos solo una vez por metodo GET
    cliente.print("GET /pruebaESP/esp.php?"+dato+"\r\n");
    cliente.print("Host: "+host+"\r\n");
  }
  x++;
}