//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 230226160
//
// version 0.1
//
//================================================================

// 0 é main (duelo) | 1-4 sentido anti horario  | 5 é o sozinho (noutro arduino)


int ledsAlvos[6] = { 1, 2, 3, 4, 5, 6 };
int LDRs[6] = { A0, A1, A2, A3, A4, A5 };
int margin = 20;

int ldrDefaultValue[6]={};
int ldrActivatedValue[6]={};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(ledsAlvos[i], OUTPUT);
  }

  Serial.setTimeout(100);
}


void checkValues() {
  Serial.print("LDR 0: ");
  Serial.print(analogRead(LDRs[0]));
  Serial.print("| LDR 1: ");
  Serial.print(analogRead(LDRs[1]));
  Serial.print(" | LDR 2: ");
  Serial.print(analogRead(LDRs[2]));
  Serial.print(" | LDR 3: ");
  Serial.print(analogRead(LDRs[3]));
  Serial.print(" | LDR 4: ");
  Serial.println(analogRead(LDRs[4]));
  delay(500);
}

void calibrationLaserOnTarget() {
  Serial.println("Starting calibration with laser");

  for (int i = 0; i < 5; i++) {

    Serial.print("Point to LDR ");
    Serial.print(i);

    delay(2500);
    ldrActivatedValue[i] = analogRead(LDRs[i]);

    Serial.print("Target with laser value: ");
    Serial.println(ldrActivatedValue[i]);
    delay(2000);
  }
}

void calibrationLuzAmbiente() {
  Serial.println("Starting calibration");

  for (int i = 0; i < 5; i++) {

    ldrDefaultValue[i] = analogRead(LDRs[i]);

    Serial.print("Calibrating Traget ");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(ldrDefaultValue[i]);
  }
}

void showVal() {

  for (int i = 0; i < 5; i++) {

    Serial.print("LDR");
    Serial.print(i);
    Serial.print(" | Laser off target LDR Value");
    Serial.print(":");
    Serial.print(ldrDefaultValue[i]);
    Serial.print(" | Laser on target LDR Value");
    Serial.print(":");
    Serial.println(ldrActivatedValue[i]);
  }
}

bool targetHit(int i) {

  if (ldrActivatedValue[i]==0)
    return 0;

  if (analogRead(LDRs[i]) > (ldrActivatedValue[i]) || (analogRead(LDRs[i]) > (ldrActivatedValue[i] - 50))) {
    Serial.print("Target ");
    Serial.print(i);
    Serial.println(" Hit");
    return 1;
  } else return 0;
}


void loop() {

  for (int i = 0; i < 5; i++) {
    targetHit(i);
  }

  String request = Serial.readString();

  if (request.length() > 0) {
    if (request.endsWith(String("\n")));
    request.remove(request.length() - 1);


    if (request.equals("CAL")) {
      calibrationLuzAmbiente();
    }

    if (request.equals("CALL")) {
      calibrationLaserOnTarget();
    }
    if (request.equals("SHOW")) {
      showVal();
    }
  }
}
