// This code controls the components of an intrusion detection system 

//-----------------------
//get keypad library
#include <Keypad.h>
//get servo library 
#include <Servo.h>
//-----------------------

//----------pin variables--------
#define pirtwo A1
#define buzzer A0
int redpin = 12;
int greenpin = 11;
int pirone = 13; 
int servopin = 2;
//-----------------------------

//----------boolean variables for door, security and alarm--------
boolean locked = false;  //door lock
boolean activated = false;  //security system
//--------------------------------

//--------init pir stat, password trial----
int i = 0; //password trial count
int pirstat1 = 0; //pir 1
int pirstat2 = 0; //pir 2

//-----------------------------------


//-----------------keypad setup------------------
//--password--
String lockpass = "123";
String activatepass = "1234";
String userlock;
String quitkey;
//-----------

//--set number of columns and rows--
const byte NUMROW = 4;
const byte NUMCOL = 4;

//--create 2d char array storing keypad values--
char keymap [NUMROW][NUMCOL] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};

//--create array of keypad pins--
//--(R1, R2, R3, R4, C1, C2, C3, C4 from left to right)--
//rows
byte keyrows[NUMROW] = {10, 9, 8, 7}; 
//columns
byte keycols [NUMCOL] = {6, 5, 4, 3};

//--instantiate keypad object--
//(array of keypad values, row pins, column pins, number of rows, number of columns)
Keypad keypad = Keypad(makeKeymap(keymap), keyrows, keycols, NUMROW, NUMCOL);

//----------------end of keypad setup----------------------

//-------------------Servo setup--------------
//create servo object
Servo servo;

//variable to store servo's position
int servopos = 0;


//---------------setup---------------------
void setup()
{
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(pirone, INPUT);
  pinMode(pirtwo, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  
  //--------set servo object as servo connected to servopin-------
  servo.attach(servopin);

}
//-------------------------------------------

//------------------main loop---------------
void loop(){
  
  //light up leds according to status (activated, deactivated, locked, unlocked)
  statuslights();
  
  //----------------------Keypad-------------------------
  //get user's key
  char userkey = keypad.getKey();
   
  //if something is entered...
  if (userkey){
    //------------------Check what user entered-------------
    
    //----------------take in user pin------
    //if userkey is not "*" (symbol used as "enter")
    //and if the number of tries is less than 5
    if (userkey != '*' && i < 5){
      //print out key for testing
      Serial.println(userkey);
      //add it to user's password
      userlock += userkey;
      
    //--------------------------------------
    
      
    //-----check value of user's pin-------      
    //once user finished entering pin...
    } else if (userkey == '*') {
     	//-------unlock door--------
      	if (userlock.equals(lockpass) && locked == true){
          unlockdoor();
        //--------------------------
          
         //---------lock door------------
        //if password matches and door is unlocked
     	} else if (userlock.equals(lockpass) && locked == false){
          lockdoor();
        //--------------------------
          
      	//---------activate security-----
        //if user pin is the activate pass, and it's deactivated
      	} else if (userlock.equals (activatepass) && activated == false){
          activate();
        //--------------------------
    
        //----------deactivate security------
        //if user pin is the activate pass and it's activated
     	} else if (userlock.equals (activatepass) && activated == true){
          deactivate();
        //-------------------------------------------

        //------if userpin doesn't match any saved pin-----
        } else {
          Serial.println("Pin doesn't match.");
          //clear user pin
          userlock = "";
          //add one to number of tries 
          i++;

          //flash green and red lights thrice
          flashlights();
        } //else end
     
       //---------------------------------
      
    //---------if number of tries exceeds 5------
    } else {
      //clear user lock
       userlock = "";  
      //print message 
      Serial.println ("TOO MANY TRIES. INTRUDER.");
      
      
       //turn on alarm
       alert(); 
     
     }//else end
  //-------------------------------------------
  }
  
  //----------------------------
  
  //-------------------PIR SENSOR----------------
  //read pir status for both sensors
  pirstat1 = digitalRead(pirone);
  pirstat2 = digitalRead (pirtwo);
  //if security is activated and one of the sensors detects something
  if (activated == true && (pirstat1 == HIGH || pirstat2 == HIGH)){
    //set off alarm
    alert();
  }
   //---------------------------------------------
  
  
  
  
  
} //--------------void loop end-----------------

//--------------show status of system with lights ---------------
void statuslights(){
  //-------------Light state for locked, unlocked, activated, deactivated--------
  //if it's locked, turn on green light
  if (locked == true){
    digitalWrite(greenpin, HIGH);
  //if unlocked, turn off green light
  } else {digitalWrite(greenpin, LOW);}
  //if secured, turn on red light
  if (activated == true){
    digitalWrite(redpin, HIGH);
  //if secure mode is not on, turn off red light
  } else {digitalWrite(redpin, LOW);}
  
}
//------------------------------------------------------

//---------------flash lights when pin doesn't match----------
void flashlights(){
  		digitalWrite (redpin, HIGH);
        digitalWrite (greenpin, HIGH);
        delay (500);
        digitalWrite (redpin, LOW);
        digitalWrite (greenpin, LOW);
        delay(500);
        
}
//-------------------------------------------------------------

//--------------unlock door function----------
void unlockdoor(){
  //set locked as false
  locked = false; 
  statuslights();
  
  //set servo position to 45 degrees
   servopos = 45;
  //have servo move to that position
  servo.write(servopos); 
  
  //clear userlock, i and print status
  clearinput("Unlocked.");
}
//-------------------------------------------

//--------------lock door function-----------
void lockdoor(){
  //set locked as true
  locked = true;
  statuslights(); 
  
  //set servo position to 135 degrees
   servopos = 135;
  //have servo move to that position
  servo.write(servopos); 
  
  //clear userlock, i and print status
  clearinput("Locked.");
}
//------------------------------------------

//------------activate security function-----------
void activate(){
  //set activated as true
  activated = true;
  statuslights();
  //clear userlock, i and print status
  clearinput("Activated.");
}

//---------------------------------------------

//------------deactivate security function-------
void deactivate(){
  //set activated as false
  activated = false;
  statuslights();
  //clear userlock, i and print status
  clearinput("Deactivated.");
}
//---------------------------------------------
    
//---------Clear userlock and i, and print status--------------------

void clearinput(String status){
  //clear userlock and i
  i = 0;
  userlock = "";
  //print status on monitor
  Serial.println(status);
  
}    
//---------------------------------------------

//----------alert function---------------
void alert(){
  //lock door if unlocked
  if (locked == false){
      lockdoor();
    }
  //-----for testing purposes------
  //-----to avoid having the alarm ring forever--------
  while (true){
    char userquit = keypad.getKey();
    if (userquit){
      quitkey = userquit;
      if (quitkey.equals ("#")){
     	 break;
      }
    }
    //--------------------------
    
    tone(buzzer, 200); // 0.2 KHz signal to buzzer pin
    delay(250);        // delay 0.5 seconds
    noTone(buzzer);     // stop signal
    delay(250);        // delay 0.5 seconds
    
      //flash red light
      digitalWrite (redpin, HIGH);
      delay (250);
      digitalWrite (redpin, LOW);
      delay (250);
        
    
  }
}
//---------------------------------------------


