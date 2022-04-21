// defines pins numbers

//gnd light green
const int stepPin = 8; //dark green  5
const int dirPin = 13; //black  2
const int enPin = 12; //grey   8

#define POTENTIOMETER_PIN A0

//potentiometer values for extremes of steering angle
const float left_extreme = 0; 
const float right_extreme = 803;

int max_angle = 25;    //angle span of steering both sides

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
    float Angle = sin(i * oneDegtoRad);                    //using sin func by converting angles to radian
    float argAngle = map(Angle * 10, -10, 10, -max_angle, max_angle);    // mapping extreme values of sin function to -45/+45 
    steer(argAngle);                                       // steering the wheels to the angle mapped 
    delay(1);

    int pot_val = analogRead(POTENTIOMETER_PIN);
    potCurr_angle = map(pot_val, left_extreme, right_extreme, -max_angle, max_angle);
    Serial.print("\n Current Angle : ");
    Serial.print(potCurr_angle);
    delay(10);

  }

}

