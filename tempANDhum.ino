#include <DHT.h>  // libreria
#include <Servo.h> //Inserire la libreria Servo

// pin digitale connesso al DHT
#define PIN 3

// tipo del sensore
#define TIPO DHT11

//Il nome del servo è mioServo
Servo mioServo; 

// sensore (pin del sensore, versione)
DHT mio_dht(PIN, TIPO);

// variabili per umidità e temperatura
float umidita = 0.0;
float temperatura = 0.0;

// LED RGB 
int redPin = 11;   // ROSSO
int greenPin = 10;  // VERDE
int bluePin = 9;   // BLU

// SERVO
int servoPin = 5;
int valore;

// BUZZER
int buzzer = 2;

// MOTORE
int motore = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     // inizializzo la comunicazione seriale
  mio_dht.begin();    // inizializzo sensore

  // output led
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // output motore
  pinMode(motore, OUTPUT);

  // output buzzer
  pinMode(buzzer, OUTPUT);
  
  // servomotore
  mioServo.attach(servoPin); //mioServo è collegato al pin digitale
}

  void loop() {
  // put your main code here, to run repeatedly:
 
  // lettura umidità
  umidita = mio_dht.readHumidity();
  // lettura temperatura
  temperatura = mio_dht.readTemperature();

  // stampa valori umidità e temperatura
  Serial.print("Umidità: ");
  Serial.print(umidita);
  Serial.print(" Temperatura: ");
  Serial.println(temperatura);

    String tmp = "{\"temperatura\":" + String(temperatura) + ",\"umidita\":" + String(umidita) +"}";  //inizializzo la stringa
  Serial.println(tmp);
  
  // colore del led
  if(umidita < 43)
  {
     analogWrite(redPin,0);
     analogWrite(greenPin,0);
     analogWrite(bluePin,194);
     delay(100);
  }
  if(umidita > 42 && umidita < 46)
  {
     analogWrite(redPin,0);
     analogWrite(greenPin,0);
     analogWrite(bluePin,255);
     delay(100);
  }
  if(umidita > 45 && umidita < 48)
  {
     analogWrite(redPin,0);
     analogWrite(greenPin,255);
     analogWrite(bluePin,255);
     delay(100);
  }
  if(umidita > 47 && umidita < 50)
  {
     analogWrite(redPin,065);
     analogWrite(greenPin,255);
     analogWrite(bluePin,050);
     delay(100);
  }
  if(umidita > 49 && umidita < 52)
  {
     analogWrite(redPin,255);
     analogWrite(greenPin,225);
     analogWrite(bluePin,0);
     delay(100);
  }
  if(umidita > 51 && umidita < 54)
  {
     analogWrite(redPin,255);
     analogWrite(greenPin,255);
     analogWrite(bluePin,024);
     delay(100);
  }
  if(umidita > 53 && umidita < 56)
  {
     analogWrite(redPin,255);
     analogWrite(greenPin,129);
     analogWrite(bluePin,0);
     delay(100);
  }
  if(umidita > 55 && umidita < 58)
  {
     analogWrite(redPin,255);
     analogWrite(greenPin,0);
     analogWrite(bluePin,0);
     delay(100);
  }

  // conversione in gradi per il ServoMotore
  valore = (180*umidita)/100;
  mioServo.write(valore);
  Serial.print("Servo motore: ");
  Serial.println(valore);

  // buzzer
  if(umidita > 50) {
    tone(buzzer, 329); 
    digitalWrite(motore, HIGH);
    delay(3000);
    noTone(buzzer);
    digitalWrite(motore, LOW); 
    
  }
  
  delay(2000);  // ritardo di 2 secondi nella lettura
}
