// Motor driver connections
int pwm_left = 5;
int pwm_right = 6;
int motor_left = 7;
int motor_right = 8;

// IR sensor connections
int left_sensor_pin = A0;
int right_sensor_pin = A1;


// Ultra Sonic sensor connections
int echo_pin = 2;
int trigger_pin = 3;

int left_sensor_state;
int right_sensor_state;
long duration;
int distance;

int speed = 100;
int turn_speed = 150;

void setup() {
    pinMode(motor_left, OUTPUT);
    pinMode(motor_right, OUTPUT);
    pinMode(trigger_pin, OUTPUT);
    pinMode(left_sensor_pin, INPUT);
    pinMode(right_sensor_pin, INPUT);
    pinMode(echo_pin, INPUT);
    Serial.begin(9600);
}

void loop() {
  
    left_sensor_state = digitalRead(left_sensor_pin);
    right_sensor_state = digitalRead(right_sensor_pin);

    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    duration = pulseIn(echo_pin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if(right_sensor_state == 1 && left_sensor_state == 0 && distance > 18){
        Serial.println("Turning right");

        digitalWrite (motor_right,LOW);
        digitalWrite(motor_left,HIGH);                       

        sigital (pwm_left, HIGH);

    }

    if(right_sensor_state == 0 && left_sensor_state == 1 && distance > 18) {
        Serial.println("Turning left");

        digitalWrite (motor_right,HIGH);
        digitalWrite(motor_left,LOW);

        analogWrite (motor_right, turn_speed);
    }

    if(right_sensor_state == 1 && left_sensor_state == 1 && distance > 18) {
        Serial.println("Going forward");

        digitalWrite (motor_right,HIGH);
        digitalWrite(motor_left,HIGH);                       

        analogWrite (pwm_left, speed);
        analogWrite (pwm_right, speed);

    }

    if(right_sensor_state == 0 && left_sensor_state == 0 && distance < 18) { 
        Serial.println("STOP");

        digitalWrite (motor_right,LOW);
        digitalWrite(motor_left,LOW);
        analogWrite (pwm_right, 0);
        analogWrite (pwm_left, 0);

    }

}
