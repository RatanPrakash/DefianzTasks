// defines pins numbers
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;

//const float Pi = 3.14159; 
//const float oneDegtoRad = Pi/180;

const int angle_toMove = 60;
const double Nema23constAng = 0.9;        //0.9 degrees step 
const int microStep = 8;

void steerRight(int moveAngle){
  //Right
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

  for(int x = 0; x < (microStep * (moveAngle/Nema23constAng)) ; x++){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(100); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100); 
    Serial.print("Steering Right!!");
 }
}

void steerLeft(int moveAngle){
  //Left
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction

  for(int x = 0; x < (microStep * (moveAngle/Nema23constAng)) ; x++){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(100); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100); 
    Serial.print("Steering left!!");
 }
}


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  Serial.begin(9600);
}

void loop() {
  delay(1000); // One second delay
  steerLeft(angle_toMove);
  steerRight(angle_toMove);       //steering back to same position

  delay(1000); // One second delay

  steerRight(angle_toMove);
  steerLeft(angle_toMove);
  delay(1000); // One second delay
  
}
