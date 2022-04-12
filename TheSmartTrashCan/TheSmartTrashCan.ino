/*
   THE SMART TRASH CAN
   Projektlabor Robotik Sommersemester 2021

   Von: Anton Qian Kun Hartmann & David Shiva Kurcbard
*/
//-------------------------------------------------------------------------------------------------------

//---------------------------------------- Importierte Bibliotheken -------------------------------------

#include <Servo.h> // Fuer die Servos
#include <HX711_ADC.h> // Fuer die Waage
//-------------------------------------------------------------------------------------------------------

//-------------------------------------- Globale Variablen und Objekte ----------------------------------

Servo servoKlappe01; // Steuert die erste Klappe an
Servo servoKlappe02; // Steuert die zweite Klappe an
Servo servoKlappe03; // Steuert die dritte Klappe an
Servo servoKlappe04; // Steuert die vierte Klappe an
Servo servoKlappe05; // Steuert die fuenfte Klappe an

HX711_ADC waage(A2, 13); // Ein Objekt fuer die Waage wird erstellt (Parameter: dt Pin, sck Pin)

int inA = 1;     // Stepper-Motor Pin
int inB = 0;     // Stepper-Motor Pin
int pwm = 3;     // Stepper-Motor Pin
int analog = A0; // Stepper-Motor Pin

int S0 = 4;         // Farbsensor Pin
int S1 = 7;         // Farbsensor Pin
int S2 = 8;         // Farbsensor Pin
int S3 = 2;         // Farbsensor Pin
int sensorOut = 12; // Farbsensor Pin

int redMin = 21;    // TODO => Kalibrierungwert fuer den Farbsensor
int redMax = 95;   // TODO => Kalibrierungwert fuer den Farbsensor
int greenMin = 22;  // TODO => Kalibrierungwert fuer den Farbsensor
int greenMax = 116; // TODO => Kalibrierungwert fuer den Farbsensor
int blueMin = 19;   // TODO => Kalibrierungwert fuer den Farbsensor
int blueMax = 99;  // TODO => Kalibrierungwert fuer den Farbsensor
/* HINWEIS zu den Kalibrierungwerten:
   Die Kalibrierungwerte sind stark abhaengig vom individuellem Setup. Sie werden in
   einem externem Programm bestimmt. Fuer weitere Inofrmationen zur Kalibrierung,
   siehe "FarbsensorKalibrierung.ino".
*/

int metallSensor = A1; // Pin fuer die Messungen des Meatallsensors
//-------------------------------------------------------------------------------------------------------

//------------------------------------------- Setup-Funktion --------------------------------------------

void setup() {

  //Serial.begin(9600);

  servoKlappe01.attach(5);
  klappeSchliessen(servoKlappe01, 160, 0);
  servoKlappe02.attach(6);
  klappeSchliessen(servoKlappe02, 120, 0);
  servoKlappe03.attach(9);
  klappeSchliessen(servoKlappe03, 160, 0);
  servoKlappe04.attach(10);
  klappeSchliessen(servoKlappe04, 120, 0);
  servoKlappe05.attach(11);
  klappeSchliessen(servoKlappe05, 160, 0);

  delay(3000);

  waage.begin(); // Startet Verbindung zum HX711
  waage.start(2000); // Die Waage hat 2000ms Zeit sich zu stabilisieren
  waage.setCalFactor(420.0); // TODO => Kalibrierungsfaktor fuer die Waage
  /* HINWEIS zum Kalibrierungsfaktor:
     Der Kalibrierungsfaktor ist stark abhaengig vom individuellem Setup. Um ihn zu bestimmen,
     legt man ein bekanntes Gewicht auf die Waage und erhoeht den Faktor so lange, bis die
     Messungen (in Gramm) ungefaehr uebereinstimmen.
  */

  pinMode(inA, OUTPUT);    // Stepper-Motor Pin
  pinMode(inB, OUTPUT);    // Stepper-Motor Pin
  pinMode(pwm, OUTPUT);    // Stepper-Motor Pin
  pinMode(analog, OUTPUT); // Stepper-Motor Pin
  analogWrite(pwm, 100);   // Stepper-Motor Geschwindigkeit

  pinMode(S0, OUTPUT);       // Farbsensor Pin
  pinMode(S1, OUTPUT);       // Farbsensor Pin
  pinMode(S2, OUTPUT);       // Farbsensor Pin
  pinMode(S3, OUTPUT);       // Farbsensor Pin
  pinMode(sensorOut, INPUT); // Farbsensor Pin

  // Setze puls width scaling auf 20% (Farbsensor)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(metallSensor, INPUT);
}
//-------------------------------------------------------------------------------------------------------

