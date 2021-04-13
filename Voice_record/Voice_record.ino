#define record_time 10000
const int pin[] = {42, 44, 46, 48, 50, 52};
const int record_pin = 40;

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*make_low(record_pin);
  for(int i = 0; i < 6; i++) {
    Serial.print("Recording audio in message ");
    Serial.print(i);
    Serial.print(" \n");
    record(pin[i]);
  }*/
  
  open_circuit(record_pin);
  for(int i = 0; i < 6; i++) {
    Serial.print("Playing recorded audio in message ");
    Serial.print(i);
    Serial.print(" \n");
    open_circuit(34);
    play(pin[i]);
  }
  
  while(1);
}
