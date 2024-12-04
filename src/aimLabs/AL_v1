//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 2023226160
//
// version 0.6
//       to do: ajustar pontos do AimLabs
//================================================================
//================================================================

// 0 é main (duelo) | 1-4 sentido anti horario  | 5 é o sozinho (noutro arduino)

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int LEDs[5] = { 8, 9, 10, 11, 7 };
int LDRs[5] = {
  A0,
  A1,
  A2,
  A3,
  A6
};

int ndiff[3] = { 30, 25, 20 };  // 0 facil, 1 medio, 2 dificil
int margin = 50;

int ldrDefaultValue[5] = {};
int ldrActivatedValue[5] = {};


//==================================
//=========AIM LABS GM==============
//==================================

int playerHits = 0;
bool hit = 0;
int seq[30] = {};
unsigned long timeAim, timeAim1, timeAim2;
//==================================
//============ DUEL GM==============
//==================================

int reacTime = 0;
int valorRecebido = 0;

//==================================
//============INTERFACE=============
//==================================

void writeLCD(int i, String fs, int k, int sc) {  // 16x2
  lcd.clear();
  lcd.setCursor(i, 0);
  lcd.print(fs);
  lcd.setCursor(k, 1);
  lcd.print(sc);
  lcd.setCursor(k + 5, 1);
  lcd.print("ms");
}


//==================================
//============FUNÇÕES===============
//==================================

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
  Serial.print(analogRead(LDRs[4]));  
}

void calibrationLaserOnTarget() {
  Serial.println("Starting calibration with laser");

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], 1);
    Serial.print("Point to LDR ");
    Serial.print(i);

    delay(2000);
    ldrActivatedValue[i] = analogRead(LDRs[i]);

    Serial.print("Target with laser value: ");
    Serial.println(ldrActivatedValue[i]);
    delay(1000);
    digitalWrite(LEDs[i], 0);
  }
}

void calibrationAmbientLighting() {
  Serial.println("Starting calibration");

  for (int i = 0; i < 5; i++) {

    ldrDefaultValue[i] = analogRead(LDRs[i]);

    Serial.print("Calibrating Target ");
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

  // if (ldrActivatedValue[i] == 0)
  // return 0;

  if (analogRead(LDRs[i]) > (ldrActivatedValue[i] - margin)) {
    Serial.print("Target ");
    Serial.print(i);
    Serial.println(" Hit");
    return 1;
  } else return 0;
}

void TurnOnAllLeds() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], 1);
  }
}