//------------------------------------------- Loop-Funktion ---------------------------------------------

void loop() {

  if (getGewicht() > 3.0) { // Falls ein Objekt schwerer als 3.0 Gramm erkannt wurde == true
    Serial.println("Objekt erkannt!");

    if (istMetall() == true) { // Falls das Objekt aus Metall (stromleitend) ist == true
      Serial.println("Metall-Objekt erkannt!");
      klappeOeffnen(servoKlappe01, 0, 160); // Klappe 01 oefnnen (0-160)
      delay(3000);
      eingangUp(); // Eingang hochfahren
      delay(3000);
      eingangDown(); // Eingang runterfahren
      delay(3000);
      klappeSchliessen(servoKlappe01, 160, 0); // Klappe 01 schliessen (160-0)
    }
    else if (istMetall() == false) { // Falls das Objekt NICHT aus Metall (stromleitend) ist == true
      Serial.println("KEIN-Metall-Objekt erkannt!");

      if (getColor() == "gruen") { // Falls das Objekt Bio-Muell (Farbe: Gruen) ist == true
        Serial.println("Gruenes-Objekt erkannt!");
        klappeOeffnen(servoKlappe02, 0, 120); // Klappe 02 oefnnen (0-120)
        delay(3000);
        eingangUp(); // Eingang hochfahren
        delay(3000);
        eingangDown(); // Eingang runterfahren
        delay(3000);
        klappeSchliessen(servoKlappe02, 120, 0); // Klappe 02 schliessen (120-0)
      }
      else if (getColor() == "rot") { // Falls das Objekt Plastik-Muell (Farbe: Rot) ist == true
        Serial.println("Rotes-Objekt erkannt!");
        klappeOeffnen(servoKlappe03, 0, 160); // Klappe 03 oefnnen (0-160)
        delay(3000);
        eingangUp(); // Eingang hochfahren
        delay(3000);
        eingangDown(); // Eingang runterfahren
        delay(3000);
        klappeSchliessen(servoKlappe03, 160, 0); // Klappe 03 schliessen (160-0)
      }
      /*else if (getColor() == "keine") { // Falls das Objekt NICHT Gruen noch Rot ist == true
        Serial.println("KEIN-Gruenes/Rotes-Objekt erkannt!");

        if (getGewicht() > 70.0) { // Falls das Objekt schwerer-Muell (Gewicht > 70.0 Gramm) ist == true
          Serial.println("Schweres-Objekt erkannt!");
          klappeOeffnen(servoKlappe04, 0, 120); // Klappe 04 oefnnen (0-120)
          delay(3000);
          eingangUp(); // Eingang hochfahren
          delay(3000);
          eingangDown(); // Eingang runterfahren
          delay(3000);
          klappeSchliessen(servoKlappe04, 120, 0); // Klappe 04 schliessen (120-0)
        }
        else if (getGewicht() <= 70.0) { // Falls das Objekt leichter-Muell (Gewicht <= 70.0 Gramm) ist == true
          Serial.println("Leichtes-Objekt erkannt!");
          Serial.println(getGewicht());
          klappeOeffnen(servoKlappe05, 0, 160); // Klappe 05 oefnnen (0-160)
          delay(3000);
          eingangUp(); // Eingang hochfahren
          delay(3000);
          eingangDown(); // Eingang runterfahren
          delay(3000);
          klappeSchliessen(servoKlappe05, 160, 0); // Klappe 05 schliessen (160-0)
        }
      }*/
    }
  }

}
//-------------------------------------------------------------------------------------------------------

//------------------------------------ Funktionen fuer den Stepper-Motor --------------------------------

// Steuert den Stepper-Motor an und bewegt den Eingangsbereich nach oben
void eingangUp() {

  digitalWrite(inB, HIGH);
  digitalWrite(inA, LOW);
  digitalWrite(analog, HIGH); // Motor wird angeschaltet

  delay(11000); // Nach 11000 ms ist der Eingangsbereich in der Maximalen Position
  digitalWrite(analog, LOW); // Motor wird abgeschaltet
}

// Steuert den Stepper-Motor an und bewegt den Eingangsbereich nach unten
void eingangDown() {

  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(analog, HIGH); // Motor wird angeschaltet

  delay(11000); // Nach 11000 ms ist der Eingangsbereich in der Minimalen Position
  digitalWrite(analog, LOW); // Motor wird abgeschaltet
}
//-------------------------------------------------------------------------------------------------------

