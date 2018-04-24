#include <Servo.h>

 String mode="debug"; 

 //the settlement of the dynamic branches

 //to create method for the sideways motion

 //to create method for the frontback motion

//MOVEMENT RANGE FOR THE SPECIFIC DEVICES

//Front motion
int dev1LowerLimit =10;
int dev1HigherLimit=60;


//sideways motion
int dev2LowerLimit =10;
int dev2HigherLimit=70;
 

bool servoState1 =false;
bool servoState2 =false;


bool isMobile1= false;
bool isMobile2 = false;


//require the current positions of the 2 devices at all time to know where the device actually is

Servo servo1,servo2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //buttons setup here
    //MODE
    pinMode(5,INPUT_PULLUP); //btnManual
    pinMode(A0,INPUT_PULLUP); //btnDebug
    pinMode(A1,INPUT_PULLUP); //btnAuto
  
    //DEVICE 1
    pinMode(A2,INPUT_PULLUP); //D1
    pinMode(A3,INPUT_PULLUP); //D2
    
    //DEVICE 2
    pinMode(A4,INPUT_PULLUP); //D3
    pinMode(A5,INPUT_PULLUP); //D4


  //end button setup


  //led setup
   //MODE
    pinMode(2,OUTPUT); //MANUAL
    pinMode(4,OUTPUT); //DEBUG
    pinMode(7,OUTPUT); //AUTO

  //DEVICE1
     pinMode(8,OUTPUT); //D1
     pinMode(12,OUTPUT); //D2

     //DEVICE 2
     pinMode(13,OUTPUT);  //D3
     pinMode(3,OUTPUT); //D4

  //end led setup

  //servo setup
   servo1.attach(9);
    servo2.attach(10);



    //check if it is required to calculate a start point for the dynamic branches
//  dev1CalculatedStart = (dev1HigherLimit+dev1LowerLimit)/2;
//  dev2CalculatedStart =(dev2HigherLimit+dev2LowerLimit)/2;
    


    // to determine what servo range to write intot he system
      //write to the lowest limit 
      servo1.write(dev1LowerLimit);
    servo2.write(dev2LowerLimit);
    //end servo setup

      servo1.detach();
      servo2.detach();
    
    //set up the debug lights
     digitalWrite(4,HIGH);


//Serial.println("Code is running");

     
}

//START UTILITY METHODS
void timeSensitiveDetach(){
  if(servo1.attached()){
    servo1.detach();
    
    }
    if(servo2.attached()){
      servo2.detach();
      
      }
  }



//method to switch off all the lights
  void killAllLights(){
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(2,LOW);
      
      digitalWrite(8,LOW);
      digitalWrite(12,LOW);
       digitalWrite(13,LOW);
       digitalWrite(3,LOW);

      
    }

    //method to test all the lights

    
    void testLights(){
     
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(2,HIGH);
      
      digitalWrite(8,HIGH);
      digitalWrite(12,HIGH);
       digitalWrite(13,HIGH);
       digitalWrite(3,HIGH);

      
    }

//to check in the current system if anything is currently in movement
  bool servoTriggered(){
      
    bool valid =false;
//    if(servo1.read()>0|| servo2.read()>0 || servo3.read()>0 || servo4.read()>0)valid=true;

    
    if(servo1.read()>0||servo2.read()>0)valid=true;

    return valid;
    
    
    }      

  //to check if specific device is currently functioning
    bool checkServo(int dev){
        bool valid=false;
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
//        if(dev==3){
//            if(servo3.read()>0){
//              valid=true;
//              }
//          }
//            if(dev==4){
//            if(servo4.read()>0){
//              valid=true;
//              }
//          }
        return valid;
      }

      //END UTILITY METHODS

//handle debug functionality for the dynamic branches

