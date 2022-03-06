// defines pins numbers
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;

float val = 0;

//const float Pi = 3.14159; 
//const float oneDegtoRad = Pi/180;

const int angle_toMove = 30;
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
    Serial.print("Steering Right!! \n");
    Serial.println(val);
    val++;
 }
}

void steerLeft(int moveAngle){
  //Left
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction

  for(int y = 0; y < (microStep * (moveAngle/Nema23constAng)) ; y++){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(10); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(10); 
    Serial.print("Steering left!! \n");
    Serial.println(val);
    val--;
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
  steerLeft(angle_toMove);
  steerRight(angle_toMove);       //steering back to same position
  delay(10); // One second delay
  steerRight(angle_toMove);
  steerLeft(angle_toMove);
  delay(1000); // One second delay
  
}
