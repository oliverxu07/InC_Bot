/* IN C BOT 
march 23 code for Oliver
output coding - 
- all 53 IN C modules
- direct LED behavior for each to visualize the melodic modules

- initial version has hard coded 250 ms per 1/8th note.
- code a more general timing scheme that does the math from a larger global tempo variable

later goals:
- PLAY current module with button 1
- go FORWARD with button 2
- go REVERSE with button 3
- use 3 bit jumper setting to allow JUMP/OFFSET to middle points in the score

*/

char LED_1 = 9;   // sound visusalizer 
char LED_2 = 10;  // sound visusalizer 
char LED_3 = 12;  // sound visusalizer 
// NOT CONNECTED
char LED_4 = 11;  // odd/even indicator of forward/back movement

const int tuningStandard = 440;
// in equal temperament, frequency of MIDI note number m is calculated with:
// freq = 440 * 2^((m-69)/12)
unsigned int G3_note = tuningStandard * pow(2.0, (55 - 69) / 12.0);
unsigned int C4_note = tuningStandard * pow(2.0, (60 - 69) / 12.0);
unsigned int E4_note = tuningStandard * pow(2.0, (64 - 69) / 12.0);
unsigned int F4_note = tuningStandard * pow(2.0, (65 - 69) / 12.0);
unsigned int Fs4_note = tuningStandard * pow(2.0, (66 - 69) / 12.0);
unsigned int G4_note = tuningStandard * pow(2.0, (67 - 69) / 12.0);
unsigned int A4_note = tuningStandard * pow(2.0, (69 - 69) / 12.0);
unsigned int Bb4_note = tuningStandard * pow(2.0, (70 - 69) / 12.0);
unsigned int B4_note = tuningStandard * pow(2.0, (71 - 69) / 12.0);
unsigned int C5_note = tuningStandard * pow(2.0, (72 - 69) / 12.0);
unsigned int D5_note = tuningStandard * pow(2.0, (74 - 69) / 12.0);
unsigned int G5_note = tuningStandard * pow(2.0, (79 - 69) / 12.0);

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
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600); // initialize serial
}


void loop(){
  // call the melodies and just test as needed
  // beat(); // eight note pulse over everything
  for (int i = 10; i <= 20; i++) {
    // playPattern(i);
    // playPattern(i);
    // playPattern(i);
    // playPattern(i);
  }
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
  playNote(C5_note, HALF, 7);
  playNote(C5_note, HALF, 7);
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
  playNote(G4_note, DOTTED_HALF, 2);
  playNote(F4_note, HALF, 1);
  playNote(F4_note, HALF, 1);
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
  // the written pattern has a 16th note tied to a dotted half note
  playNote(G4_note, DOTTED_HALF, 2);
  playRest(SIXTEENTH);
}

void fourteen() {
  playNote(C5_note, HALF, 7);
  playNote(B4_note, HALF, 6);
  playNote(G4_note, HALF, 5);
  playNote(Fs4_note, HALF, 4);
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

void twentySeven(){
  
    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);

    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);


    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);


    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);



    tone(8,G4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH); 
    delay(200);
    OFF();
    delay(50);


    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);

    tone(8,G4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH); 
    delay(75);
    OFF();
    delay(50);

    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);

      tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(75);
    OFF();
    delay(50);
}




    
