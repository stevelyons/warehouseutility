/*
  WarehouseUtility 
  @description: turn OWI Robot arm into an additional hand for any operation

  
 
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// Setup Motor 

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


#define TURNING_SPEED 20

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motorOne = AFMS.getMotor(1);
Adafruit_DCMotor *motorTwo = AFMS.getMotor(2);
Adafruit_DCMotor *motorThree = AFMS.getMotor(3);
Adafruit_DCMotor *motorFour = AFMS.getMotor(4);

int sensor0 = A0; // variable to store the Arm 1 sensor 
int sensor1 = A1; // variable to store the Arm 2 sensor 
int sensor2 = A2; // variable to store the Arm 3 sensor 
int sensor3 = A3; // variable to store the Arm 4 sensor 


// openclaw
void openClaw()
{
  motorOne->setSpeed(TURNING_SPEED + 30);
  motorOne->run(BACKWARD);
  delay(1000); 
}

void closeClaw()
{
  motorOne->setSpeed(TURNING_SPEED + 30);
  motorOne->run(FORWARD);
  delay(1000);
}

void turnLeft()
{
  
  
}

void turnRight()
{
  
  
}

void turnUpControl()
{
  motorOne->setSpeed(TURNING_SPEED);
 motorOne->run(FORWARD);
 delay(1000);
  motorOne->run(FORWARD);
 delay(1000);
motorOne->run(FORWARD);
 delay(1000);
  motorOne->run(FORWARD);
 delay(1000);
 
  motorOne->run(BACKWARD);
 delay(1000);
  motorOne->run(BACKWARD);
 delay(1000);

}

void turnUp()
{

}

void turnDown()
{
 motorOne->setSpeed(TURNING_SPEED + 30);
 motorOne->run(BACKWARD);
 delay(1000);
}

void neckUp()
{
 motorTwo->setSpeed(TURNING_SPEED + 30);
 motorTwo->run(FORWARD);
 delay(1000);
  
}

void neckDown()
{
  motorTwo->setSpeed(TURNING_SPEED + 30);
  motorTwo->run(BACKWARD);
 delay(1000);
}

void bodyUp()
{
 motorThree->setSpeed(TURNING_SPEED + 30);
 motorThree->run(BACKWARD);
 delay(1000);
  
}

void bodyDown()
{
  motorThree->setSpeed(TURNING_SPEED + 30);
  motorThree->run(FORWARD);
 delay(1000);
}

void ExtendUp()
{
 motorFour->setSpeed(TURNING_SPEED + 30);
 motorFour->run(BACKWARD);
 delay(1000);
  
}

void ExtendDown()
{
  motorFour->setSpeed(TURNING_SPEED + 30);
  motorFour->run(FORWARD);
 delay(1000);
}


void demoSequenceOne()
{
   bodyDown();
   bodyDown();
   closeClaw();
   closeClaw();

   neckDown();
   neckUp();
   
   bodyUp();
   bodyUp();  
   openClaw();

}


byte byteRead;

/*
 Intialize the motors' speeds 
*/
void setup() 
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Robot arm test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  motorOne->setSpeed(0);     // set the speed to 100/255
  motorTwo->setSpeed(0);     // do the same for the others...
  motorThree->setSpeed(0);    
  motorFour->setSpeed(0);
   // turn on motor
  motorOne->run(RELEASE);
  motorTwo->run(RELEASE);
  motorThree->run(RELEASE);
  motorFour->run(RELEASE);
}

