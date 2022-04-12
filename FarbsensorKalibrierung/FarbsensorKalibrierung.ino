/*
   FARBSENSOR KALIBRIERUNG
   Projektlabor Robotik Sommersemester 2021

   Von: Anton Qian Kun Hartmann & David Shiva Kurcbard


   Um alle sechs Kalibrierungwerte zu bestimmen, sind folgende Materialien notwendig:
   - Schablone mit weissem Hintergrund,
   - Schablone mit schwarzem Hintergrund.

   1. Schritt:
   Lasse das Programm laufen und lege die Schablone mit dem WEISSEM Hintergrund an den Farbsensor.
   2. Schritt:
   Notiere die NIEDRIGSTEN Messergebnisse (puls width Messungen) der jeweiligen Farben Rot, Gruen und Blau.
   3. Schritt:
   Lasse das Programm laufen und lege die Schablone mit dem SCHWARZEM Hintergrund an den Farbsensor.
   4. Schritt:
   Notiere die HOECHSTEN Messergebnisse (puls width Messungen) der jeweiligen Farben Rot, Gruen und Blau.
   5. Trage die Kalibrierungwerte in das Programm "TheSmartTrashCan.ino" ein.
*/
//-------------------------------------------------------------------------------------------------------

int S0 = 4; // Farbsensor Pin
int S1 = 7; // Farbsensor Pin
int S2 = 8; // Farbsensor Pin
int S3 = 2; // Farbsensor Pin
int sensorOut = 12; // Farbsensor Pin

void setup() {

  pinMode(S0, OUTPUT); // Farbsensor Pin
  pinMode(S1, OUTPUT); // Farbsensor Pin
  pinMode(S2, OUTPUT); // Farbsensor Pin
  pinMode(S3, OUTPUT); // Farbsensor Pin
  pinMode(sensorOut, INPUT); // Farbsensor Pin

  // Setze puls width scaling auf 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {

  // Ausgabe der Messergebnisse am Farbsensor (pulse width):
  Serial.print("Red PW = ");
  Serial.print(getRedPW());
  Serial.print(" - Green PW = ");
  Serial.print(getGreenPW());
  Serial.print(" - Blue PW = ");
  Serial.println(getBluePW());
}

// Misst nur die roten-Farbanteile (pulse width)
int getRedPW() {

  // Setze den Farbsensor so, dass nur die roten-Farbanteile gemessen werden
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Gebe das Messergebnis zurueck
  return pulseIn(sensorOut, LOW);
}

// Misst nur die gruenen-Farbanteile (pulse width)
int getGreenPW() {

  // Setze den Farbsensor so, dass nur die gruenen-Farbanteile gemessen werden
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Gebe das Messergebnis zurueck
  return pulseIn(sensorOut, LOW);
}

// Misst nur die blauen-Farbanteile (pulse width)
int getBluePW() {

  // Setze den Farbsensor so, dass nur die blauen-Farbanteile gemessen werden
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Gebe das Messergebnis zurueck
  return pulseIn(sensorOut, LOW);
}
