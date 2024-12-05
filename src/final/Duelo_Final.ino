//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 230226160
//
// version 0.4
//
//================================================================

// 0 é main (duelo)

int i = 0;
int LED = 7;
#define LDR A0
int margin = 20;

int ldrDefaultValue = 0;
int ldrActivatedValue = 0;

// DUELO

int reacTime = 1000;
String recebido;

#include <SPI.h>
#include <TFT.h>

#define cs 10
#define dc 8
#define rst 9

TFT screen = TFT(cs, dc, rst);

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
//=====================
//======INTERFASE======
//=====================

void writeLCD(int i, String fs, int k, int sc) {
  lcd.clear();
  lcd.setCursor(i, 0);
  lcd.print(fs);
  lcd.setCursor(k, 1);
  lcd.print(sc);
  lcd.setCursor(k + 5, 1);
  lcd.print("ms");
}

void drawDuel() {

  screen.stroke(0, 0, 255);
  screen.fill(0, 0, 255);

  screen.circle(screen.width() - 145, (screen.height() / 2) - 22, 12);

  screen.stroke(0, 0, 0);
  screen.text("DUEL", (screen.width() - 90) / 2, (screen.height() - 62) / 2);
}

void drawAimlabs() {

  screen.stroke(0, 150, 0);
  screen.fill(0, 150, 0);

  screen.circle(screen.width() - 145, (screen.height() / 2) + 30, 12);

  screen.stroke(0, 0, 0);
  screen.text("AIMLABS", (screen.width() - 90) / 2, (screen.height() + 38) / 2);
}

void drawDifficulties() {
  screen.stroke(0, 0, 255);  // set the stroke color to red
  screen.fill(0, 0, 255);    // set the fill color to red
  screen.circle(screen.width() - 135, (screen.height() / 2) - 30, 15);
  screen.stroke(0, 0, 0);
  screen.text("1", screen.width() - 140, screen.height() / 2 - 10);

  screen.stroke(0, 0, 255);  // set the stroke color to red
  screen.fill(0, 0, 255);    // set the fill color to red
  screen.circle(screen.width() - 30, (screen.height() / 2) - 30, 15);
  screen.stroke(0, 0, 0);
  screen.text("3", screen.width() - 35, screen.height() / 2 - 10);

  screen.stroke(0, 150, 0);  // set the stroke color to green
  screen.fill(0, 150, 0);    // set the fill color to green
  screen.circle(screen.width() / 2, (screen.height() / 2) + 20, 15);
  screen.stroke(0, 0, 0);
  screen.text("2", screen.width() / 2 - 5, screen.height() / 2 + 40);
}

void winnerOne() {
  screen.setTextSize(2);     // text size
  screen.stroke(0, 0, 255);  // set the stroke color to red
  screen.fill(0, 0, 255);    // set the fill color to red

  screen.circle(screen.width() - 145, (screen.height() / 2), 12);  // duelo

  screen.stroke(0, 0, 0);
  screen.text("PLAYER ONE", (screen.width() - 90) / 2, (screen.height() / 2) - 15);
  screen.text("WINS", (screen.width() - 30) / 2, (screen.height() / 2) + 5);
}

void winnerTwo() {
  screen.setTextSize(2);     // text size
  screen.stroke(0, 150, 0);  // set the stroke color to green
  screen.fill(0, 150, 0);    // set the fill color to green

  screen.circle(screen.width() - 145, (screen.height() / 2), 12);  // duelo

  screen.stroke(0, 0, 0);
  screen.text("PLAYER TWO", (screen.width() - 90) / 2, (screen.height() / 2) - 15);
  screen.text("WINS", (screen.width() - 30) / 2, (screen.height() / 2) + 5);
}
//                         ======================GAME MODE: DUEL===================
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
  unsigned long int sec=millis();
  do{
    Serial.println(tempo);
  }while((millis()-sec)<1500);
  
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
  writeLCD(1, "Reaction Time:", 5, reacTime);

  compareDGM();
}
void drawAnalisarDados() {
  screen.background(255, 255, 255);

  screen.stroke(0, 0, 0);

  screen.setTextSize(2);
  screen.text("A analisar", (screen.width() - (6 * 2 * 10)) / 2, (screen.height() / 2) - 20);
  screen.text("os resultados", (screen.width() - (6 * 2 * 13)) / 2, (screen.height() / 2) + 10);
}

void compareDGM() {
  int ReactionTime2 = 2;

  drawAnalisarDados();


  unsigned long int tenSeg = millis();

  do {
    while (Serial.available() > 0) {
      recebido = Serial.readStringUntil('\n');
      //Serial.print("Recebi: ");
      //Serial.println(recebido);
      ReactionTime2 = recebido.toInt();
      //Serial.println(ReactionTime2);
    }
  } while ((millis() - tenSeg) < 2500);

  screen.background(255, 255, 255);
  if (ReactionTime2 > reacTime) {
    winnerOne();
  } else {
    winnerTwo();
  }
}

void menu() {

  if (targetHit()) {
    screen.background(255, 255, 255);
    drawDuel();

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Prepare-se!");

    DuelGM();

    delay(5000);

    screen.background(255, 255, 255);
    drawAimlabs();
    drawDuel();

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Escolha um");
    lcd.setCursor(2, 1);
    lcd.print("modo de Jogo");
    digitalWrite(LED, 1);
  }
}

void LWD() {
  screen.background(0, 0, 0);
  screen.stroke(255, 255, 255);

  screen.setTextSize(3);
  int lazerWidth = 6 * 3 * 5;
  screen.text("LASER", (screen.width() - lazerWidth) / 2, (screen.height() / 2) - 40);

  screen.setTextSize(2);
  int westernWidth = 6 * 2 * 7;
  screen.text("WESTERN", (screen.width() - westernWidth) / 2, (screen.height() / 2));

  int duelWidth = 6 * 2 * 4;
  screen.text("DUEL", (screen.width() - duelWidth) / 2, (screen.height() / 2) + 30);
}

//=====================
//======MAIN===========
//=====================

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  Serial.setTimeout(100);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("Loading...");

  screen.begin();
  screen.background(255, 255, 255);
  screen.setTextSize(2);

  LWD();

  digitalWrite(LED, 1);
  delay(2500);
  digitalWrite(LED, 0);
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

  screen.background(255, 255, 255);
  drawAimlabs();
  drawDuel();

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Escolha um");
  lcd.setCursor(2, 1);
  lcd.print("modo de Jogo");
  digitalWrite(LED, 1);
}


void loop() {

  menu();

  int valorRecebido = 0;
  if (Serial.available() > 0) {
    String recebido = Serial.readStringUntil('\n');
    //Serial.print("Recebi: ");
    //Serial.println(recebido);
    valorRecebido = recebido.toInt();
    //Serial.println(valorRecebido);
    if (valorRecebido == 5) {
      Serial.println("dentro do if5");
      screen.background(255, 255, 255);
      drawDifficulties();
    }
    if (valorRecebido == 10) {
      Serial.println("dentro do if10");
      screen.background(255, 255, 255);
      drawAimlabs();
    }
    if (valorRecebido == 15) {
      Serial.println("dentro do if15");
      screen.background(255, 255, 255);
      drawAimlabs();
      drawDuel();
    }    
  }
}
