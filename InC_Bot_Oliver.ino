/* 
IN C BOT - button control
04082024 - Levy Lorenzo
NEW FEATURES
   * TWO modes of operation
   * 1:  BEAT jumpers at 111 - 
   * 2:  NORMAL PLAY jumpers not at 111
- DIP switch jumps to sections according to red boxes in score
- PLAY (middle button)  - plays music of current section
- At Power Up - with DIP to 0000, init to Section 1, with all LED's on
- Press of NEXT will increment section by 1
- Another increment will only be allowed if a current section is played at least once 
- ALL LEDS ON - anytime we are in standing by in Section 1
- LED even/odd indicator:  LED 4 is ON when current section is EVEN and off when ODD
- ending condition to never increment past Section 53 (the last section )

USER INSTRUCTIONS
- place all jumpers down to 0000
- plug in usb cable
- all lights will turn on - we are waiting in SECTION 1
- press middle button to play
- hit right button to go to next
- you can only go to the next when at least 1 cycle of the current seciont has been played
... etc etc.... we'll work on refining this.

- design decision:  do not allow user to go in reverse.  if you want to go back you have move and then
re-set the jumper position

note: "REVERSE button" has no function  can find a use later...

----------------------
IN C BOT 
04012024 - Oliver Xu

output coding - 
- all 53 IN C patterns
- direct LED behavior for each to visualize the melodic patterns

- tuning is configurable with tuningStandard global constant
- tempo is configurable with tempo global constant

*/

char LED_1 = 9;   // sound visusalizer 
char LED_2 = 10;  // sound visusalizer 
char LED_3 = 11;  // sound visusalizer 
// NOT CONNECTED
char LED_4 = 12;  // odd/even indicator of forward/back movement

char B1_fwd = 4;  //button - forward
char B2_rev = 2;  //button - reverse
char B3_play = 3; //button - play

char jump1 = 5;   //dip switch for offset, reh number jump MSB
char jump2 = 6;   //dip switch for offset, reh number jump
char jump3 = 7;   //dip switch for offset, reh number jump

int SECTION = 1;    /* MAIN SECTION NUMBER */
int SEC_OFFSET = 1; /* offset to base starting number to jump to reh numbres */

//OFFSET CALCULATION FLAGS
int storeOFFSET = 1;
boolean holdOFFSET = 0;

//SECTION CALCULATION FLAGS
boolean GO_forward = 1; //init to allow going forward in increment SECTION
boolean hasPLAYED = 1;   //has a seciton played at least once? init to 1

const int tuningStandard = 440;
// in equal temperament, frequency of MIDI note number m is calculated with:
// freq = 440 * 2^((m-69)/12)
// https://homes.luddy.indiana.edu/donbyrd/Teach/MusicalPitchesTable.htm
unsigned int G3_note = round(tuningStandard * pow(2.0, (55 - 69) / 12.0));
unsigned int C4_note = round(tuningStandard * pow(2.0, (60 - 69) / 12.0));
unsigned int E4_note = round(tuningStandard * pow(2.0, (64 - 69) / 12.0));
unsigned int F4_note = round(tuningStandard * pow(2.0, (65 - 69) / 12.0));
unsigned int Fs4_note = round(tuningStandard * pow(2.0, (66 - 69) / 12.0));
unsigned int G4_note = round(tuningStandard * pow(2.0, (67 - 69) / 12.0));
unsigned int A4_note = round(tuningStandard * pow(2.0, (69 - 69) / 12.0));
unsigned int Bb4_note = round(tuningStandard * pow(2.0, (70 - 69) / 12.0));
unsigned int B4_note = round(tuningStandard * pow(2.0, (71 - 69) / 12.0));
unsigned int C5_note = round(tuningStandard * pow(2.0, (72 - 69) / 12.0));
unsigned int D5_note = round(tuningStandard * pow(2.0, (74 - 69) / 12.0));
unsigned int E5_note = round(tuningStandard * pow(2.0, (76 - 69) / 12.0));
unsigned int F5_note = round(tuningStandard * pow(2.0, (77 - 69) / 12.0));
unsigned int Fs5_note = round(tuningStandard * pow(2.0, (78 - 69) / 12.0));
unsigned int G5_note = round(tuningStandard * pow(2.0, (79 - 69) / 12.0));
unsigned int A5_note = round(tuningStandard * pow(2.0, (81 - 69) / 12.0));
unsigned int B5_note = round(tuningStandard * pow(2.0, (83 - 69) / 12.0));