void handleDebug(int dev){

    
  //sweep motion to test the full servo
    if(dev==1){
      //if the device is 1 use first servo
      //cradle to device left to right
      servo1.attach(9);
      //int i = dev1LowerLimit;
      for(int i = dev1LowerLimit;i<dev1HigherLimit;i++){
      servo1.write(i);
      
      delay(15);
      }
      //inverse the direction
      
      for(int u=dev1HigherLimit;u>dev1LowerLimit;u--){
        servo1.write(u);
        delay(15);
        }
        servo1.detach();
      }
       if(dev==2){
        //rocks to
        //int i= dev2LowerLimit;
        servo2.attach(10);
        for(int i= dev2LowerLimit;i<dev2HigherLimit;i++){
          servo2.write(i);
          delay(15);
          }
          //rocks fro
        for(int  u= dev2HigherLimit;u>dev2LowerLimit;u--){
          servo2.write(u);
          delay(15);
          }
          servo2.detach();
        
      }
  
  
  
  }

  void handleAuto(int dev){
      //based on the device number toggle the device to be rocking constantly or switch off the state of the system to go back to rest stop at lower limits

      if(dev==1){

        //check the servoState of the device to see if it is currently running
        //device not functional switch it on
        if(servoState1 ==false){
            //switch the device light on and switch the state of the system to true

            servoState1 = true;

            //led setup
            digitalWrite(8,HIGH);
            digitalWrite(12,HIGH);

          
          
          }else{
              servoState1= false;

              //rest the servo if it is not at minimal range
            if(!servo1.attached()){
            servo1.attach(9);
            }
              //if device not at lowest limit
              if(servo1.read()>dev1LowerLimit){
                //bring device to rest
                for(int i = servo1.read();i> dev1LowerLimit;i--){

                  servo1.write(i);
                  delay(15);
                  }

                       
           
                      }
                         //led setup
                  digitalWrite(8,LOW);
                  digitalWrite(12,LOW); 
                  servo1.detach();
            
            }

        
        
        
        }else if(dev==2){
          
                //check the servoState of the device to see if it is currently running
        //device not functional switch it on
        if(servoState2 ==false){
            //switch the device light on and switch the state of the system to true

            servoState2 = true;

            //led setup
            digitalWrite(13,HIGH);
            digitalWrite(3,HIGH);

          
          
          }else{
              servoState2= false;
              Serial.println("attempting shut off");
              

              //rest the servo if it is not at minimal range
            if(!servo2.attached()){
            servo2.attach(10);
            }
            //if device not at lowest limit
              if(servo2.read()>dev2LowerLimit){
                //bring device to rest
                for(int i = servo2.read();i> dev2LowerLimit;i--){

                  servo2.write(i);
                  delay(15);
                  }

                      
                      }
                         //led setup
                  digitalWrite(13,LOW);
                  digitalWrite(3,LOW);
                servo2.detach();
            
            
            
            }

        
          
          
          
          }


    
    
    }


//btn defines the button that is pressed, 1 or 2
//dev defines which device it is for
  void rockDevice(int dev,int btn){
      Servo servoToUse;
      int lowerLimit =0;
      int higherLimit=0;
      
    if(dev==1){
      
      servoToUse =servo1;
      lowerLimit = dev1LowerLimit;
      higherLimit = dev1HigherLimit;

      isMobile1 = true;
      servo1.attach(9);
    }else{
      servoToUse= servo2;
      lowerLimit = dev2LowerLimit;
      higherLimit =dev2HigherLimit;

      isMobile2=true;
      servo2.attach(10);
      }
        //check which button was used
        if(btn==1){

         
          //button left for the first device
          int i=servoToUse.read();
         // isMobile1 =true;
            for(i;i< higherLimit;i++){
            servoToUse.write(i);
            delay(15);
            }
         
          
          }else if(btn==2){
            //servo1.attach(9);
          //button right for the second device
          int i = servoToUse.read();
          //isMobile2 = true;
          for(i;i>lowerLimit;i--){
            servoToUse.write(i);
            delay(15);
            }
            
          }
          //isMobile2=false;

          //after everything is done change the isMobile state to default
          if(dev==1){
            isMobile1 = false;
            servo1.detach();
            }else{
              isMobile2 = false;
              servo2.detach();
              
              }
                
    }



//to default the mode switch
    void toDefault(){


      //this method will be called as long as it is within the mode switch , in the mode switch i want to ensure that all servoStates default

      servoState1 = false;
      servoState2 =false;

      //default the servo positions

      servo1.attach(9);
      servo2.attach(10);

      //check the values

      if(servo1.read()> dev1LowerLimit){
          for(int i= servo1.read(); i> dev1LowerLimit;i--){
            servo1.write(i);
            delay(15);
            
            }
        
        }
        if(servo2.read()> dev2LowerLimit){
          for(int i= servo2.read(); i>dev2LowerLimit;i--){
              servo2.write(i);
              delay(15);
            
            }
          
          }

        //clean up
        servo1.detach();
        servo2.detach();
      
      
      }


      void handleAutoSweep(int dev){
          int lowerLimit =0;
          int higherLimit =0;
          Servo servoToUse;
          
          if(dev==1){
            
            lowerLimit = dev1LowerLimit;
            higherLimit = dev1HigherLimit;
            servo1.attach(9);
            servoToUse = servo1;            
            
            }else if(dev==2){
              
              lowerLimit = dev2LowerLimit;
              higherLimit = dev2HigherLimit;
              servo2.attach(10);
              servoToUse = servo2;
              
              
              }

              //SWEEP -to
              for(int i= lowerLimit;i< higherLimit;i++){
                servoToUse.write(i);
                delay(15);
                
                }
                //SWEEP -fro
                for(int  u= servoToUse.read();u>lowerLimit;u--){
                  servoToUse.write(u);
                  delay(15);
                  }

              

              //CLEAN UP
              servoToUse.detach();
              
        
        
        }





