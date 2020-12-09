// Motor driver connections
int pwm_left = 5;
int pwm_right = 6;
int motor_left = 7;
int motor_right = 8;

// IR sensor connections
int left_sensor_pin = A0;
int right_sensor_pin = A1;

int left_sensor_state;
int right_sensor_state;

int speed = 100;
int turn_speed = 150;

void setup() {
    pinMode(motor_left, OUTPUT);
    pinMode(motor_right, OUTPUT);
    Serial.begin(9600);
}


void loop() {
  
    left_sensor_state = analogRead(left_sensor_pin);
    right_sensor_state = analogRead(right_sensor_pin);

    if(right_sensor_state > 500 && left_sensor_state < 500) {
        Serial.println("Turning right");

        digitalWrite (motor_right,LOW);
        digitalWrite(motor_left,HIGH);                       

        analogWrite (pwm_left, vSpeed);

    }

    if(right_sensor_state < 500 && left_sensor_state > 500) {
        Serial.println("Turning left");

        digitalWrite (motor_right,HIGH);
        digitalWrite(motor_left,LOW);

        analogWrite (motor_right, turn_speed);
    }

    if(right_sensor_state > 500 && left_sensor_state > 500) {
        Serial.println("Going forward");

        digitalWrite (motor_right,HIGH);
        digitalWrite(motor_left,HIGH);                       

        analogWrite (pwm_left, speed);
        analogWrite (pwm_right, speed);

    }

    if(right_sensor_state < 500 && left_sensor_state < 500) { 
        Serial.println("STOP");

        analogWrite (pwm_right, 0);
        analogWrite (pwm_left, 0);

    }

}
