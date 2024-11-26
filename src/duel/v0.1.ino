//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 230226160
//
// version 0.2
//
//================================================================



int LED = 2;
#define LDR A0
int margin = 20;

int ldrDefaultValue = 0;
int ldrActivatedValue = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  Serial.setTimeout(100);
}


void checkValues() {
  Serial.print("LDR Value: ");
  Serial.print(analogRead(LDR));
  delay(500);
}

void calibrationLaserOnTarget() {
  Serial.println("Starting calibration with laser");

    Serial.print("Point to LDR ");

    delay(2500);
    ldrActivatedValue = analogRead(LDR);

    Serial.print("Target with laser value: ");
    Serial.println(ldrActivatedValue);
    delay(2000);
}

void calibrationAmbientLighting() {
  Serial.println("Starting calibration");

    ldrDefaultValue = analogRead(LDR);

    Serial.print("Calibrating Target ");
    Serial.print(" - ");
    Serial.println(ldrDefaultValue);
}

void showVal() {

    Serial.print("Laser off target LDR Value");
    Serial.print(":");
    Serial.print(ldrDefaultValue);
    Serial.print(" | Laser on target LDR Value");
    Serial.print(":");
    Serial.println(ldrActivatedValue);
  }

bool targetHit() {

  if (ldrActivatedValue==0)
    return 0;

  if (analogRead(LDR) > (ldrActivatedValue) || (analogRead(LDR) > (ldrActivatedValue - 50))) {
    Serial.print("Target ");
    Serial.println(" Hit");
    return 1;
  } else return 0;
}

void DuelGM(){
  int hit =0;
  digitalWrite(LED,1);
  delay(2000);
  Serial.println("Get ready");
  digitalWrite(LED,0);

  int tempo= random (5000,7001);
  unsigned int DuelTime=millis();

  while((millis()-DuelTime) < tempo){}

  digitalWrite(LED,1);
  unsigned int DuelReacTime=millis();
  
  do{
    if(targetHit()){
      Serial.print("Target hit | Time: ");
      Serial.println(millis()-DuelReacTime);
      hit = 1 ;
    }
  }while(hit==0);
}


void loop() {

  targetHit();

  String request = Serial.readString();

  if (request.length() > 0) {
    if (request.endsWith(String("\n")));
    request.remove(request.length() - 1);


    if (request.equals("CAL")) {
      calibrationAmbientLighting();
    }

    if (request.equals("CALL")) {
      calibrationLaserOnTarget();
    }
    if (request.equals("SHOW")) {
      showVal();
    }
    if (request.equals("DUEL")) {
      DuelGM();
    }
  }
}