void loop() {

      // retrieve all the button values but invert the values for the manual and auto lights
        //or rather dont invert the code logic but invert the wiring should be easier to do and less complication involvement
 int modeManual= digitalRead(5);
    int modeDebug =digitalRead(A0);
    int modeAuto = digitalRead(A1);
    
  //controls for the first device
    int dev1Left = digitalRead(A2);
    int dev1Right = digitalRead(A3);


  //controls for the second device  
    int dev2Left =digitalRead(A4);
    int dev2Right = digitalRead(A5);

      
    



      //handle mode selection

   


      
      if(modeManual==LOW){
           //noInterrupts();
        timeSensitiveDetach();
        Serial.println("enters A");
          mode="auto";
          killAllLights();
          toDefault();
          //light the manual control lights
          digitalWrite(2,HIGH);
        //interrupts();
        }
        if(modeDebug==LOW){
          //noInterrupts();
          timeSensitiveDetach();
          Serial.println("enters D");
          mode="debug";
             testLights();
        delay(500);
        killAllLights();
        toDefault();
          digitalWrite(4,HIGH);
          //interrupts();
          }
          if(modeAuto==LOW){
            //noInterrupts();
            timeSensitiveDetach();
            Serial.println("enters M");
            mode="manual";
            killAllLights();
            toDefault();
            digitalWrite(7,HIGH);
            //interrupts();
            }

            
      
      //end mode selection
  //interrupts();

  //HANDLE THE INDIVIDUAL MODE LOGIC

  //DEBUG
  if(mode.equals("debug")){
     

      //in debug mode wire buttons so that dev1 buttons set do the same functionality (do full rocking motion)


      //check the status of the system to know if either button 1 or button 2 was pressed for first branch
      if(dev1Left==LOW){

          //noInterrupts();
          
            digitalWrite(8,HIGH);
            digitalWrite(12,HIGH);

            handleDebug(1);

            delay(150);

            digitalWrite(8,LOW);
            digitalWrite(12,LOW);
            
      //interrupts();
            
        }else if(dev1Right==LOW){
        //    noInterrupts();
       
                  digitalWrite(8,HIGH);
            digitalWrite(12,HIGH);

            handleDebug(1);

            delay(150);

            digitalWrite(8,LOW);
            digitalWrite(12,LOW);
          //interrupts();
            
          }
        
        
        if(dev2Left==LOW){

            //noInterrupts();
            digitalWrite(13,HIGH);
            digitalWrite(3,HIGH);
          
            handleDebug(2);
           
            delay(150);
            digitalWrite(13,LOW);
            digitalWrite(3,LOW);
          
            //interrupts();
          
          }else if(dev2Right==LOW){


            //noInterrupts();
            digitalWrite(13,HIGH);
            digitalWrite(3,HIGH);

          
            handleDebug(2);
            
            delay(150);
            digitalWrite(13,LOW);
            digitalWrite(3,LOW);
          
            //interrupts();
            
            }
    
    
    
    }
  //END DEBUG 
   
 
  //AUTO
  if(mode.equals("manual")){
    
     //MANUAL
    

        //dev1 button1 move to left
        //check which button was pressed

        if(dev1Left ==LOW){
            //device 1 button 1
            //noInterrupts();
            Serial.println("rocking device 1 LEFT");
            if(!isMobile1){
            digitalWrite(8,HIGH);
            rockDevice(1,1);
         
            delay(50);
            digitalWrite(8,LOW);
           
            }
           //  interrupts();
          }
          if(dev1Right==LOW){
            //noInterrupts();
            if(!isMobile1){
            Serial.println("rocking device 1 RIGHT");
            digitalWrite(12,HIGH);
            rockDevice(1,2);
            
            delay(50);
            digitalWrite(12,LOW);
              }
              // interrupts();
            }
            if(dev2Left==LOW){
               //noInterrupts();
              if(!isMobile2){
              Serial.println("rocking device 2 LEFT");
            digitalWrite(13,HIGH);
                rockDevice(2,1);
         
            delay(50);
            digitalWrite(13,LOW);
              }
                 //interrupts();
              }
              if(dev2Right ==LOW){
                 //noInterrupts();
                if(!isMobile2){
                  digitalWrite(3,HIGH);
                Serial.println("rocking device 2 RIGHT");
                rockDevice(2,2);
               
            delay(50);
            digitalWrite(3,LOW);
                }
                 //interrupts();
                }
      
    //END MANUAL

    }
    //END true manual


  
  
    if(mode.equals("auto")){
      //to prep: toggle state of device to set in constant sweep motion

      //check if device 1 buttons are pressed

      //buttons for device 1 is pressed
      if(dev1Left==LOW || dev1Right==LOW){
      
     //    noInterrupts();
        handleAuto(1);
        delay(250);
       //  interrupts();
        }
        
        if(dev2Left==LOW || dev2Right==LOW){
         //  noInterrupts();

         Serial.println("entering the button press for device2");
           handleAuto(2);
          delay(250);
           //interrupts();
          }


          //handle the sweeping motion

          if(servoState1==true){

            handleAutoSweep(1);
            
            
            }
            if(servoState2==true){
              
              handleAutoSweep(2);
              
              }



        


      
      }

    //END true Auto
    

  delay(100);

}


