int r18 = 18;
int r19 = 19;
int r20 = 20;
int r21 = 21;
int r22 = 22;
int r23 = 23;
int r24 = 24;
int r25 = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(r18, OUTPUT);
  pinMode(r19, OUTPUT);
  pinMode(r20, OUTPUT);
  pinMode(r21, OUTPUT);
  pinMode(r22, OUTPUT);
  pinMode(r23, OUTPUT);
  pinMode(r24, OUTPUT);
  pinMode(r25, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(r18, LOW);
  digitalWrite(r19, LOW);
  digitalWrite(r20, LOW);
  digitalWrite(r21, LOW);
  digitalWrite(r22, LOW);
  digitalWrite(r23, LOW);
  digitalWrite(r24, LOW);
  digitalWrite(r25, LOW);
  
  delay(1000);
  
  digitalWrite(r18, HIGH);
  digitalWrite(r19, HIGH);
  digitalWrite(r20, HIGH);
  digitalWrite(r21, HIGH);
  digitalWrite(r22, HIGH);
  digitalWrite(r23, HIGH);
  digitalWrite(r24, HIGH);
  digitalWrite(r25, HIGH);
  
  delay(1000);
}
