#include <TimerOne.h>
#define FR 6
#define FL 4
#define BR 7
#define BL 5
#define PR 9
#define PL 10

#define IRA 8
#define IRB 12
#define IRC 13

#define PT A0 
#define BZ 11

#define TRIG A1
#define ECHO A2
#define volt A5
bool READA = LOW;
bool READB = LOW;
bool READC= LOW;

int PTread;
int Speed;
int speed;
int presentage;

bool pass =true;

int Case;

unsigned int Distance=0;
unsigned int distance=0;
unsigned int Cdistance=20;
int time=0;


void setup()
{
  Serial.begin(9600);
  pinMode(FR,OUTPUT);
  pinMode(FL,OUTPUT);
  pinMode(BR,OUTPUT);
  pinMode(BL,OUTPUT);
  pinMode(PR,OUTPUT);
  pinMode(PL,OUTPUT);
  
  pinMode(IRA,INPUT);
  pinMode(IRB,INPUT);
  pinMode(IRC,INPUT);

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(volt,OUTPUT);
  
  pinMode(BZ,OUTPUT);
  stop();
  delay(3000);
  tone(BZ,3333);
   delay(700);
   noTone(BZ);
  delay(2000);
  
 digitalWrite(volt,HIGH);

Timer1.attachInterrupt(start);

}

void loop()
 {
 Distance= ULTRASONIC(distance);
 Serial.println(Distance);
 }






void start()
{

 IRread();
  
  if(READB==HIGH ) // black
  {
    Case=0;
  
  }
  
  else if(READB==LOW ) // white
  { 
    Case=1;
  }

  
  
    
     switch(Case)
  {
  
    case 0:
    FORWARD();
    break;



    case 1:
   
    IRread();

    
    while(READA==LOW && READC==LOW  ) //while
    {
      
       IRread();
       FORWARD();
    }
    
    IRread();

    
    if(READA==HIGH)
    {
      
      while(READB==LOW ) // while
      {
      
        IRread();
        LEFT();
        tone(BZ,2900,100);
      }
    }
    
    else if(READC==HIGH )
    {
       
       while(READB==LOW  ) //while
      {
     
        IRread();
        RIGHT();
        tone(BZ,3000,100);
      }
    }
    break;

 
    default:
    stop();
  }
  
}





int  ULTRASONIC(int distance )
{
 


 digitalWrite(TRIG,HIGH); // 
 
  
delayMicroseconds(2);

 digitalWrite(TRIG,LOW); //
 
 
 time = pulseIn(ECHO,HIGH); 
 distance=(time*0.035)/2;  
 return distance;
}



void IRread()
{
  READA=digitalRead(IRA);
  READB=digitalRead(IRB);
  READC=digitalRead(IRC);
}

void FORWARD()
{
  
  analogWrite(PR,speed);
  digitalWrite(FR,HIGH);
  analogWrite(PL,speed);
  digitalWrite(FL,HIGH);
}
void RIGHT()
{
  
  analogWrite(PR,speed);
  digitalWrite(FR,HIGH);
  analogWrite(PL,10);
  digitalWrite(FL,HIGH);
}
void stop()
{
  pinMode(FR,LOW);
  pinMode(FL,LOW);
  pinMode(BR,LOW);
  pinMode(BL,LOW);
}
void LEFT ()
{
  
  analogWrite(PL,speed);
  digitalWrite(FL,HIGH);
  analogWrite(PR,10);
  digitalWrite(FR,HIGH);
}
void SPEED()
{
 
 Distance= ULTRASONIC(distance);
 if(distance<=Cdistance)
 {
  speed=0;
 }
 else
 {
  speed=150;
 }

   //PTread=analogRead(PT);
   //Speed=PTread*255.0/1001.0;
   //speed=constrain(Speed,70,255);
   //presentage=map(speed,70,255,0,100);
  // Serial.println(speed);
  // Serial.println('%');

  
}