const int tempo = 120;
double thirtySecondNoteDuration = 60000.0 / tempo / 8;
// rhythmic multipliers are used to calculate duration of notes and rests
const int THIRTY_SECOND = 1; // 62.5ms
const int SIXTEENTH = 2; // 125ms
const int DOTTED_SIXTEENTH = 3; // 187.5ms
const int EIGHTH = 4; // 250ms
const int DOTTED_EIGHTH = 6; // 375ms
const int QUARTER = 8; // 500ms
const int DOTTED_QUARTER = 12; // 750ms
const int HALF = 16; // 1000ms
const int DOTTED_HALF = 24; // 1500ms
const int WHOLE = 32; // 2000ms
const int DOTTED_WHOLE = 48; // 3000ms

void playNote(unsigned int frequency, int rhythmicMultiplier, int led) {
  tone(8, frequency);
  lightOn(led);
  if (rhythmicMultiplier == THIRTY_SECOND) {
    // grace note should be full length
    delay(thirtySecondNoteDuration * rhythmicMultiplier);
    OFF();
  }
  else {
    // all other rhythmic values have 50ms of silence at the end
    delay(thirtySecondNoteDuration * rhythmicMultiplier - 50);
    OFF();
    delay(50);
  }
}

void playRest(int rhythmicMultiplier) {
  OFF();
  delay(thirtySecondNoteDuration * rhythmicMultiplier);
}

void OFF(){
  noTone(8);
  digitalWrite(LED_1, LOW); 
  digitalWrite(LED_2, LOW); 
  digitalWrite(LED_3, LOW); 
}

void beat(){
  playNote(C5_note * 2, THIRTY_SECOND, 7);
  playRest(DOTTED_SIXTEENTH);
}

void lightOn(int led) {
  switch (led) {
    case 1:
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      break;
    case 2:
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      break;
    case 3:
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      break;
    case 4:
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW);
      break;
    case 5:
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      break;
    case 6:
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, HIGH); 
      break;
    case 7:
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, HIGH); 
      break;
  }
}

void setup() {

  
  pinMode(B1_fwd, INPUT);  //button to advance forward to next section
  pinMode(B2_rev, INPUT); // button to go back to previous sections
  pinMode(B3_play, INPUT);  //button PLAY current setion

  pinMode(jump1, INPUT_PULLUP);  //jumper #1 for section offset to jump to rehearsal number
  pinMode(jump2, INPUT_PULLUP);  //jumper #2 for section offset to jump to rehearsal number
  pinMode(jump3, INPUT_PULLUP);  //jumper #3 for section offset to jump to rehearsal number

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600); // initialize serial
}


