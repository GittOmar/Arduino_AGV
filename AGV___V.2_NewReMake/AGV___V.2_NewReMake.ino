#define   F_Right 6
#define   B_Right 7  // Right Wheel
#define Pwm_Right 9

#define   F_Left  4
#define   B_Left  5  // Left Wheel
#define Pwm_Left 10

#define IR_Right  11
#define IR_Middle 12 // IR Sensors
#define IR_Left   13

#define Trig      A3
#define Echo      A4

#define Potentiometer A0  // Additions
#define     Buz       8

bool IRstate_Right  = LOW ;
bool IRstate_Middle = LOW ; // IR State == LOW <White>
bool IRstate_Left   = LOW ;

int Potentiometer_Read ;
int Main_Speed ;             // Potentiometer Reading And Speed Control
int Secondary_Speed ;
int Speed_Presentage ;

unsigned int Distance;
unsigned int Less_Distance = 10;
int Distance_Time;

int TimeOutOfPath = 0; 

void setup() 
{
  
 Serial.begin(9600);             // Serial Baud Rate
 
 pinMode(F_Right,OUTPUT);
 pinMode(B_Right,OUTPUT);       // Right Wheel Pin State
 pinMode(Pwm_Right,OUTPUT);

 pinMode(F_Left,OUTPUT);
 pinMode(B_Left,OUTPUT);      // Left Wheel Pin State
 pinMode(Pwm_Left,OUTPUT);

 pinMode(IR_Right,INPUT);
 pinMode(IR_Middle,INPUT);   // IR Pin State
 pinMode(IR_Left,INPUT);

 pinMode(Trig,OUTPUT);      // Ultrasonic Pin State
 pinMode(Echo,INPUT);     
 
 pinMode(Buz,OUTPUT);      // Buz Pin State

 delay(3000);
 tone(Buz,3333); 
 delay(700);              // Robot Sound Intro 
 noTone(Buz);
 delay(2000);         
 
}


void loop() 
{
 IRstate();
 SpeedCalculations(); 
 Ultrasonic();
 
  if(IRstate_Middle == HIGH && Distance>=Less_Distance)      // First Case _ IF Middle See Black Move Forward    // IF
   {
    Forward();
   }
 
  else if(IRstate_Middle == LOW && Distance>=Less_Distance)  // Second Case _ Middle See White                  // Esle IF
   {
  while(IRstate_Right == LOW && IRstate_Left == LOW && Distance>=Less_Distance) //  While Right And Left See White Move Forward  // While
   {
    Forward();
   }
  
   if(IRstate_Right == HIGH  ) // IF Right See Black     //IF
   { 
   while(IRstate_Middle == LOW && Distance>=Less_Distance) // While Middle See White Turn Left   // While
   {
    Left();
    tone(Buz,2900,100);
   }
   }

  
   else if(IRstate_Left == HIGH  ) // IF Left See Black   //Else IF
    {
   while(IRstate_Middle == LOW && Distance>=Less_Distance) // While Middle See White Turn Right  // While
    { 
      Right();
      tone(Buz,3000,100);
    }
    }
    }
    else if(Distance<=Less_Distance)
    {
      Stop();
    }
    }  // Void Loop End


























void IRstate()  // Read IR State
{
 IRstate_Right  = digitalRead(IR_Right);
 IRstate_Middle = digitalRead(IR_Middle);
 IRstate_Left   = digitalRead(IR_Left);
}

void OutOfPath() 
{
  IRstate();
  if(IRstate_Right == LOW && IRstate_Middle == LOW && IRstate_Left == LOW || IRstate_Right == HIGH && IRstate_Middle == HIGH && IRstate_Left == HIGH)
    {
    TimeOutOfPath++;
    Serial.println(TimeOutOfPath);
  if(TimeOutOfPath>=1200) 
     {
  while(IRstate_Right == LOW && IRstate_Middle == LOW && IRstate_Left == LOW || IRstate_Right == HIGH && IRstate_Middle == HIGH && IRstate_Left == HIGH)
    {
        TimeOutOfPath=0;
        Stop();
        tone(Buz,3333);
        delay(500);
        noTone(Buz);
        delay(500);
   }
   }
   }
  else  // Else
   {
     TimeOutOfPath=0;
   }
}

void Ultrasonic()
{
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  Distance_Time = pulseIn(Echo,HIGH); // Problem
  Distance=(Distance_Time*0.035)/2;
}

void Forward()
{
  IRstate();
  SpeedCalculations();
  OutOfPath();
  Ultrasonic();
  
  analogWrite (Pwm_Right,Main_Speed);
  analogWrite (Pwm_Left ,Main_Speed);
  
  digitalWrite(F_Right,HIGH);
  digitalWrite(B_Right,LOW);
  
  digitalWrite(F_Left ,HIGH);
  digitalWrite(B_Left ,LOW);
}



void Right()
{
  IRstate();
  SpeedCalculations();
  OutOfPath();
  Ultrasonic();
  
  analogWrite (Pwm_Right,Main_Speed);
  analogWrite (Pwm_Left ,10); 
  
  digitalWrite(F_Right,HIGH);
  digitalWrite(B_Right,LOW);
  
  digitalWrite(F_Left ,HIGH);
  digitalWrite(B_Left ,LOW);
}



void Left()
{
  IRstate();
  SpeedCalculations();
  OutOfPath();
  Ultrasonic();
  
  analogWrite (Pwm_Right,10); 
  analogWrite (Pwm_Left ,Main_Speed);
  
  digitalWrite(F_Right,HIGH);
  digitalWrite(B_Right,LOW);
  
  digitalWrite(F_Left ,HIGH);
  digitalWrite(B_Left ,LOW);
}



void Stop()
{
  IRstate();
  SpeedCalculations();
  OutOfPath();
  Ultrasonic();
  
  digitalWrite(F_Right,LOW);
  digitalWrite(B_Right,LOW);

  digitalWrite(F_Left,LOW);
  digitalWrite(B_Left,LOW);
}



void SpeedCalculations()
{
  Potentiometer_Read = analogRead(Potentiometer);
  Secondary_Speed    = (Potentiometer_Read*255.0)/1001.0;
  Main_Speed         = constrain(Secondary_Speed,70,255);
  Speed_Presentage   = map(Main_Speed,70,255,0,100);
 // Serial.println  (Speed_Presentage);
// Serial.println   ('%');
}
