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

unsigned int C4_note = 261.63;
unsigned int E4_note = 329.63;
unsigned int F4_note = 349.23;
unsigned int Fs4_note = 369.99;
unsigned int G4_note = 392;

unsigned int C5_note = 523.25;

int tempo = 120;
const double tempoConversion = 60000.0;
double thirtySecondNoteDuration = tempoConversion / tempo / 8;
const int THIRTY_SECOND = 1; // 62.5ms
const int SIXTEENTH = 2; // 125ms
const int DOTTED_SIXTEENTH = 3; // 187.5ms
const int EIGHTH = 4; // 250ms
const int DOTTED_EIGHTH = 6; // 375ms
const int QUARTER = 8; // 500ms
const int DOTTED_QUARTER = 12; // 750ms
const int HALF = 16; // 1000ms

void playNote(unsigned int frequency, int duration, int led) {
  tone(8, frequency);
  lightOn(led);
  if (duration == THIRTY_SECOND) {
    delay(thirtySecondNoteDuration*duration);
    OFF();
  }
  else {
    delay(thirtySecondNoteDuration*duration-50);
    OFF();
    delay(50);
  }
}

void playRest(int duration) {
  OFF();
  delay(thirtySecondNoteDuration*duration);
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

  Serial.begin(9600);    // initialize serial:
}


void loop(){
  // call the melodies and just test as needed
  // beat(); // eight note pulse over everything
  for (int i = 1; i <= 6; i++) {
    // selectPattern(i);
  }
}

void selectPattern(int num) {
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


void OFF(){
      noTone(8);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
}

void beat(){
    tone(8,C5_note*2);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH); 
    delay(75);
    OFF();
    delay(175);
}

    
