// defines pins numbers
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;


// +ve for right and -ve for left side in angles 
float curr_angle = 0; // current steer state of wheels 
float target_angle = 0;  // target angle to achieve by steering the wheels (Publishes by ros topics)

// for conversion from deg to radians
const float Pi = 3.14159;    
const float oneDegtoRad = Pi/180;


// some important constants for running the Stepper Motor
const float Nema23constAng = 0.9;        //0.9 degrees step 
const int microStep = 8;                 //from microstep driver settings


void steer(int target_angle){
  float steerAngle = target_angle - curr_angle; // difference of the current and target angle that needs to be executed. 
  
  if (steerAngle >= 0){
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction (Right)
  }
  else if (steerAngle < 0) {
    digitalWrite(dirPin, LOW); // (Left)
    steerAngle = -steerAngle;
  }
    
  for(int x = 0; x < (microStep * (steerAngle/Nema23constAng)) ; x++){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(800); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(800); 
 }
 curr_angle = target_angle; //setting the current angle to the Angle just steered...
 Serial.println(curr_angle); 
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
  
  for(int i = 0; i <= 360; i++){
    float Angle = sin(i * oneDegtoRad);                        //using sin func by converting angles to radian
    float argAngle = map(Angle * 10, -10, 10, -30, 30);    // mapping extreme values of sin function to -45/+45 
    steer(argAngle);                                           // steering the wheels to the angle mapped 
                                   //printing current angle of wheels to Plotter/Monitor
    delay(1);

  }

}
