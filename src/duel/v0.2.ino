//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 230226160
//
// version 0.2
//
//================================================================

// 0 é main (duelo)

int i = 0;
int LED = 8;
#define LDR A0
int margin = 20;

int ldrDefaultValue = 0;
int ldrActivatedValue = 0;

// DUELO

int reacTime = 1000;
String recebido;

//=====================
//======FUNÇÕES========
//=====================


void checkValues() {
  Serial.print("LDR Value: ");
  Serial.print(analogRead(LDR));
  delay(500);
}

void calibrationLaserOnTarget() {
  Serial.println("Starting calibration with laser");

  Serial.print("Point to LDR ");
  digitalWrite(LED, 1);
  delay(2500);
  ldrActivatedValue = analogRead(LDR);

  Serial.print("Target with laser value: ");
  Serial.println(ldrActivatedValue);
  digitalWrite(LED, 0);
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

  if (analogRead(LDR) > (ldrActivatedValue - margin)) {
    Serial.println("Target Hit");
    return 1;
  } else return 0;
}

void DuelGM() {
  //AVISAR O OUTRO ALVO QUE ESTE MODO DE JOGO FOI ESCOLHIDO
  
  Serial.println(1);

  //DUEL GAME MODE
  int hit = 0;
  digitalWrite(LED, 1);
  delay(2000);
  //Serial.println("Get ready");
  digitalWrite(LED, 0);

  int tempo = random(5000, 7001);

  //while((millis()-DuelTime) < tempo){}
  Serial.println(tempo);
  delay(tempo);
  
  digitalWrite(LED, 1);
  unsigned int Timer = millis();

  do {
    if (targetHit()) {
      reacTime = millis() - Timer;
      //Serial.print("Target hit | Time: ");
      //Serial.print(reacTime);
      //Serial.println(" Milisegundos");
      hit = 1;
    }
  } while (hit == 0);

  digitalWrite(LED, 0);

  compareDGM();
}

void compareDGM() {
  int ReactionTime2 = 2;
  unsigned long int tenSeg = millis();

  do{
    while (Serial.available() > 0){
      recebido = Serial.readStringUntil('\n');
      //Serial.print("Recebi: ");
      //Serial.println(recebido);
      ReactionTime2 = recebido.toInt();
      //Serial.println(ReactionTime2);
    }
  }while((millis() - tenSeg) < 5000);

  if (ReactionTime2 > reacTime) {
    Serial.print("| Player1 WON | P1 RT =");
    Serial.print(reacTime);
    Serial.print(" | P2 RT = ");
    Serial.println(ReactionTime2);
  } else {
    Serial.print("| Player2 WON | P1 RT =");
    Serial.print(reacTime);
    Serial.print(" | P2 RT = ");
    Serial.println(ReactionTime2);
  }
}

void menu() {

  if (targetHit())
    DuelGM();

}

//=====================
//======MAIN===========
//=====================

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  Serial.setTimeout(100);

  digitalWrite(LED, 1);
  delay(2500);
  digitalWrite(LED, 0);
  delay(2500);

  calibrationAmbientLighting();
  calibrationLaserOnTarget();

  delay(2500);

}


void loop() {

  delay(10);
  menu();
}
