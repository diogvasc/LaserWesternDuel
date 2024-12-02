//================================================================
// Projeto I - FCTUC - LEEC 2023/24
// ---- Laser Western Duel ----
// Diogo Vasco - 2023226969
// Rodrigo Gonçalves - 230226160
//
// TFT Interface
//
//================================================================

#include <SPI.h>
#include <TFT.h> 

#define cs 10
#define dc 8
#define rst 9

TFT screen = TFT(cs, dc, rst);

//       W
// H

// blue | green | red

void setup() {
  screen.begin();  // initialize the screen
  screen.background(255, 255, 255);   // make the background white
  screen.setTextSize(3); // text size
  
}

void drawGreen(){ // duel

  screen.stroke(0, 150, 0);  // set the stroke color to green
  screen.fill(0, 150, 0);  // set the fill color to green
  
  screen.circle(screen.width() - 145 , (screen.height()/2) - 22, 12); // duelo

  screen.stroke(0, 0, 0);
  screen.text("DUEL", (screen.width() - 90) / 2, (screen.height() - 62) / 2);

}

void drawRed(){ // aimlabs 

  screen.stroke(0, 0, 255);  // set the stroke color to red
  screen.fill(0, 0, 255);  // set the fill color to red

  screen.circle(screen.width() - 145 , (screen.height()/2) + 30, 12); // aimlabs
  
  screen.stroke(0, 0, 0);
  screen.text("AIMLABS", (screen.width() - 90 ) / 2, (screen.height() + 38) / 2);
}

void loop() {
  drawGreen();
  drawRed();
}


