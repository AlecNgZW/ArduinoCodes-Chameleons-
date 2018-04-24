 
#include <Servo.h>


  //these are for the values for the launch and keeping delays 

  //mode variable to hold the different modes of the system 
    String mode="debug"; 
    
    int launchAngle =100;
    int keepAngle =0;

    //mode breakdown:
      //debug (led red)
        //manual (led blue)
          //auto  (led green)

  //state collection for all the devices

  //default all to be off

    bool servoState1 = false;
    bool servoState2 = false;
    bool servoState3 = false;
    bool servoState4 = false;
  
    Servo servo1,servo2,servo3,servo4;


    //to track the run times for the 4 servos


    //calculating the millis() at 2 different intervals of time will return the total elapsed time for the system


    int start1, start2, start3, start4 =0;

    int curr1,curr2,curr3,curr4 =0;

    int elapsed1,elapsed2, elapsed3,elapsed4 =0;


    //set values to handle for the randomization (time range for the randomization algorithm)
    long randLow =10000;
    long randHigh = 60000;



    //variables to store the randomized values in the process of the auto mode


    //random range to be set from 10 seconds to 1 minute
    int randomized1, randomized2, randomized3, randomized4 =0;


    //randNum(1,5) returns a number between 1 and 5
    // 1 second = 1000 millis
    //10 seconds = 10 000 millis
    //1 minute = 60 000 millis

    //if random range to be set for range of the 10 seconds till 1 minute
    //randomization process needs to be for 10 000 to 60 000
    //then compare the elapsed time within the loop to check if the time has arrived to prop the devices down
    


void setup() {
  // put your setup code here, to run once:


  //begin serial monitor
  Serial.begin(9600);

    
  //randomzer seed 
  //analog read on an unconnected pin (0 and 1 are valid targets)
  //randomSeed(analogRead(0));


  //buttons setup here
    //MODE
    pinMode(5,INPUT_PULLUP); //btnManual
    pinMode(A0,INPUT_PULLUP); //btnDebug
    pinMode(A1,INPUT_PULLUP); //btnAuto
  
    //DEVICE
    pinMode(A2,INPUT_PULLUP); //D1
    pinMode(A3,INPUT_PULLUP); //D2
    pinMode(A4,INPUT_PULLUP); //D3
    pinMode(A5,INPUT_PULLUP); //D4
  //end button setup


  //led setup here

   //MODE
    pinMode(2,OUTPUT); //MANUAL
    pinMode(4,OUTPUT); //DEBUG
    pinMode(7,OUTPUT); //AUTO

  //DEVICE
     pinMode(8,OUTPUT); //D1
     pinMode(12,OUTPUT); //D2
     pinMode(13,OUTPUT);  //D3
     pinMode(3,OUTPUT); //D4

  //end led setup

  //servo setup here
  attachAll();
    //todo after phase 1: light testing
   toDefault();
  //end servo setup
 digitalWrite(4,HIGH);
//testLights();
}


  //this method defaults all devices to the original downed positions : servo range 0
void toDefault(){
     
    //to insert and attach servos here
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);
 

   //revertStates to off
     servoState1 =false;
     servoState2 =false;
     servoState3 =false;
     servoState4 =false;
  }


  void killAllLights(){
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(2,LOW);
      
      digitalWrite(8,LOW);
      digitalWrite(12,LOW);
       digitalWrite(13,LOW);
       digitalWrite(3,LOW);

      
    }


    void testLights(){
     
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(2,HIGH);
      
      digitalWrite(8,HIGH);
      digitalWrite(12,HIGH);
       digitalWrite(13,HIGH);
       digitalWrite(3,HIGH);

      
    }




  //this function wiggles the arm to animate the bait
  void wiggleArm(int dev){
      Servo servoToUse;
      int startAngle = 100;
      int endAngle =  80;

     // attachAll();
      switch(dev){
        case 1:
        
          servoToUse = servo1;
         
        //  Serial.println("enters case1");
        
        break;

        case 2:
       
          servoToUse = servo2;
        
        break;

        case 3:
       
          servoToUse = servo3;
          
        break;

        case 4:
        
          servoToUse = servo4;
          
        break;

        default:
        //do nothing
        break;
          
        // wiggle the arm base on the case entered
      }
       
        for(int i=startAngle;i>endAngle;i--){
            //from the start angle wiggle to the end angle and then return
            servoToUse.write(i);
            //ignore delays if there is a device in use
           // if(!servoTriggered()){
            delay(15);
            //}
            //Serial.println("within the first for loop");
          }
          for(int u=endAngle;u<startAngle;u++){
            servoToUse.write(u);
            //ignore delays if there is a device already in use(check servo orientation to see if it is 0)
          //  if(!servoTriggered()){
            delay(15);
            
            //Serial.println("within the second for loop");
            
            }

        //  detachAll();
          
        
        }

  bool servoTriggered(){

      attachAll();
    bool valid =false;
    if(servo1.read()>0|| servo2.read()>0 || servo3.read()>0 || servo4.read()>0)valid=true;
    detachAll();
    return valid;
    
    
    }      

    bool checkServo(int dev){
        bool valid=false;

       attachAll();
        if(dev==1){
            if(servo1.read()>0){
              valid=true;
              }
          }
          if(dev==2){
            if(servo2.read()>0){
              valid=true;
              }
          }    
        if(dev==3){
            if(servo3.read()>0){
              valid=true;
              }
          }
            if(dev==4){
            if(servo4.read()>0){
              valid=true;
              }
          }
        //detach all
       detachAll();
        

          
        return valid;
      }

    