void loop()
{
  //start:

   // Start by displaying all the current sensor values
  //Serial.println("Start!");

  /*
  int potValueOne = analogRead(sensor0);
  int potValueTwo = analogRead(sensor1);
  int potValueThree = analogRead(sensor2);
  int potValueFour = analogRead(sensor3);

  // set intial values
  int pvoInital = potValueOne;
  int pvtInital = potValueTwo;
  int pvthreeInitial =  potValueThree;
  int pvfInitial = potValueFour;
  */
  
  //Serial.print("1 = ");

  //Serial.println(potValueOne);
  /*
   Serial.print("2 = ");
  Serial.println(potValueTwo);
   Serial.print("3 = ");
  Serial.println(potValueThree);
   Serial.print("4 = ");
  Serial.println(potValueFour);
  */
  delay(100);        // delay in between reads for stability


// sensor will not work, must use timer

if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    //Serial.write(byteRead);
    switch(byteRead)
    {
      case 'a':
        Serial.println("Left");
        break;
      case 'd':
        Serial.println("Right");
        break;
      case 'w':
        neckDown();
        Serial.println("Up");
        break;
      case 's':
        neckUp();
        Serial.println("Down");
        break;
      case 'z':
        Serial.println("Claw Close");
        closeClaw();
        break;
      case 'x':
        Serial.println("Claw Open");
        openClaw();
        break;

         case 'i':
        Serial.println("Body Up");
        bodyUp();
        break;
      case 'k':
        Serial.println("Body Down");
        bodyDown();
        break;

       case 'j':
        Serial.println("Extend Up");
        bodyUp();
        break;
      case 'l':
        Serial.println("Extend ]Down");
        bodyDown();
        break;
      case 'h':
        Serial.println("Demo Start");
        demoSequenceOne();
        break;
      
        
      default:
        Serial.println("Bad choice");
      break;
        
     
    }
  }

/*

  motorOne->setSpeed(TURNING_SPEED);     // set the speed to 100/255
  motorOne->run(FORWARD);

  // keep m1 from going past a certian degree
  if(potValueOne >50)
  {
     Serial.println("Motor 1 was stopped");
    // stop 
    motorOne->setSpeed(0);
    delay(1000);

    // return back 
    Serial.println("Motor 1 is going back ");
    motorOne->run(BACKWARD);
    motorOne->setSpeed(50); 
  } else if (potValueOne < 0)
  {
    Serial.println("Motor 1 went too far back ");
    motorOne->setSpeed(0);
    delay(1000);
    // go forward
     motorOne->run(FORWARD);
     motorOne->setSpeed(TURNING_SPEED); 
    
    }
    */
  /*
  else if (potValueOne <= pvoInital)
  {
   // stop 
      motorFour->setSpeed(50);

    // return back 
    motorOne->run(FORWARD);
     motorOne->setSpeed(0); 
  }*/

  










  //delay (1000);
  motorOne->setSpeed(0);       // turn off motors
  motorTwo->setSpeed(0);   
  motorThree->setSpeed(0);    
  motorFour->setSpeed(0);

  //goto start;

/*
  int potValueTwo = analogRead(sensor1);
  Serial.println(potValueTwo);
  delay(100);        // delay in between reads for stability

  
  int potValueThree = analogRead(sensor2);
  Serial.println(potValueThree);
  delay(100);        // delay in between reads for stability
  

/*
  int potValueFour = analogRead(sensor3);
  Serial.println(potValueFour);
  delay(100);        // delay in between reads for stability
*/

  
/*
  Serial.println(sensor1);
  delay(1);        // delay in between reads for stability

  Serial.println(sensor2);
  delay(1);        // delay in between reads for stability

  Serial.println(sensor3);
  delay(1);        // delay in between reads for stability
  */
}