void loop(){
  int NEXT = digitalRead(B1_fwd);
  int PREV = digitalRead(B2_rev);
  int PLAY = digitalRead(B3_play);
  Serial.print("                      ");  
  Serial.print(PREV);   Serial.print(" "); Serial.print(PLAY); Serial.print(" "); Serial.println(NEXT);  

  boolean J1 = digitalRead(jump1);
  boolean J2 = digitalRead(jump2);
  boolean J3 = digitalRead(jump3);
  
  // Parse jumper values to determine offset  - LOW ACTIVE BITS!
  if (J1==1 && J2==1 && J3==1)        {  SEC_OFFSET = 1; }
  else if (J1==0 && J2==1 && J3==1)   {  SEC_OFFSET = 9; }
  else if (J1==1 && J2==0 && J3==1)   {  SEC_OFFSET = 18; }
  else if (J1==1 && J2==1 && J3==0)   {  SEC_OFFSET = 29; }
  else if (J1==0 && J2==0 && J3==1)   {  SEC_OFFSET = 36; }
  else if (J1==0 && J2==1 && J3==0)   {  SEC_OFFSET = 43; }
  else if (J1==1 && J2==0 && J3==0)   {  SEC_OFFSET = 49; }
  else if (J1==0 && J2==0 && J3==0)   {  SEC_OFFSET = 100; }  // all 1 is BEAT FUNCTION
  else                                {  SEC_OFFSET = 0;};
  Serial.print("OFFSET= ");    Serial.println(SEC_OFFSET);

  /*
   * TWO modes of operation
   * 1:  BEAT jumpers at 111 - 
   * 2:  NORMAL PLAY jumpers not at 111
   */

  if (SEC_OFFSET != 100) { // normal playing operation - all jumpers are
    if(SEC_OFFSET != storeOFFSET){  holdOFFSET = 0; }    //dont hold offset - bc OFFSET has CHANGED!
  
    //increment section if FWD is pressed
    if(NEXT == 0){                  //NEXT not pressed
        if(holdOFFSET == 0){        //allow new offset to take effect to update section
          SECTION = SEC_OFFSET;
          storeOFFSET = SEC_OFFSET; //store OFFSET to compare later to see if a change has happened in OFFSET
        }
    }
    else{                           //! yes NEXT is Pressed !
      if(hasPLAYED == 1 && SECTION <53){           //only increment if we are allowed to GO Forward
        
        SECTION = SECTION + 1 ;
        hasPLAYED = 0;              // new section so it has NOT played
        holdOFFSET = 1;             //we've advanced in SECTION - lets stop offset from overriding SECTION
        // EVEN/ODD LED activity - ON if EVEN
        if (SECTION % 2 == 0) { digitalWrite(LED_4, HIGH); }  else{ digitalWrite(LED_4, LOW); }
      }
    }
    Serial.print("         "); Serial.print("SECTION= ");    Serial.println(SECTION);
  
    
    // --- PLAY! ---
    if(PLAY == 1){
      playPattern(SECTION);         // play the music of the current SECTION
      hasPLAYED = 1;                //ok we've played at least once
    }
    else{
      if (SEC_OFFSET == 1 && SECTION == 1) { //indicator for SECTION 1 - all lights ON!
        digitalWrite(LED_1, HIGH); digitalWrite(LED_2, HIGH); digitalWrite(LED_3, HIGH); digitalWrite(LED_4, HIGH);
      }
      else {                         //no section 1, so behave as usual - turn everything off when not playing
        OFF();
      }
    }
  }
  else {
    beat();  
  }
  // ? with jumper 111 ?
  // call playPattern(54) to stop piece
}

void playPattern(int num) {
  switch (num) {
    case 1:
      One();
      break;
    case 2:
      Two();
      break;
    case 3:
      Three();
      break;
    case 4:
      Four();
      break;
    case 5:
      Five();
      break;
    case 6:
      Six();
      break;
    case 7:
      Seven();
      break;
    case 8:
      Eight();
      break;
    case 9:
      Nine();
      break;
    case 10:
      ten();
      break;
    case 11:
      eleven();
      break;
    case 12:
      twelve();
      break;
    case 13:
      thirteen();
      break;
    case 14:
      fourteen();
      break;
    case 15:
      fifteen();
      break;
    case 16:
      sixteen();
      break;
    case 17:
      seventeen();
      break;
    case 18:
      eighteen();
      break;
    case 19:
      nineteen();
      break;
    case 20:
      twenty();
      break;
    case 21:
      twentyOne();
      break;
    case 22:
      twentyTwo();
      break;
    case 23:
      twentyThree();
      break;
    case 24:
      twentyFour();
      break;
    case 25:
      twentyFive();
      break;
    case 26:
      twentySix();
      break;
    case 27:
      twentySeven();
      break;
    case 28:
      twentyEight();
      break;
    case 29:
      twentyNine();
      break;
    case 30:
      thirty();
      break;
    case 31:
      thirtyOne();
      break;
    case 32:
      thirtyTwo();
      break;
    case 33:
      thirtyThree();
      break;
    case 34:
      thirtyFour();
      break;
    case 35:
      thirtyFive();
      break;
    case 36:
      thirtySix();
      break;
    case 37:
      thirtySeven();
      break;
    case 38:
      thirtyEight();
      break;
    case 39:
      thirtyNine();
      break;
    case 40:
      forty();
      break;
    case 41:
      fortyOne();
      break;
    case 42:
      fortyTwo();
      break;
    case 43:
      fortyThree();
      break;
    case 44:
      fortyFour();
      break;
    case 45:
      fortyFive();
      break;
    case 46:
      fortySix();
      break;
    case 47:
      fortySeven();
      break;
    case 48:
      fortyEight();
      break;
    case 49:
      fortyNine();
      break;
    case 50:
      fifty();
      break;
    case 51:
      fiftyOne();
      break;
    case 52:
      fiftyTwo();
      break;
    case 53:
      fiftyThree();
      break;
    case 54:
      // silence to end piece
      break;
  }
}