void handleDebug(int dev){
  Serial.println(dev);
  //only run the code when servo in question not triggered
   // if(checkServo(dev)){
      if(dev==1){
        //servo1.attach(6);
         digitalWrite(8,HIGH);
          slowLaunch(dev);
         
          delay(500);
          slowKeep(dev);  
          digitalWrite(8,LOW);
          
        }else if(dev==2){
          //servo2.attach(9);
           digitalWrite(12,HIGH);
          //servo2.write(100);
            slowLaunch(dev);
          delay(500);
          //servo2.write(0);
            slowKeep(dev);
             digitalWrite(12,LOW);
          
          }else if(dev==3){
            //servo3.attach(10);
          //servo3.write(100);
            digitalWrite(13,HIGH);
            slowLaunch(dev);
             
          delay(500);
          //servo3.write(0);
          slowKeep(dev);
             digitalWrite(13,LOW);
          
          }else if(dev==4){
            //servo4.attach(11);
             digitalWrite(3,HIGH);
            slowLaunch(dev);
          //servo4.write(100);
            
          delay(500);
          slowKeep(dev);
          //servo4.write(0);
             digitalWrite(3,LOW);
          }
        //detachAll();
  
  
  
  }
  Servo selectServo(int dev){
      switch(dev){
          case 1:
            return servo1;
            break;
          case 2:
            return servo2;
            break;
          case 3:
            return servo3;
            break;
          case 4:
            return servo4;
            break;
          default:
            return;
            break;
        }
    }

  

  void slowLaunch(int dev){
      
      //get the servo to use
      Servo servoToUse = selectServo(dev);

      //base on the servo do a slow write to 100

      for(int i=keepAngle; i<launchAngle;i++){

        servoToUse.write(i);
        delay(7);
        
        }
      
    
    
    
    }
    //requirements before this method is run, servo in question must already be attached
    void slowKeep(int dev){
            //get the servo to use
      Servo servoToUse = selectServo(dev);

      //base on the servo do a slow write to 100

      for(int i=launchAngle; i>keepAngle;i--){

        servoToUse.write(i);
        delay(7);
        
        } 
      }

//this method is used to reset all the randomization values, elapsed start and curr
void resetValues(){
      randomized1 =0;
      randomized2 =0;
      randomized3 =0;
      randomized4 =0;

      curr1 = 0;
      curr2 =0;
      curr3=0;
      curr4=0;

      elapsed1=0;
      elapsed2=0;
      elapsed3=0;
      elapsed4=0;

  
  }




void handleManual(int dev){

    //check the device state
    
    if(dev==1){
        
        if(servoState1==false){
            servoState1=true;
            //servo1.write(100);
               digitalWrite(8,HIGH);
              slowLaunch(dev);
               
            
          }else{
              servoState1=false;
              //servo1.write(0);
              slowKeep(dev);
              
               digitalWrite(8,LOW);
                
            }

     
      }else if(dev==2){
      
        
         if(servoState2==false){
            servoState2=true;
           // servo2.write(100);
            digitalWrite(12,HIGH);
                slowLaunch(dev);
              
          }else{
              servoState2=false;
              //servo2.write(0);
                   slowKeep(dev);
                 digitalWrite(12,LOW);
                   
            }
     
        }else if(dev==3){
          
    
         if(servoState3==false){
            servoState3=true;
            //servo3.write(100);
             digitalWrite(13,HIGH);
                 slowLaunch(dev);
              
          }else{
              servoState3=false;
              //servo3.write(0);
                   slowKeep(dev);
                 digitalWrite(13,LOW);
               
            }
       
        }else if(dev==4){
        
       
         if(servoState4==false){
            servoState4=true;
            //servo4.write(100);
             digitalWrite(3,HIGH);
                 slowLaunch(dev);
              
          }else{
              servoState4=false;
              //servo4.write(0);
                  slowKeep(dev);
               digitalWrite(3,LOW);
                 
            }
       
        }
     
  
  
  }
  
  
  //UTILITY: attachment of all servos
  void attachAll(){
    
      servo1.attach(6);
      servo2.attach(9);
      servo3.attach(10);
      servo4.attach(11);
      
    }

    //UTILITY: detachment of all servos
  void detachAll(){
      servo1.detach();
      servo2.detach();
      servo3.detach();
      servo4.detach();
    
    }




