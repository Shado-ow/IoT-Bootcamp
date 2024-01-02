

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D2, INPUT); //echo
  pinMode(D1, OUTPUT); //trigger
  pinMode(D3, OUTPUT); // red
  pinMode(D4, OUTPUT); // yellow
  pinMode(D7, OUTPUT); // green
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D2, LOW);
  delayMicroseconds(2);

  digitalWrite(D1, HIGH);
  delayMicroseconds(10);
  digitalWrite(D1, LOW);

  float duration = pulseIn(D2,HIGH);
  //Serial.print("duration: ");
  //Serial.println(duration);
  float speed = 0.0343;
  float distance = (duration * speed) / 2; 
  Serial.print("Distance:");
  Serial.println(distance);

  if(distance < 8){
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    digitalWrite(D7, LOW);
  }
  else if(distance >= 8 && distance <=15)
  {
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    digitalWrite(D7, LOW);
  }
  else if(distance >= 15 && distance <= 200){
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D7, HIGH);
  }

  delay(1000);


}