void One(){
  playNote(C4_note, THIRTY_SECOND, 1);
  playNote(E4_note, EIGHTH, 2);
  playRest(DOTTED_SIXTEENTH);
  playNote(C4_note, THIRTY_SECOND, 1);
  playNote(E4_note, EIGHTH, 2);
  playRest(DOTTED_SIXTEENTH);
  playNote(C4_note, THIRTY_SECOND, 1);
  playNote(E4_note, EIGHTH, 2);
  playRest(DOTTED_SIXTEENTH);
}

void Two(){
  playNote(C4_note, THIRTY_SECOND, 1);
  playNote(E4_note, DOTTED_SIXTEENTH, 2);
  playNote(F4_note, EIGHTH, 3);
  playNote(E4_note, EIGHTH, 2);
  playRest(EIGHTH);   
}

void Three() {
  playRest(EIGHTH);
  playNote(E4_note, EIGHTH, 2);
  playNote(F4_note, EIGHTH, 3);
  playNote(E4_note, EIGHTH, 1);
}

void Four() {
  playRest(EIGHTH);
  playNote(E4_note, EIGHTH, 1);
  playNote(F4_note, EIGHTH, 2);
  playNote(G4_note, EIGHTH, 3);
}

void Five() {
  playNote(E4_note, EIGHTH, 1);
  playNote(F4_note, EIGHTH, 2);
  playNote(G4_note, EIGHTH, 3);
  playRest(EIGHTH);
}

void Six() {
  playNote(C5_note, WHOLE, 7);
  playNote(C5_note, WHOLE, 7);
}

void Seven() {
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(EIGHTH);
  playNote(C4_note, SIXTEENTH, 1);
  playNote(C4_note, SIXTEENTH, 2);
  playNote(C4_note, EIGHTH, 3);
  playRest(EIGHTH);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
}

void Eight() {
  playNote(G4_note, DOTTED_WHOLE, 2);
  playNote(F4_note, WHOLE, 1);
  playNote(F4_note, WHOLE, 1);
}

void Nine() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 1);
  playRest(EIGHTH);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
}

void ten() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 1);
}

void eleven() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
}

void twelve() {
  playNote(F4_note, EIGHTH, 1);
  playNote(G4_note, EIGHTH, 2);
  playNote(B4_note, WHOLE, 4);
  playNote(C5_note, QUARTER, 3);
}

void thirteen() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, DOTTED_EIGHTH, 2);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, EIGHTH, 2);
  playRest(DOTTED_EIGHTH);
  // this is notated as a 16th note tied to a dotted half note
  playNote(G4_note, DOTTED_HALF, 2);
  playRest(SIXTEENTH);
}

void fourteen() {
  playNote(C5_note, WHOLE, 7);
  playNote(B4_note, WHOLE, 6);
  playNote(G4_note, WHOLE, 5);
  playNote(Fs4_note, WHOLE, 4);
}

void fifteen() {
  playNote(G4_note, SIXTEENTH, 1);
  playRest(DOTTED_EIGHTH);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
}