/*
void input()
{
  int incomingByte = 0;
  motorOne->setSpeed(0);     // stop the motor
  Serial.println("Hit return for next motion");   
  while (incomingByte != 13)  // 13 is the ASCII code for "enter"
    {
  if (Serial.available() > 0) 
         {   
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
   }
     }
  }
 
  void setup() 
  {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Robot arm test!");
  motorOne->setSpeed(10);     // set the speed to 100/255
  motorTwo->setSpeed(10);     // do the same for the others...
  motorThree->setSpeed(10);    
  motorFour->setSpeed(10);
}
    
void loop()

  {
  start:
  
  // Start by displaying all the current sensor values
  Serial.println("Start!");
  sensor0 = analogRead(0);    // read the input pin 0
  sensor1 = analogRead(1);    // read the input pin 0
  sensor2 = analogRead(2);    // read the input pin 0
  sensor3 = analogRead(3);    // read the input pin 0
        
  Serial.print("1 = ");
  Serial.print(sensor0);             // debug value
  Serial.print("  2 = ");
  Serial.print(sensor1);             // debug value
  Serial.print("  3 = ");
  Serial.print(sensor2);             // debug value
  Serial.print("  4 = ");
  Serial.println(sensor3);             // debug value
  delay(100);
  
 if (sensor0 > 500)          // If base is not at end, move to end
  {
    while (sensor0 > 500)
     {
      sensor0 = analogRead(0);    // read the input pin 0
      Serial.print("Value = ");
      Serial.println(sensor0);             // debug value
      motorOne->setSpeed(100);     // set the speed to 100/255
      motorOne->run(FORWARD);
      delay(100);
     }
  }
  
  input();  // wait for user to hit return
  
  
  // Now we're going to move all the motors forward a bit so we can see how the motor direction and sensor direction correlate
  
  motorOne->setSpeed(100);     // set the speed to 100/255
  motorOne->run(FORWARD);
  motorTwo->setSpeed(100);     // set the speed to 100/255
  motorTwo->run(FORWARD);
  motorThree->setSpeed(100);     // set the speed to 100/255
  motorThree->run(FORWARD);
  motorFour->setSpeed(100);     // set the speed to 100/255
  motorFour->run(FORWARD);
  delay (1000);
  motorOne->setSpeed(0);       // turn off motors
  motorTwo->setSpeed(0);   
  motorThree->setSpeed(0);    
  motorFour->setSpeed(0);   
  
  // Now read the sensors to see how they changed

  sensor0 = analogRead(0);    // read the input pin 0
  sensor1 = analogRead(1);    // read the input pin 1
  sensor2 = analogRead(2);    // read the input pin 2
  sensor3 = analogRead(3);    // read the input pin 3
        
  Serial.print("1 = ");    // report the new readings
  Serial.print(sensor0);             
  Serial.print("  2 = ");
  Serial.print(sensor1);             
  Serial.print("  3 = ");
  Serial.print(sensor2);            
  Serial.print("  4 = ");
  Serial.println(sensor3);          
  delay(100);

  input();  // wait for user to hit return
  
    // Now we're going to move all the motors back to where they started
  
  motorOne->setSpeed(100);     // set the speed to 100/255
  motorOne->run(BACKWARD);
  motorTwo->setSpeed(100);     // set the speed to 100/255
  motorTwo->run(BACKWARD);
  motorThree->setSpeed(100);     // set the speed to 100/255
  motorThree->run(BACKWARD);
  motorFour->setSpeed(100);     // set the speed to 100/255
  motorFour->run(BACKWARD);
  delay (1000);
  motorOne->setSpeed(0);       // turn off motors
  motorTwo->setSpeed(0);   
  motorThree->setSpeed(0);    
  motorFour->setSpeed(0);   
  
  // Now read the sensors to see how they changed

  sensor0 = analogRead(0);    // read the input pin 0
  sensor1 = analogRead(1);    // read the input pin 1
  sensor2 = analogRead(2);    // read the input pin 2
  sensor3 = analogRead(3);    // read the input pin 3
        
  Serial.print("1 = ");    // report the new readings
  Serial.print(sensor0);             
  Serial.print("  2 = ");
  Serial.print(sensor1);             
  Serial.print("  3 = ");
  Serial.print(sensor2);            
  Serial.print("  4 = ");
  Serial.println(sensor3);          
  delay(100);

  input();  // wait for user to hit return

  goto start;
  }
*/