//------------------------------------ Funktionen fuer die Servo-Motoren --------------------------------

// Der als Parameter uebergebene Servo wird angesteuert (Klappe wird geoeffnet)
void klappeOeffnen(Servo servo, int startPos, int endPos) {

  for (; startPos <= endPos; startPos++) {
    servo.write(startPos);
    delay(15);
  }
}

// Der als Parameter uebergebene Servo wird angesteuert (Klappe wird geschlossen)
void klappeSchliessen(Servo servo, int startPos, int endPos) {

  for (; startPos >= endPos; startPos--) {
    servo.write(startPos);
    delay(15);
  }
}
//-------------------------------------------------------------------------------------------------------

//------------------------------------ Funktionen fuer den Metallsensor ---------------------------------

// Gibt einen boolean zurueck, ob Metall erkannt wurde
boolean istMetall() {

  // Sobald sich Metall auf dem Metallsensor befindet, erhaelt man Messergebnisse > 0
  if (analogRead(metallSensor) > 100) return true; // Schwellenwert auf 100, um Messfehler zu vermeiden
  return false;
}
//-------------------------------------------------------------------------------------------------------

//-------------------------------------- Funktionen fuer die Waage --------------------------------------

// Speichert 100 Messungen der Waage in einem Array und gibt den Durchschnittswert in Gramm als double zurueck
double getGewicht() {

  double messungen[99];
  double durchschnittswert;

  for (int i = 0; i <= 99; i++) {
    waage.update(); // Ruft Daten aus der Waage ab
    messungen[i] = waage.getData(); // Speichert Messwert im Array
    delay(0); // TODO => eventuell delay notwendig
  }

  for (int i = 0; i <= 99; i++) {
    durchschnittswert += messungen[i]; // Summiert alle Werte aus dem Array
  }

  return durchschnittswert / 100;
}
//-------------------------------------------------------------------------------------------------------

//------------------------------------ Funktionen fuer den Farbsensor -----------------------------------

// Misst nur die roten-Farbanteile (pulse width) und gibt einen Durchschnitts-RGB-Wert (0-255) zurueck
int getRedValue() {

  int redPw; // Speichert den Messwert (pulse width)
  int redValue; // Speichert den RGB-Wert

  // Setze den Farbsensor so, dass nur die roten-Farbanteile gemessen werden
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redPw = pulseIn(sensorOut, LOW);

  redValue = map(redPw, redMin, redMax, 255, 0); // Konvertiert zu einem Wert zwischen 0-255
  delay(200);
  return redValue;
}

// Misst nur die gruenen-Farbanteile (pulse width) und gibt einen Durchschnitts-RGB-Wert (0-255) zurueck
int getGreenValue() {

  int greenPw; // Speichert den Messwert (pulse width)
  int greenValue; // Speichert den RGB-Wert

  // Setze den Farbsensor so, dass nur die gruenen-Farbanteile gemessen werden
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenPw = pulseIn(sensorOut, LOW);

  greenValue = map(greenPw, greenMin, greenMax, 255, 0); // Konvertiert zu einem Wert zwischen 0-255
  delay(200);
  return greenValue;
}

// Misst nur die blauen-Farbanteile (pulse width) und gibt einen Durchschnitts-RGB-Wert (0-255) zurueck
int getBlueValue() {

  int bluePw; // Speichert den Messwert (pulse width)
  int blueValue; // Speichert den RGB-Wert

  // Setze den Farbsensor so, dass nur die blauen-Farbanteile gemessen werden
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  bluePw = pulseIn(sensorOut, LOW);

  blueValue = map(bluePw, blueMin, blueMax, 255, 0); // Konvertiert zu einem Wert zwischen 0-255
  delay(200);
  return blueValue;
}

// Bestimmt aufgrund der RGB-Werte (mithilfe der drei oberen Funktionen),
// die Farbe (rot / gruen / keine) und gibt sie als String zurueck
String getColor() {

  int red = getRedValue();     // Speichert den roten RGB-Wert
  int green = getGreenValue(); // Speichert den gruenen RGB-Wert
  int blue = getBlueValue();   // Speichert den blauen RGB-Wert

  // Sobald die RGB-Werte in einem bestimmten Intervall liegen, wird die entsprechende Farbe ausgegeben
  if (red > 200 & green < 100 & blue < 120) return "rot"; // TODO => Werte anpassen
  else if (red<130 & green>160 & blue < 135) return "gruen"; // TODO => Werte anpassen
  else return "keine";
}
//-------------------------------------------------------------------------------------------------------