void sixteen() {
  playNote(G4_note, SIXTEENTH, 1);
  playNote(B4_note, SIXTEENTH, 2);
  playNote(C5_note, SIXTEENTH, 3);
  playNote(B4_note, SIXTEENTH, 2);
}

void seventeen() {
  playNote(B4_note, SIXTEENTH, 2);
  playNote(C5_note, SIXTEENTH, 3);
  playNote(B4_note, SIXTEENTH, 2);
  playNote(C5_note, SIXTEENTH, 3);
  playNote(B4_note, SIXTEENTH, 2);
  playRest(SIXTEENTH);
}

void eighteen() {
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, DOTTED_EIGHTH, 1);
  playNote(E4_note, SIXTEENTH, 1);
}

void nineteen() {
  playRest(DOTTED_QUARTER);
  playNote(G5_note, DOTTED_QUARTER, 7);
}

void twenty() {
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(G3_note, DOTTED_EIGHTH, 7);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
}

void twentyOne() {
  playNote(Fs4_note, DOTTED_HALF, 7);
}

void twentyTwo() {
  playNote(E4_note, DOTTED_QUARTER, 1);
  playNote(E4_note, DOTTED_QUARTER, 1);
  playNote(E4_note, DOTTED_QUARTER, 1);
  playNote(E4_note, DOTTED_QUARTER, 1);
  playNote(E4_note, DOTTED_QUARTER, 1);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(B4_note, EIGHTH, 5);
}

void twentyThree() {
  playNote(E4_note, EIGHTH, 1);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(Fs4_note, DOTTED_QUARTER, 2);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(B4_note, QUARTER, 5);
}

void twentyFour() {
  playNote(E4_note, EIGHTH, 1);
  playNote(Fs4_note, EIGHTH, 2);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(G4_note, DOTTED_QUARTER, 3);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(B4_note, EIGHTH, 5);
}

void twentyFive() {
  playNote(E4_note, EIGHTH, 1);
  playNote(Fs4_note, EIGHTH, 2);
  playNote(G4_note, EIGHTH, 3);  
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(A4_note, DOTTED_QUARTER, 4);
  playNote(B4_note, DOTTED_QUARTER, 5);
}

void twentySix() {
  playNote(E4_note, EIGHTH, 1);
  playNote(Fs4_note, EIGHTH, 2);
  playNote(G4_note, EIGHTH, 3);  
  playNote(A4_note, EIGHTH, 4);  
  playNote(B4_note, DOTTED_QUARTER, 5);
  playNote(B4_note, DOTTED_QUARTER, 5);
  playNote(B4_note, DOTTED_QUARTER, 5);
  playNote(B4_note, DOTTED_QUARTER, 5);
  playNote(B4_note, DOTTED_QUARTER, 5);
}

void twentySeven() {
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(G4_note, EIGHTH, 3);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 3);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
}

void twentyEight() {
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, SIXTEENTH, 1);
  playNote(Fs4_note, SIXTEENTH, 2);
  playNote(E4_note, DOTTED_EIGHTH, 1);
  playNote(E4_note, SIXTEENTH, 1);
}

void twentyNine() {
  playNote(E4_note, DOTTED_HALF, 1);
  playNote(G4_note, DOTTED_HALF, 2);
  playNote(C5_note, DOTTED_HALF, 3);
}

void thirty() {
  playNote(C5_note, DOTTED_WHOLE, 7);
}

void thirtyOne() {
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
}

void thirtyTwo() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(F4_note, DOTTED_HALF, 1);
  playRest(SIXTEENTH);
  playNote(G4_note, DOTTED_QUARTER, 2);
}

void thirtyThree() {
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
  playRest(EIGHTH);
}

void thirtyFour() {
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
}

