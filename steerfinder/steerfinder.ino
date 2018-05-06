#include <Wire.h>

  // Use this code to print sensor counts & steer angle to monitor & setup steering for 4WS or Accusteer.
  //first get & record sensor data, calculate steeringPosition2 to match steeringPosition, change map(steeringPosition2.....) values to correct for machine.
  
 //steering variables
  int numsteersensor = 1;    // 4WS or Case stx accusteer = 2, normal 2WS or Artic = 1
  float steerAngleActual = 0;
  int steerPrevSign = 0, steerCurrentSign = 0; // the steering wheels angle currently and previous one
  float steerAngleSetPoint = 0; //the desired angle from AgOpen
  int steeringPosition = 0, steeringPositionZero = 543; //from steering sensor, set in AOG
  int steeringPosition2 = 0; //steeringPositionZero2 = 544; //from other steering sensor, **** set posZero here
  int steer2 = 0; // corrected steer position
  float steerAngleError = 0; //setpoint - actual
  float distanceError = 0; //
  float steerSensorCounts = 16;  // set counts per degree here for pot1
  //float steerSensorCounts2 = 20; //  set counts per degree here  for pot2


void setup() {
  // put your setup code here, to run once:

  Serial.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:

if (numsteersensor = 1)
  {
    analogRead(A0); //discard initial reading
    steeringPosition = analogRead(A0); delay(4);
    steeringPosition += analogRead(A0); delay(4);
    steeringPosition += analogRead(A0); delay(4);
    steeringPosition += analogRead(A0);

    steeringPosition = steeringPosition >> 2; //divide by 4
    steeringPosition = ( steeringPosition - steeringPositionZero);   //read the No1 steering position sensor

    //convert position to steer angle. 6 counts per degree of steer pot position in my case 
    //  ***** make sure that negative steer angle makes a left turn and positive value is a right turn *****
    // remove or add the minus for steerSensorCounts to do that.
    steerAngleActual = (float)(steeringPosition/-steerSensorCounts);    // 2 wheel steer or artic

    Serial.print(steeringPosition);
    Serial.print("- pot reading,   ");    
    Serial.print(steerAngleActual); //The actual steering angle in degrees
    Serial.println("-steer angle");   
    Serial.flush();

 
  }
  
else if (numsteersensor = 2)
{
    //steering position and steer angle specific for 4WS and Case accusteer tractor, for 2WS comment out all references to steeringPosition2
    analogRead(A0); //discard initial reading
    analogRead(A2); //discard initial reading
    steeringPosition = analogRead(A0);
    steeringPosition2 = analogRead(A2);
    delay(2);
    steeringPosition += analogRead(A0);
    steeringPosition2 += analogRead(A2);
    delay(2);
    steeringPosition += analogRead(A0);
    steeringPosition2 += analogRead(A2);
    delay(2);
    steeringPosition += analogRead(A0);
    steeringPosition2 += analogRead(A2); 
       
    steeringPosition = steeringPosition >> 2; //divide by 4 
    steeringPosition2 = steeringPosition2 >> 2; //divide by 4

    steer2 = map(steeringPosition2,313,773,433,653); //map front sensor to match steerposition sensor counts/degree

    steeringPosition = ( steeringPosition - steeringPositionZero);   //read the No1 steering position
    steer2 = (steer2 - steeringPositionZero);   //read the No2 steering position

    
    //convert position to steer angle. 6 counts per degree of steer pot position in my case 
    //  ***** make sure that negative steer angle makes a left turn and positive value is a right turn *****
    // remove or add the minus for steerSensorCounts to do that.
    steerAngleActual = (float)((steeringPosition/-steerSensorCounts)+(steer2/steerSensorCounts)); // 4 wheel steer or Case STX Accusteer
    
   

    Serial.print(steeringPosition);
    Serial.print("- pot1,   ");    
    Serial.print(steeringPosition2);
    Serial.print("- pot2,   ");
    Serial.print(steerAngleActual); //The actual steering angle in degrees
    Serial.println("-steer angle");   
    Serial.flush(); 
}
else
{   Serial.println(" error number steer sensors, set in steering variables");
    delay(5000);
}   
   delay(100);
}   


