/* 

IN C BOT - isolate beat function
04112024 - Oliver Xu

autopilot button is used to start and stop the 8th note pulse

----------------------

IN C BOT - button control
04082024 - Levy Lorenzo
NEW FEATURES
   * TWO modes of operation
   * 1:  BEAT jumpers at 111 - 
   * 2:  NORMAL PLAY jumpers not at 111
- DIP switch jumps to patterns according to red boxes in score
- PLAY (middle button)  - plays music of current pattern
- At Power Up - with DIP to 0000, init to pattern 1, with all LED's on
- Press of NEXT will increment pattern by 1
- Another increment will only be allowed if a current pattern is played at least once 
- ALL LEDS ON - anytime we are in standing by in pattern 1
- LED even/odd indicator:  LED 4 is ON when current pattern is EVEN and off when ODD
- ending condition to never increment past pattern 53 (the last pattern )

USER INSTRUCTIONS
- place all jumpers down to 0000
- plug in usb cable
- all lights will turn on - we are waiting in pattern 1
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

char LED_1 = 9;   // sound visualizer 
char LED_2 = 10;  // sound visualizer 
char LED_3 = 11;  // sound visualizer 
char LED_4 = 12;  // odd/even indicator of forward/back movement

char B2_autopilot = 2;  // button - autopilot

volatile boolean autopilotActive = 0; // flag to determine if autopilot is active

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

unsigned long lastInterruptTime = 0;
unsigned long startMillis = 0;
unsigned long currentMillis = 0;

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

void autopilotToggle() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    autopilotActive = (autopilotActive == 1) ? 0 : 1;
  }
  lastInterruptTime = interruptTime;
}

void setup() {
  pinMode(B2_autopilot, INPUT); // button to enable and disable autopilot
  attachInterrupt(digitalPinToInterrupt(B2_autopilot), autopilotToggle, RISING);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600); // initialize serial
  startMillis = millis();
}


void loop(){
  currentMillis = millis();
  if (autopilotActive) {
    if (currentMillis - startMillis >= thirtySecondNoteDuration*EIGHTH) {
      beat();
      startMillis = currentMillis;
    }
  }
}