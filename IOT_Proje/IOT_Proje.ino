#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  //Gerekli kütüphanelerimizi ekliyoruz.
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLe2uOp5WT"
#define BLYNK_DEVICE_NAME "Watering System"

char token[] = "47DpzOQsOLrm-CiE-mnVMB566z4NfrxR";
char agAdi[] = "Serdar"; //Blynk uygulamasının bize vermiş olduğu token ve bağlanmak istediğimiz wifi ve şifresini char komutu ile belirliyoruz.
char agSifre[] = "12345678";
int nemDeger ;      // okuma yapacağımız nem değerini deger değişkeni olarak belirliyoruz.
int nemDonusum;
bool Relay = 0;

#define nemSensor A0  // Sensor okuma yapacağımız pini burada belirliyoruz. 
#define suMotoru D1
#define buzzer D0
void setup() {
  
  
  Serial.begin(9600);   //Blynk ve ESP iletişimi için serial monitörü başlatıyoruz.
  pinMode(suMotoru, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(suMotoru, HIGH);
  digitalWrite(buzzer, LOW);
  Blynk.begin(token, agAdi, agSifre, "blynk.cloud",80);  // blynk uygulaması ve ESP bağlantısı sağlanması açısından Blynk.begin komutu içerisine token ve ag adı,şifremizi yazıyoruz.
  
}
    // Buton 
 BLYNK_WRITE(V1)
    {
      Relay = param.asInt();

      if (Relay == 1) 
      {
        digitalWrite(suMotoru, LOW);
        Serial.println("Motor Çalıştı");
        delay(1000);
        digitalWrite(buzzer, HIGH);
      } 
      else 
      {
        digitalWrite(suMotoru, HIGH);
        digitalWrite(buzzer, LOW);
        Serial.println("Motor Durdu");
        delay(1000);
      }
    }

void loop() {
   
    // Nem Değeri alma
    nemDeger = analogRead(nemSensor);     //toprak nem sensöründen analog okuma yapıyoruz.
    nemDonusum=map(nemDeger, 0, 1024, 0, 100);      // okunan bu değer 0-1023 değeri arasında olacağı için burada map komutu ile istediğimiz 0-100 aralığına çeviriyoruz.
    nemDonusum = (nemDonusum - 100) * -1;
    Serial.print("Toprak nem degeri: ");
    Serial.println(nemDonusum);
    delay(1000);
    while(suMotoru == LOW)
    {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);       
    }
    Blynk.virtualWrite (V0, nemDonusum);
    Blynk.run();            //Blynk uygulamasını başlatıyoruz.
 

}
