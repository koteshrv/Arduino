#define echoPin 26
#define trigPin 2
#define led 13
#define buzzer 9
#define threshold 900
#define STOP_COUNT 6
#define STOP_TIME 5000
#define record_time 10000
const int pin[] = {42, 44, 46, 48, 50, 52};
const int record_pin = 40; 
int message_count = 0;
bool isPlayed = false;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int count = 0;
long duration;
int distance;

int sensorPins[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
int dir[2] = {36, 38};
int pwm[2] = {5, 6};
int statusSensor[12] = {0}; 

// change this to make the song slower or faster
int mario_tempo = 200;
int pacman_tempo = 105;

int mario_melody[] = {
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
  REST,1, 
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
  
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  
  //game over sound
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

};

int pacman_melody[] = {

  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int mario_notes = sizeof(mario_melody) / sizeof(mario_melody[0]) / 2;

// this calculates the duration of a whole note in ms
int mario_wholenote = (60000 * 4) / mario_tempo;

int mario_divider = 0, mario_noteDuration = 0;

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int pacman_notes = sizeof(pacman_melody) / sizeof(pacman_melody[0]) / 2;

// this calculates the duration of a whole note in ms
int pacman_wholenote = (60000 * 4) / pacman_tempo;

int pacman_divider = 0, pacman_noteDuration = 0;

void error_sound() {
  tone(buzzer, 2000); 
  delay(1000);       
}

void turning_sound() {
  tone(buzzer, 1000); 
  delay(500);       
  noTone(buzzer);     
  delay(500); 
}


void stop_sound() {
  for (int thisNote = 0; thisNote < pacman_notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    pacman_divider = pacman_melody[thisNote + 1];
    if (pacman_divider > 0) {
      // regular note, just proceed
      pacman_noteDuration = (pacman_wholenote) / pacman_divider;
    } else if (pacman_divider < 0) {
      // dotted pacman_notes are represented with negative durations!!
      pacman_noteDuration = (pacman_wholenote) / abs(pacman_divider);
      pacman_noteDuration *= 1.5; // increases the duration in half for dotted pacman_notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, pacman_melody[thisNote], pacman_noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(pacman_noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  delay(1000);   
}

void end_sound() {
  for (int thisNote = 0; thisNote < mario_notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    mario_divider = mario_melody[thisNote + 1];
    if (mario_divider > 0) {
      // regular note, just proceed
      mario_noteDuration = (mario_wholenote) / mario_divider;
    } else if (mario_divider < 0) {
      // dotted mario_notes are represented with negative durations!!
      mario_noteDuration = (mario_wholenote) / abs(mario_divider);
      mario_noteDuration *= 2;//1.5 // increases the duration in half for dotted mario_notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, mario_melody[thisNote], mario_noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(mario_noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void open_circuit(int n) {
  pinMode (n, INPUT) ;
}

void make_low(int n) {
   pinMode (n, OUTPUT);
   digitalWrite (n, LOW) ;
}

void record(int n) {
  make_low(n);
  delay(record_time);
  open_circuit(n);
  delay(500);
}

void play(int n) {
  open_circuit(n);
  delay(1000);
  make_low(n);
  delay(1000);
  open_circuit(n);
  delay(record_time - 2000);//2500
  make_low(n);
  delay(500);
  open_circuit(n);
  //delay(500);
}

void recording_audio() {
  Serial.print("Recording audio in message ");
  Serial.print(message_count);
  Serial.print(" \n");
  record(pin[message_count++]);
}

void play_recorded_audio() {
  message_count = 0;
  open_circuit(record_pin);
  for(int i = 0; i < 6; i++) {
    Serial.print("Playing recorded audio in message ");
    Serial.print(message_count);
    Serial.print(" \n");
    play(pin[message_count++]);
  }
}

int check(int a[], int b[]) {
  int count = 0;
  for(int i = 0; i < 12; i++) {
    if(a[i] == b[i]) count++;
  }
  if(count == 12) return 1;
  return 0;
}

int IR_status(int ar[]) {

  int stop[12]      =        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  
  int forward1[12]  =        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
  int forward2[12]  =        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0};
  int forward3[12]  =        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0};
  int forward4[12]  =        {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0};
  int forward5[12]  =        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0};
  int forward6[12]  =        {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0};
  
  int right1[12]    =        {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
  int right2[12]    =        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
  int right3[12]    =        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  int right4[12]    =        {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
  int right5[12]    =        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
  int right6[12]    =        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
  int right7[12]    =        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

  int left1[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0};
  int left2[12]     =        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0};
  int left3[12]     =        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
  int left4[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0};
  int left5[12]     =        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
  int left6[12]     =        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0};
  int left7[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};


  if (check(ar, stop)) return 0;

  if (check(ar, forward1)) return 1;
  if (check(ar, forward2)) return 1;
  if (check(ar, forward3)) return 1;
  if (check(ar, forward4)) return 1;
  if (check(ar, forward5)) return 1;
  if (check(ar, forward6)) return 1;

  if (check(ar, left1)) return 2;
  if (check(ar, left2)) return 2;
  if (check(ar, left3)) return 2;
  if (check(ar, left4)) return 2;
  if (check(ar, left5)) return 2;
  if (check(ar, left6)) return 2;
  if (check(ar, left7)) return 2;

  if (check(ar, right1)) return 3;
  if (check(ar, right2)) return 3;
  if (check(ar, right3)) return 3;
  if (check(ar, right4)) return 3;
  if (check(ar, right5)) return 3;
  if (check(ar, right6)) return 3;
  if (check(ar, right7)) return 3;
  
  return -1;
}


void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (dir[0], OUTPUT);
  pinMode (dir[1], OUTPUT);
  pinMode(pwm[0], OUTPUT);
  pinMode(pwm[1], OUTPUT);
  pinMode(buzzer, OUTPUT);
  for(int i = 0; i < 12; i++) pinMode(sensorPins[i], INPUT);
}

void loop() 
{
  for(int i = 0; i < 12; i++) statusSensor[i] = (analogRead(sensorPins[i])>= threshold);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);   
  Serial.print("\n"); 

  for(int i = 0; i < 12; i++) {
    Serial.print(statusSensor[i]);
    Serial.print(" ");
  }
  Serial.print(" \n");

  
  if (distance >=20)
  {
   if (IR_status(statusSensor) == 0)
    {
      count++;
      if(count < STOP_COUNT) {
        digitalWrite(dir[0], LOW); 
        analogWrite(pwm[0], 0);
        digitalWrite(dir[1], LOW); 
        analogWrite(pwm[1], 0);
        digitalWrite(led, LOW);
        Serial.print("Stoping for ");
        Serial.print("12");
        Serial.print(" seconds\n");
        //delay(STOP_TIME);
        stop_sound();
        make_low(record_pin);
        recording_audio();
        digitalWrite(dir[0], LOW); 
        analogWrite(pwm[0], 80);
        digitalWrite(dir[1], LOW); 
        analogWrite(pwm[1], 80);
        delay(1000);
      }
      else {
        digitalWrite(dir[0], LOW); 
        analogWrite(pwm[0], 0);
        digitalWrite(dir[1], LOW); 
        analogWrite(pwm[1], 0);
        digitalWrite(led, LOW);
        Serial.print("Reached Destination\n");
        end_sound();
        if(!isPlayed) {
          play_recorded_audio();
          isPlayed = true;
        }
      }
    }

    else if(IR_status(statusSensor) == 1) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 85);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 85 );
      digitalWrite(led, HIGH);
      Serial.print("Moving Forward\n");
    }

    else if(IR_status(statusSensor) == 2) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 60);//70
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 0);
      digitalWrite(led, HIGH);
      Serial.print("Moving Left\n");
      turning_sound();
    }

    else if(IR_status(statusSensor) == 3) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 0);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 60);//70
      digitalWrite(led, HIGH);
      Serial.print("Moving Right\n");
      turning_sound();
    }


    else {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 60);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 60);
      digitalWrite(led, LOW);
      Serial.print("Invalid path\n");
      //error_sound();
    }
        
  }

  else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, LOW);
    Serial.print("Obstacle detected\n");
    digitalWrite(dir[0], LOW); 
    analogWrite(pwm[0], 0);
    digitalWrite(dir[1], LOW); 
    analogWrite(pwm[1], 0);
    error_sound();
  }
  

}