void TurnOffAllLeds() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], 0);
  }
}
//                         ======================GAME MODE: AIM LABS===================
void doSeq(int diff) {

  randomSeed(millis());

  for (int i = 0; i < 30; i++) {
    seq[i] = 0;
  }

  for (int i = 1; i < 30; i++) {
    seq[i] = random(0, 5);

    while ((seq[i] == seq[i - 1])) {
      seq[i] = random(0, 5);
      Serial.println("NEW RANDOM");
    }

    Serial.print("random ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(seq[i]);
  }
}

void AimLabsGM(int diff) {

  doSeq(diff);
  Serial.print("Diff = ");
  Serial.println(diff);

  switch (diff) {
    case 0:  // FACIL
      Serial.print("IN CASE DIF=");
      Serial.println(diff);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Dificuldade:");
      lcd.setCursor(5,1);
      lcd.print("Facil");      
      ALEasy();
      break;
    case 1:  // MEDIO
      Serial.print("IN CASE DIF=");
      Serial.println(diff);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Dificuldade:");
      lcd.setCursor(5,1);
      lcd.print("Media");       
      ALMedium();
      break;
    case 2:  //DIFICIL
      Serial.print("IN CASE DIF=");
      Serial.println(diff);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Dificuldade:");
      lcd.setCursor(4,1);
      lcd.print("Dificil");       
      ALHard();
      break;
  }

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Pontuacao:");
  lcd.setCursor(5, 1);
  lcd.print(playerHits);

  delay(5000);
}

int escdiff() {
  
  digitalWrite(LEDs[0],1);
  digitalWrite(LEDs[1],1);
  digitalWrite(LEDs[4],1);

  Serial.println(5);

  delay(1500);

  if (targetHit(1)) {
    return 0;
  } else if (targetHit(0)) {
    return 1;
  } else if (targetHit(4)) {
    return 2;
  } else return -1;
}
void ALEasy() {
  TurnOffAllLeds();
  Serial.println("AL_Easy");
  playerHits = 0;
  int On[3] = {};  // ================  AIM LABS ====================
  do {             // =============  EASY GAME MODE =================
    randomSeed(millis());
    On[0] = random(0, 5);
    On[1] = random(0, 5);
    On[2] = random(0, 5);
  } while ((On[0] == On[1]) || (On[0] == On[2]) || (On[1] == On[2]));

  digitalWrite(LEDs[On[0]], 1);
  digitalWrite(LEDs[On[1]], 1);
  digitalWrite(LEDs[On[2]], 1);
  int i = 0;
  while (i < ndiff[0]) {

    if (targetHit(On[0])) {
      digitalWrite(LEDs[On[0]], 0);
      playerHits++;
      do {
        randomSeed(millis());
        On[0] = random(0, 4);
      } while ((On[0] == On[1]) || (On[0] == On[2]) || (On[1] == On[2]));
      digitalWrite(LEDs[On[0]], 1);
      i++;
    }

    if (targetHit(On[1])) {
      digitalWrite(LEDs[On[1]], 0);
      playerHits++;
      do {
        randomSeed(millis());
        On[1] = random(0, 5);
      } while ((On[0] == On[1]) || (On[0] == On[2]) || (On[1] == On[2]));
      digitalWrite(LEDs[On[1]], 1);
      i++;
    }

    if (targetHit(On[2])) {
      digitalWrite(LEDs[On[2]], 0);
      playerHits++;
      do {
        randomSeed(millis());
        On[2] = random(0, 5);
      } while ((On[0] == On[1]) || (On[0] == On[2]) || (On[1] == On[2]));
      digitalWrite(LEDs[On[2]], 1);
      i++;
    }
  }
  TurnOffAllLeds();
  delay(500);
  TurnOnAllLeds();
  delay(2000);
  TurnOffAllLeds();

  Serial.print("Total de hits: ");
  Serial.println(playerHits);
}

void ALMedium() {
  TurnOffAllLeds();
  Serial.println("AL_Medium");
  playerHits = 0;
  int on[2] = {};  //============= AIM LABS =============
  do {             //========= MEDIUM GAME MODE =========
    randomSeed(millis());
    on[0] = random(0, 5);
    on[1] = random(0, 5);
  } while (on[0] == on[1]);

  digitalWrite(LEDs[on[0]], 1);
  digitalWrite(LEDs[on[1]], 1);
  int j = 0;
  while (j < ndiff[1]) {

    if (targetHit(on[0]) || (millis() - timeAim1) > 2000) {
      digitalWrite(LEDs[on[0]], 0);
      playerHits++;
      do {
        randomSeed(millis());
        on[0] = random(0, 5);
      } while (on[0] == on[1]);
      digitalWrite(LEDs[on[0]], 1);
      j++;
      timeAim1 = millis();
    }

    if (targetHit(on[1]) || (millis() - timeAim2) > 2000) {
      digitalWrite(LEDs[on[1]], 0);
      playerHits++;
      do {
        randomSeed(millis());
        on[1] = random(0, 5);
      } while (on[0] == on[1]);
      digitalWrite(LEDs[on[1]], 1);
      j++;
    }
    timeAim2 = millis();
  }
  TurnOffAllLeds();
  delay(500);
  TurnOnAllLeds();
  delay(2000);
  TurnOffAllLeds();

  Serial.print("Total de hits: ");
  Serial.println(playerHits);
}

void ALHard() {
  TurnOffAllLeds();
  Serial.println("AL_Hard");
  doSeq(ndiff[2]);

  for (int i = 0; i < ndiff[2]; i++) {  //========= AIM LABS ============
    digitalWrite(LEDs[seq[i]], 1);      //======= HARD GAME MODE ========
    timeAim = millis();
    hit = 0;
    Serial.println("IN HARD FOR");
    while (((millis() - timeAim) < 2000) && (hit == 0)) {
      if (targetHit(seq[i])) {
        playerHits++;
        Serial.print("PlayerHits: ");
        Serial.println(playerHits);
        hit = 1;
      }
    }
    digitalWrite(LEDs[seq[i]], 0);
  }

  TurnOffAllLeds();
  delay(500);
  TurnOnAllLeds();
  delay(2000);
  TurnOffAllLeds();

  Serial.print("Total de hits: ");
  Serial.println(playerHits);
}
//                          ======================GAME MODE: DUEL===================
void DuelGM() {
  int hit = 0;
  digitalWrite(LEDs[0], 1);
  delay(1500);
  Serial.println("Get ready");
  digitalWrite(LEDs[0], 0);

  int tempo;

  while (Serial.available() > 0) {
    String recebido = Serial.readStringUntil('\n');
    //Serial.print("Recebi: ");
    //Serial.println(recebido);
    tempo = recebido.toInt();
    //Serial.println(ReactionTime2);
  }

  delay(tempo - 100);

  digitalWrite(LEDs[0], 1);
  unsigned int Timer = millis();

  do {
    if (targetHit(0)) {
      reacTime = millis() - Timer;
      //Serial.print("Target hit | Time: ");
      //Serial.print(reacTime);
      //Serial.println(" Milisegundos");
      //digitalWrite(LEDs[0], 0);
      hit = 1;
    }
  } while (hit == 0);

  digitalWrite(LEDs[0], 0);
  writeLCD(0, "Reaction Time:", 5, reacTime);

  sendRT();

  delay(5000);
  //Serial.println(reacTime);
}

void sendRT() {
  unsigned long int tenSeg = millis();

  do {
    Serial.println(reacTime);
    delay(10);
  } while (millis() - tenSeg < 2500);
}
//==================================
//==============MAIN================
//==================================

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("Loading...");

  for (int i = 0; i < 4; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(LDRs[i], INPUT);
  }
  Serial.setTimeout(100);

  TurnOnAllLeds();
  delay(2500);

  TurnOffAllLeds();
  delay(2500);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Calibracao");
  lcd.setCursor(0, 1);
  lcd.print("Aponte para alvo");

  calibrationAmbientLighting();
  calibrationLaserOnTarget();

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Calibracao");
  lcd.setCursor(3, 1);  // ver valores e falar sobre eles !!!EXTRA!!!
  lcd.print("Concluida");

  delay(2500);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Escolha um");
  lcd.setCursor(2, 1);
  lcd.print("modo de Jogo");
  digitalWrite(LEDs[0], 1);
}

void loop() {
  valorRecebido = 0;
  if (Serial.available() > 0) {
    String recebido = Serial.readStringUntil('\n');
    //Serial.print("Recebi: ");
    //Serial.println(recebido);
    valorRecebido = recebido.toInt();
    //Serial.println(valorRecebido);
    if (valorRecebido == 1) {
      Serial.println("dentro do if");
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Prepare-se!");
      DuelGM();
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Escolha um");
      lcd.setCursor(2, 1);
      lcd.print("modo de Jogo");
      digitalWrite(LEDs[0], 1);
    }
  }

  if (targetHit(0)) {  // AIM LABS GM
    int dif = -1;
    while (dif == -1) {
      dif = escdiff();
    }
    Serial.println(10);
    
    AimLabsGM(dif);

    Serial.println(15);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Escolha um");
    lcd.setCursor(2, 1);
    lcd.print("modo de Jogo");
    digitalWrite(LEDs[0], 1);
  }
}
