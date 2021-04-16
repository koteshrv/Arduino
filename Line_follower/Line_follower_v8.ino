#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

#define STOP_COUNT 6
#define record_time 10000

#define SD_ChipSelectPin 53
#define echoPin 26
#define trigPin 2
#define threshold 900
#define buzzer 9
#define record_play_button 3
#define record_pin 40
#define record_button 13
#define play_button 14

const int sound_module_pins[] = {42, 44, 46, 48, 50, 52};
const int sensorPins[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
const int dir_pins[2] = {36, 38};
const int pwm_pins[2] = {5, 6};


int message_count = 0;
int record_button_count = 0;
int station_count = 0;
unsigned long stopped_time;
long duration;
int distance;
int statusSensor[12] = {0};
bool reached_destination = false;
bool isRecording = false;
bool is_playing = false;
bool stopFlag = true;

TMRpcm tmrpcm;

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

void open_circuit(int n) {
  pinMode (n, INPUT) ;
}

void make_low(int n) {
  pinMode (n, OUTPUT);
  digitalWrite (n, LOW) ;
}

void play_message(int n) {
  open_circuit(n);
  delay(1000);
  make_low(n);
  delay(1000);
  open_circuit(n);
  delay(record_time - 2000); // 2500
  make_low(n);
  delay(500);
  open_circuit(n);
}

void recording_audio_in_message(int message_pin) {
  Serial.print("Recording audio in message ");
  Serial.print(message_count);
  Serial.print(" \n");
  make_low(sound_module_pins[message_pin]);
}

void stop_recording_in_message(int message_pin) {
  Serial.print("Stoping recording in message ");
  Serial.print(message_count);
  Serial.print(" \n");
  open_circuit(sound_module_pins[message_pin]);
}

void record_interupt() {
  if(tmrpcm.isPlaying())  tmrpcm.disable();
  is_playing = true;
}

void play_interupt() {
  if(tmrpcm.isPlaying())  tmrpcm.disable();
  isRecording = true;
}


void record() {
  if(!reached_destination && record_button_count < 7) {
    make_low(record_pin);
    recording_audio_in_message(record_button_count);
  }

  else if(record_button_count > 6) {
    Serial.print("Sorry! Can't record any more messages\n");
  }
  record_button_count++;
}

void stop_record() {
    make_low(record_pin);
    stop_recording_in_message(record_button_count);
}

void playing() {
  open_circuit(record_pin);
  for (int i = 0; i < record_button_count; i++) {
    Serial.print("Playing recorded audio in message ");
    Serial.print(message_count);
    Serial.print(" \n");
    play_message(sound_module_pins[message_count++]);
  }
}


int check(int a[], int b[]) {
  int ar_count = 0;
  for (int i = 0; i < 12; i++) {
    if (a[i] == b[i]) ar_count++;
  }
  if (ar_count == 12) return 1;
  return 0;
}

void motors(int dir0, int dir1, int pwm0, int pwm1) {
  digitalWrite(dir_pins[0], dir0);
  analogWrite(dir_pins[0], pwm0);
  digitalWrite(dir_pins[1], dir1);
  analogWrite(dir_pins[1], pwm1);
}

void print_sensor_values() {
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

  for (int i = 0; i < 12; i++) {
    Serial.print(statusSensor[i]);
    Serial.print(" ");
  }
  Serial.print(" \n");
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
  pinMode (dir_pins[0], OUTPUT);
  pinMode (dir_pins[1], OUTPUT);
  pinMode(dir_pins[0], OUTPUT);
  pinMode(dir_pins[1], OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(record_play_button, INPUT);
  attachInterrupt(digitalPinToInterrupt(record_button), record_interupt, RISING);
  attachInterrupt(digitalPinToInterrupt(play_button), play_interupt, RISING);
  for (int i = 0; i < 12; i++) pinMode(sensorPins[i], INPUT);
  tmrpcm.speakerPin = 11;
  if(!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  else Serial.println("SD card initialized");
}

void loop()
{
  for (int i = 0; i < 12; i++) statusSensor[i] = (analogRead(sensorPins[i]) >= threshold);
  print_sensor_values();

  if (distance >= 20)
  {
    if (IR_status(statusSensor) == 0)
    {
      station_count++;
      if (station_count < STOP_COUNT) {
        motors(0, 0, 0, 0);
        Serial.print("Stoping here for the next ");
        Serial.print("15");
        Serial.print(" seconds\n");
        Serial.print("If you want some thing, then press the record button\n");
        // if(stopFlag) stopped_time = millis();
        tmrpcm.play("stop_audio.wav");
        if(isRecording) {
          record();
          delay(10000); //while(millis() - stopped_time < record_time);
          stop_record();
        }
        else delay(15000);
        motors(0, 0, 80, 80);
        delay(1000);
        stopFlag = true;
        isRecording = false;
      }
      else {
        motors(0, 0, 0, 0);
        Serial.print("Reached Destination\n");
        while(1) {
          tmrpcm.play("End_audio.wav");
          if(is_playing) playing();
        }
      }
    }

    else if (IR_status(statusSensor) == 1) {
      motors(0, 0, 100, 100); //85
      Serial.print("Moving Forward\n");
    }

    else if (IR_status(statusSensor) == 2) {
      motors(0, 0, 70, 0); //60, 0
      Serial.print("Moving Left\n");
      turning_sound();
    }

    else if (IR_status(statusSensor) == 3) {
      motors(0, 0, 0, 70); // 0, 60
      Serial.print("Moving Right\n");
      turning_sound();
    }


    else {
      motors(0, 0, 60, 60);
      Serial.print("Invalid path\n");
      tmrpcm.play("invalid_path_audio.wav");
    }
  }

  else {
    Serial.print("Obstacle detected\n");
    motors(0, 0, 0, 0);
    tmrpcm.play("obstacle_detected_audio.wav");
  }
}