void loop() {
  // put your main code here, to run repeatedly:
 
    int modeManual= digitalRead(5);
    int modeDebug =digitalRead(A0);
    int modeAuto = digitalRead(A1);
    

    int dev1 = digitalRead(A2);
    int dev2 = digitalRead(A3);
    int dev3 =digitalRead(A4);
    int dev4 = digitalRead(A5);




//MODE SELECTION

//prevent mode change when in debug mode and servo is triggered
 // if((mode.equals("debug") && servoTriggered())){}else{
    if(modeManual ==LOW){
        Serial.println("enters M");
        killAllLights();


        resetValues();
         toDefault();
        mode ="manual";
        digitalWrite(2,HIGH);

       
      }

         if(modeDebug ==LOW){
        Serial.println("enters D");
        killAllLights();
        
        //show and fade away all lights
        testLights();
        delay(500);
        killAllLights();
        //end fade away of the lights
        resetValues();
       toDefault();
       
        mode ="debug";
        //on debug light
        digitalWrite(4,HIGH);
      }

          if(modeAuto ==LOW){
        Serial.println("enters A");
        killAllLights();
        toDefault();
        resetValues();
        //setManualLight on
        mode ="auto";
        digitalWrite(7,HIGH);
      }
//  }

  //END MODE SELECTION

//DEBUG FUNCTIONALITY

  if(mode.equals("debug")){
  
      if(dev1==LOW){
        handleDebug(1);
        }else if(dev2==LOW){
          handleDebug(2);
          
          }else if(dev3==LOW){
            handleDebug(3);
            
            }else if(dev4==LOW){
              handleDebug(4);
              }
    }


//DEBUG FUNCTION

    if(mode.equals("manual")){
      if(dev1==LOW){
        //check the print speed of the button to see if it is slow or  fast after triggering and check the allowed acceptance of the button input
        //Serial.println("dev1 pressed");
      
        handleManual(1);
          delay(250);

        
        }else if(dev2==LOW){
          handleManual(2);
             delay(250);
          
          }else if(dev3==LOW){
            handleManual(3);
            delay(250);
            
            }else if(dev4==LOW){
              handleManual(4);
                 delay(250);
              }

      //handle the wiggle motions of the active servos (if the bug is up run the wiggleArm code for the specific servo)
        
        //if state is true then the device is active
        if(servoState1){
           
            //if the device is active then we trigger the arm to do a wiggle motion    
              wiggleArm(1);
        }
             
          
          if(servoState2){

            
        
              wiggleArm(2);
              
              
            
            }
            if(servoState3){
         
              wiggleArm(3);
              
              
              }
              if (servoState4){
               
              wiggleArm(4);
              
              
                }




      
      }//END MANUAL

//AUTO MODE
      if(mode.equals("auto")){

          //to check the current time for the devices 1,2,3,4
          //check if they are initially 0 to not replace the values everytime it enters the auto mode segment
          //only set the initialized current time whenever all 4 values are 0
     
          if(start1 ==0){
            start1 =millis();
            }
            if(start2 == 0){
              start2 =millis();
              
              }
              if(start3 ==0){
                start3 = millis();
                
                }
                if(start4 ==0){
                    start4 = millis();
                  }
        
          //handle auto mode logic

          //check if the device is active if active run an elapsed timer and check against a random timing range and then prop the target down

          //returns true if the device is active
         
          
          //handle timing randomization
          if(randomized1==0){
            //if the timing is not yet established to randomize a timing between 10000 and 60000
                randomSeed(micros());
              randomized1 = random(randLow,randHigh);


              Serial.println(abs(randomized1));
            
            }
            if(randomized2==0){
                randomSeed(micros());
               randomized2 = random(randLow,randHigh); 

              Serial.println(abs(randomized2));
              
              
              }
              if(randomized3 ==0){
                 randomSeed(micros());
                 
                randomized3 = random(randLow , randHigh);
                
                }

                if(randomized4 ==0){
              randomSeed(micros());
                  randomized4 = random(randLow, randHigh);
                  
                  
                  }
                //end time randomization
          
          //IF DEVICE INACTIVE, check the timing in this segment and compare to randomized
          if(servoState1==false){
              //the device is inactive
              //  Servo servoToUse= selectServo(1);

                //check the current time
                  // compare 

                  curr1 = millis();

                  elapsed1 = curr1-start1;

                  //check the value to see if elapsed past the randomized value
                  if(elapsed1 > abs(randomized1)){
                    //prop and run slow start code 
                      
                      handleManual(1);

                      //reset the start to be this time after it starts

                      start1 = millis();
                      
                    }
          }else{
           
              // to insert code logic for handling keeping the device
                curr1 = millis();
                elapsed1 = curr1 - start1;
                if(elapsed1>abs(randomized1)){
                    handleManual(1);

                    //new randomized value would be reassigned in the auto segment of the loop
                    randomized1 =0;
                    //reset the starting time to be the current time when the device is offed
                    //when it cycles into the auto segment of the loop new start time would be assigned
                    start1 = 0;
                  } 


            
            }

              //device 2

             if(servoState2==false){
              //the device is inactive
              //  Servo servoToUse= selectServo(1);

                //check the current time
                  // compare 

                  curr2 = millis();

                  elapsed2 = curr2-start2;

                  //check the value to see if elapsed past the randomized value
                  if(elapsed2 > abs(randomized2)){
                    //prop and run slow start code 
                      
                      handleManual(2);

                      //reset the start to be this time after it starts

                      start2 = millis();
                      
                    }
          }else{
           
              // to insert code logic for handling keeping the device
                curr2 = millis();
                elapsed2 = curr2 - start2;
                if(elapsed2>abs(randomized2)){
                    handleManual(2);

                    //new randomized value would be reassigned in the auto segment of the loop
                    randomized2 =0;
                    //reset the starting time to be the current time when the device is offed
                    //when it cycles into the auto segment of the loop new start time would be assigned
                    start2 = 0;
                  } 
            
            }
          

               //device 3

               if(servoState3==false){
              //the device is inactive
              //  Servo servoToUse= selectServo(1);

                //check the current time
                  // compare 

                  curr3 = millis();

                  elapsed3 = curr3-start3;

                  //check the value to see if elapsed past the randomized value
                  if(elapsed3 > abs(randomized3)){
                    //prop and run slow start code 
                      
                      handleManual(3);

                      //reset the start to be this time after it starts

                      start3 = millis();
                      
                    }
          }else{
           
              // to insert code logic for handling keeping the device
                curr3 = millis();
                elapsed3 = curr3 - start3;
                if(elapsed3>abs(randomized3)){
                    handleManual(3);

                    //new randomized value would be reassigned in the auto segment of the loop
                    randomized3 =0;
                    //reset the starting time to be the current time when the device is offed
                    //when it cycles into the auto segment of the loop new start time would be assigned
                    start3 = 0;
                  } 
            
            }

                //device 4
        
                 if(servoState4==false){
              //the device is inactive
              //  Servo servoToUse= selectServo(1);

                //check the current time
                  // compare 

                  curr4 = millis();

                  elapsed4 = curr4-start4;

                  //check the value to see if elapsed past the randomized value
                  if(elapsed4 > abs(randomized4)){
                    //prop and run slow start code 
                      
                      handleManual(4);

                      //reset the start to be this time after it starts

                      start4 = millis();
                      
                    }
          }else{
           
              // to insert code logic for handling keeping the device
                curr4 = millis();
                elapsed4 = curr4 - start4;
                if(elapsed4>abs(randomized4)){
                    handleManual(4);

                    //new randomized value would be reassigned in the auto segment of the loop
                    randomized4 =0;
                    //reset the starting time to be the current time when the device is offed
                    //when it cycles into the auto segment of the loop new start time would be assigned
                    start4 = 0;
                  } 
            
            }
        
          //handle wiggling


          
      //handle the wiggle motions of the active servos (if the bug is up run the wiggleArm code for the specific servo)
        
        //if state is true then the device is active
       //if state is true then the device is active
        if(servoState1){
           
            //if the device is active then we trigger the arm to do a wiggle motion    
              wiggleArm(1);
        }
             
          
          if(servoState2){

            
        
              wiggleArm(2);
              
              
            
            }
            if(servoState3){
         
              wiggleArm(3);
              
              
              }
              if (servoState4){
               
              wiggleArm(4);
              
              
                }


        }
        //END AUTO

      
  
  //overall delay will slow down the system and evidently make the button controls insensitive
  //provide a delay reduction when the system checks that there is a servo active
  //offset the 15 delay
 
  delay(150);
  

}
s