void thirtyFive() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playRest(EIGHTH);
  playRest(QUARTER);
  playRest(QUARTER);
  playRest(QUARTER);
  playNote(Bb4_note, QUARTER, 4);
  playNote(G5_note, DOTTED_HALF, 5);
  playNote(A5_note, EIGHTH, 6);
  playNote(G5_note, QUARTER, 5);
  playNote(B5_note, EIGHTH, 7);
  playNote(A5_note, DOTTED_QUARTER, 6);
  playNote(G5_note, EIGHTH, 5);
  playNote(E5_note, DOTTED_HALF, 4);
  playNote(G5_note, EIGHTH, 5);
  // this is notated as an 8th note tied to a dotted half note
  playNote(Fs5_note, DOTTED_HALF, 4);
  playRest(EIGHTH);

  playRest(QUARTER);
  playRest(QUARTER);
  playRest(EIGHTH);
  // this is notated as an 8th note tied to a half note
  playNote(E5_note, HALF, 4);
  playRest(EIGHTH);

  playNote(F5_note, DOTTED_HALF, 7);
}

void thirtySix() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
}

void thirtySeven() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);  
}

void thirtyEight() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
}

void thirtyNine() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(B4_note, SIXTEENTH, 3);
  playNote(C5_note, SIXTEENTH, 4);
}

void forty() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(F4_note, SIXTEENTH, 1);
}

void fortyOne() {
  playNote(B4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
}

void fortyTwo() {
  playNote(C5_note, WHOLE, 3);
  playNote(B4_note, WHOLE, 2);
  playNote(A4_note, WHOLE, 1);
  playNote(C5_note, WHOLE, 3);
}

void fortyThree() {
  playNote(F5_note, SIXTEENTH, 3);
  playNote(E5_note, SIXTEENTH, 2);
  playNote(F5_note, SIXTEENTH, 3);
  playNote(E5_note, SIXTEENTH, 2);
  playNote(E5_note, EIGHTH, 2);  
  playNote(E5_note, EIGHTH, 2);  
  playNote(E5_note, EIGHTH, 2);  
  playNote(F5_note, SIXTEENTH, 3);
  playNote(E5_note, SIXTEENTH, 2);
}

void fortyFour() {
  playNote(F5_note, EIGHTH, 3);  
  playNote(E5_note, QUARTER, 2);
  playNote(E5_note, EIGHTH, 2);  
  playNote(C5_note, QUARTER, 1);
}

void fortyFive() {
  playNote(D5_note, QUARTER, 3);
  playNote(D5_note, QUARTER, 3);
  playNote(G4_note, QUARTER, 1);
}

void fortySix() {
  playNote(G4_note, SIXTEENTH, 1);
  playNote(D5_note, SIXTEENTH, 2);
  playNote(E5_note, SIXTEENTH, 3);
  playNote(D5_note, SIXTEENTH, 2);
  playRest(EIGHTH);
  playNote(G4_note, EIGHTH, 1);
  playRest(EIGHTH);
  playNote(G4_note, EIGHTH, 1);
  playRest(EIGHTH);
  playNote(G4_note, EIGHTH, 1);
  playNote(G4_note, SIXTEENTH, 1);
  playNote(D5_note, SIXTEENTH, 2);
  playNote(E5_note, SIXTEENTH, 3);
  playNote(D5_note, SIXTEENTH, 2);
}

void fortySeven() {
  playNote(D5_note, SIXTEENTH, 2);
  playNote(E5_note, SIXTEENTH, 3);
  playNote(D5_note, EIGHTH, 2);
}

void fortyEight() {
  playNote(G4_note, DOTTED_WHOLE, 5);
  playNote(G4_note, WHOLE, 5);
  playNote(F4_note, WHOLE, 4);
  playNote(F4_note, QUARTER, 4);
}

void fortyNine() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(Bb4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(Bb4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
}

void fifty() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
}

void fiftyOne() {
  playNote(F4_note, SIXTEENTH, 1);
  playNote(G4_note, SIXTEENTH, 2);
  playNote(Bb4_note, SIXTEENTH, 3);
}

void fiftyTwo() {
  playNote(G4_note, SIXTEENTH, 2);
  playNote(Bb4_note, SIXTEENTH, 3);
}

void fiftyThree() {
  playNote(Bb4_note, SIXTEENTH, 3);
  playNote(G4_note, SIXTEENTH, 2);
}