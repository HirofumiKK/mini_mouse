
#define bled 2
#define gled 8
#define rled 12

#define left 19
#define middle 18
#define right 17

#define lmotor 3
#define rmotor 5

//Period = 1/500Hz = 0.0005 S
//62 45 49
//Goal: l:300 m:143 r:337

float duty = 0.5;
float PWM = duty*255;
int old_error_m = 0;
int error_m = 0;
int error_lr = 0;
int e_PWM = 0;

float Kpm = 0.25;
float Kdm = 0.001;

void setup() {
  Serial.begin(9600);
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(bled, OUTPUT);
  
  pinMode(left, INPUT);
  pinMode(middle, INPUT);
  pinMode(right, INPUT);
  
  pinMode(lmotor, OUTPUT);
  pinMode(rmotor, OUTPUT);
}

void loop() {
  error_m = 343 - analogRead(middle);
  e_PWM = Kpm*error_m + Kdm*(error_m - old_error_m);
  if (e_PWM < 15) {
    digitalWrite(gled, HIGH);
    analogWrite(lmotor, PWM);
    analogWrite(rmotor, PWM*1.6);
    delay(1);
    digitalWrite(gled, LOW);
  }
  else if (analogRead(left) < 215) {   //turn right
    digitalWrite(rled, HIGH);
    analogWrite(lmotor, PWM + e_PWM);
    analogWrite(rmotor, PWM*1.6 - e_PWM);
    delay(1);
    digitalWrite(rled, LOW);
  }
  else {                          //turn left
    digitalWrite(bled, HIGH);
    analogWrite(lmotor, PWM - e_PWM);
    analogWrite(rmotor, PWM*1.6 + e_PWM);
    delay(1);
    digitalWrite(bled, LOW);
  }
  old_error_m = error_m;
  Serial.println(e_PWM);

  if (analogRead(middle) > 300 && analogRead(left) > 350 && analogRead(right) > 500) {
    digitalWrite(rled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(gled, HIGH);
    analogWrite(lmotor, 0);
    analogWrite(rmotor, 0);
    while (true) {}
  }
  
  /*digitalWrite(rled, HIGH);
  digitalWrite(gled, HIGH);
  digitalWrite(bled, HIGH);
  delay(1000);
  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);
  digitalWrite(bled, LOW);
  delay(1000);*/
  
  /*int inpl = analogRead(left);
  int inpm = analogRead(middle);
  int inpr = analogRead(right); 
  Serial.print(inpl);
  Serial.print("\t");
  Serial.print(inpm);
  Serial.print("\t");
  Serial.print(inpr);
  Serial.println();*/
  
}
