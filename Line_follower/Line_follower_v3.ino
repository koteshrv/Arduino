#define echoPin 26
#define trigPin 2
#define led 13
#define buzzer 12
#define threshold 900
long duration;
int distance;

int sensorPins[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
int dir[2] = {36, 38};
int pwm[2] = {5, 6};
int statusSensor[12] = {0}; 


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
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 0);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 0);
      digitalWrite(led, LOW);
      Serial.print("Stop\n");
    }

    else if(IR_status(statusSensor) == 1) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 100);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 100);
      digitalWrite(led, HIGH);
      Serial.print("Moving Forward\n");
    }

    else if(IR_status(statusSensor) == 2) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 0);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 70);
      digitalWrite(led, HIGH);
      Serial.print("Moving Left\n");
    }

    else if(IR_status(statusSensor) == 3) {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 70);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 0);
      digitalWrite(led, HIGH);
      Serial.print("Moving Right\n");
    }


    else {
      digitalWrite(dir[0], LOW); 
      analogWrite(pwm[0], 60);
      digitalWrite(dir[1], LOW); 
      analogWrite(pwm[1], 60);
      digitalWrite(led, LOW);
      Serial.print("Invalid path\n");
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
  }
  

}
