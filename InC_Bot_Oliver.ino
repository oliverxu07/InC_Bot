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
char LED_3 = 11;  // sound visusalizer 
char LED_4 = 12;  // odd/even indicator of forward/back movement

unsigned int C4_note = 261.63;
unsigned int E4_note = 329.63;
unsigned int F4_note = 349.23;
unsigned int Fs4_note = 369.99;
unsigned int G4_note = 392;

unsigned int C5_note = 523.25;
void setup() {

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);


  Serial.begin(9600);    // initialize serial:
}


void loop(){
  // call the melodies and just test as needed
  
  //One(); One(); One();
  //Two(); Two(); Two();
 // Three(); Three(); Three();
  twentySeven(); twentySeven();


//  beat(); // eight note pulse over everything
}


void One(){
    tone(8,C4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(50);
    tone(8,E4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(200);
    noTone(8);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(250);    

    tone(8,C4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(50);
    tone(8,E4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(200);
    noTone(8);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(250);    

    tone(8,C4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(50);
    tone(8,E4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(200);
    noTone(8);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(250);    

}


void Two(){
    tone(8,C4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(50);
    tone(8,E4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW);     
    delay(200);
    tone(8,F4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(250);
    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(250);
    noTone(8);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(250);    
}


void Three(){ //this is just an example of what can be don

    tone(8,200);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW);     
    delay(100);

    tone(8,300);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW);       
    delay(100);

    tone(8,859);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW);       
    delay(100);

    tone(8,2753);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH);       
    delay(1000);

}

/*
void twentySeven(){  // version with no gaps between notes

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,G4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH); 
    delay(250);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(125);  
    tone(8,G4_note);
      digitalWrite(LED_1, HIGH); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, HIGH); 
    delay(125);

        tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,Fs4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, LOW); 
      digitalWrite(LED_3, HIGH); 
      digitalWrite(LED_4, LOW); 
    delay(125);

    tone(8,E4_note);
      digitalWrite(LED_1, LOW); 
      digitalWrite(LED_2, HIGH); 
      digitalWrite(LED_3, LOW); 
      digitalWrite(LED_4, LOW); 
    delay(100);

    noTone(8);
        delay(25);
   
}
*/

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

    
