#define echoPin 26
#define trigPin 2
int led = 13;
int buzzer = 13;

long duration;
int distance;

int dir_1 = 28;
int SPEED_1 = 3;
int sensorPin_0 = A0; 
int sensorPin_1 = A1; 
int sensorPin_2 = A2; 
int sensorPin_3 = A3; 
int sensorPin_4 = A4; 
int sensorPin_5 = A5; 


int dir_2 = 38;
int SPEED_2 = 4;
int sensorPin_6 = A6; 
int sensorPin_7 = A7; 
int sensorPin_8 = A8; 
int sensorPin_9 = A9; 
int sensorPin_10 = A10; 
int sensorPin_11 = A11; 
int threshold = 800;

int statusSensor_0 = 0;  // variable to store the value coming from the sensor
int statusSensor_1 = 0;
int statusSensor_2 = 0;
int statusSensor_3 = 0;
int statusSensor_4 = 0;
int statusSensor_5 = 0;
int statusSensor_6 = 0;  
int statusSensor_7 = 0;
int statusSensor_8 = 0;
int statusSensor_9 = 0;
int statusSensor_10 = 0;
int statusSensor_11 = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (dir_1, OUTPUT);
  pinMode (SPEED_1, OUTPUT);
  pinMode(sensorPin_0, INPUT);
  pinMode(sensorPin_1, INPUT);
  pinMode(sensorPin_2, INPUT);
  pinMode(sensorPin_3, INPUT);
  pinMode(sensorPin_4, INPUT);
  pinMode(sensorPin_5, INPUT);

  
  pinMode (dir_2, OUTPUT);
  pinMode (SPEED_2, OUTPUT);
  pinMode(sensorPin_6, INPUT);
  pinMode(sensorPin_7, INPUT);
  pinMode(sensorPin_8, INPUT);
  pinMode(sensorPin_9, INPUT);
  pinMode(sensorPin_10, INPUT);
  pinMode(sensorPin_11, INPUT);
}

void loop() 
{
  statusSensor_0 = analogRead(sensorPin_0) >= threshold;  // read the value from the sensor:
  statusSensor_1 = analogRead(sensorPin_1) >= threshold;
  statusSensor_2 = analogRead(sensorPin_2) >= threshold;
  statusSensor_3 = analogRead(sensorPin_3) >= threshold;
  statusSensor_4 = analogRead(sensorPin_4) >= threshold;
  statusSensor_5 = analogRead(sensorPin_5) >= threshold;
  statusSensor_6 = analogRead(sensorPin_6) >= threshold;  
  statusSensor_7 = analogRead(sensorPin_7) >= threshold;
  statusSensor_8 = analogRead(sensorPin_8) >= threshold;
  statusSensor_9 = analogRead(sensorPin_9) >= threshold;
  statusSensor_10 = analogRead(sensorPin_10) >= threshold;
  statusSensor_11 = analogRead(sensorPin_11) >= threshold;
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

  Serial.print(statusSensor_0);
  Serial.print(" ");
  Serial.print(statusSensor_1);
  Serial.print(" ");
  Serial.print(statusSensor_2);
  Serial.print(" ");
  Serial.print(statusSensor_3);
  Serial.print(" ");
  Serial.print(statusSensor_4);
  Serial.print(" ");
  Serial.print(statusSensor_5);
  Serial.print(" ");
  Serial.print(statusSensor_6);
  Serial.print(" ");
  Serial.print(statusSensor_7);
  Serial.print(" ");
  Serial.print(statusSensor_8);
  Serial.print(" ");
  Serial.print(statusSensor_9);
  Serial.print(" ");
  Serial.print(statusSensor_10);
  Serial.print(" ");
  Serial.print(statusSensor_11);
  Serial.print(" \n");

  
  if (distance >=20)
  {
   if (statusSensor_0 == 0 && statusSensor_1 == 0 && statusSensor_2 == 0 && statusSensor_3 == 0 && statusSensor_4 == 0 
    && statusSensor_5 == 0 && statusSensor_6 == 0 && statusSensor_7 == 0 && statusSensor_8 == 0 && statusSensor_9 == 0
    && statusSensor_10 == 0 && statusSensor_11 == 0)
    {
      digitalWrite(dir_1, LOW); 
      analogWrite(SPEED_1, 0);
      digitalWrite(dir_2, LOW); 
      analogWrite(SPEED_2, 0);
      digitalWrite(led, LOW);
      Serial.print("Stop\n");
    }

    else if ((statusSensor_0 == 0 && statusSensor_1 == 0 && statusSensor_2 == 0 && statusSensor_3 == 0 && statusSensor_4 == 0 
    && statusSensor_5 == 0 && statusSensor_6 == 1 && statusSensor_7 == 1 && statusSensor_8 == 1 && statusSensor_9 == 1
    && statusSensor_10 == 1 && statusSensor_11 == 1)
    {
      digitalWrite(dir_1, LOW); 
      analogWrite(SPEED_1, 0);
      digitalWrite(dir_2, LOW); 
      analogWrite(SPEED_2, 200);
      Serial.print("Moving right\n");
    }

    else if (statusSensor_0 == 1 && statusSensor_1 == 1 && statusSensor_2 == 1 && statusSensor_3 == 1 && statusSensor_4 == 1
    && statusSensor_5 == 1 && statusSensor_6 == 0 && statusSensor_7 == 0 && statusSensor_8 == 0 && statusSensor_9 == 0
    && statusSensor_10 == 0 && statusSensor_11 == 0)
    {
      digitalWrite(dir_1, LOW); 
      analogWrite(SPEED_1, 200);
      digitalWrite(dir_2, LOW); 
      analogWrite(SPEED_2, 0);
      Serial.print("Moving left\n");
    }


    else if (statusSensor_0 == 1 && statusSensor_1 == 1 && statusSensor_2 == 1 && statusSensor_3 == 1 && statusSensor_4 == 1
    && statusSensor_5 == 1 && statusSensor_6 == 1 && statusSensor_7 == 1 && statusSensor_8 == 1 && statusSensor_9 == 1
    && statusSensor_10 == 1 && statusSensor_11 == 1)
    {
      digitalWrite(dir_1, LOW); 
      analogWrite(SPEED_1, 150);
      digitalWrite(dir_2, LOW); 
      analogWrite(SPEED_2, 150);
      Serial.print("Moving forward\n");
    }
        
  }

  else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    Serial.print("Obstacle detected\n");
    digitalWrite(dir_1, LOW); 
    analogWrite(SPEED_1, 200);
    digitalWrite(dir_2, LOW); 
    analogWrite(SPEED_2, 200);
  }
  

}
