// variables for all the buttons
int UP = 5;   // pin 15 - Up
int DN = 6;   // pin 7 - Down
int LT = 7;   // pin 14 - Left
int RT = 8;   // pin 6 - Right
int A = 9;    // pin 13 - A
int B = 2;    // pin 10 - K2
int C = 13;   // pin 2 - K3
int X = 11;   // pin 5 - B
int Y = 10;   // pin 12 - C
int Z = 12;   // pin 4 - D 
int L = 3;    // pin 3 - Coin
int R = -1;    // pin 13 - A - Dup -1 used to ignore default key map
int ST = 4;   // pin 11 - Start
// Saturn input line pins
int D0 = A3;  // pin 3
int D1 = A2;  // pin 2
int D2 = A5;  // pin 8
int D3 = A4;  // pin 7
int S0 = A0;  // pin 4
int S1 = A1;  // pin 5

int reproLED_Pin = 0;
int val = 0;
int readDelay = 1;
bool reprogrammingEnabled = false;
bool rapidConfigEnabled = false;
int pinOut[8]={A,X,Y,Z,ST,L,B,C}; // neo geo - A,B,C,D,START,COIN,K2,K3
int buttonConfig[9]={A,B,C,X,Y,Z,L,R,ST};
int rapidFireConfig[9]={0,0,0,0,0,0,0,0,0};
int buttonIndex = 0;
int rapidConfigTimer = 0;

void setup()
{
  // Delay for hot plug issue
  delay(300);
  
  pinMode(reproLED_Pin, OUTPUT);
  //Serial.begin(9600);
  // Neo Geo Pins
  pinMode(UP, OUTPUT);
  pinMode(DN, OUTPUT); 
  pinMode(LT, OUTPUT);
  pinMode(RT, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(X, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(Z, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(ST,OUTPUT);

  // Saturn Pins
  // Declares D0-3 as inputs with internal pullup.
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  // Declares Select Pins as outputs.
  pinMode(S0, OUTPUT);          
  pinMode(S1, OUTPUT);
}

void loop()
{
  // reset pins
  UP = 0;
  DN = 0;
  LT = 0;
  RT = 0;
  A = 0;
  B = 0;
  C = 0;
  X = 0;
  Y = 0;
  Z = 0;
  L = 0;
  R = 0;
  ST = 0;

  delay(readDelay);
  Saturn1stBitRead();
  delay(readDelay);
  Saturn2ndBitRead();
  delay(readDelay);
  Saturn3rdBitRead();
  delay(readDelay);
  Saturn4thBitRead();
  delay(readDelay);

  if(!reprogrammingEnabled && !rapidConfigEnabled)
  {
    if(DN == 1)
    {
      //Serial.println("Send - Down");
      digitalWrite(6, LOW); 
    }
    else
    {
      digitalWrite(6, HIGH); 
    }
    if(UP == 1)
    {
      //Serial.println("Send - Up");
      digitalWrite(5, LOW); 
    }
    else
    {
      digitalWrite(5, HIGH); 
    }
    if(LT == 1)
    {
      //Serial.println("Send - Left");
      digitalWrite(7, LOW); 
    }
    else
    {
      digitalWrite(7, HIGH); 
    }
    if(RT == 1)
    {
      //Serial.println("Send - Right");
      digitalWrite(8, LOW); 
    }
    else
    {
      digitalWrite(8, HIGH); 
    }
    
    if(buttonConfig[0] != -1)
    {
      if(A == 1)
      {
        //Serial.println("Send - A");
        digitalWrite(buttonConfig[0], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[0], HIGH); 
      }
    }
    if(buttonConfig[1] != -1)
    {
      if(B == 1)
      {
        //Serial.println("Send - K2");
        digitalWrite(buttonConfig[1], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[1], HIGH); 
      }
    }
    if(buttonConfig[2] != -1)
    {
      if(C == 1)
      {
        //Serial.println("Send - K3");
        digitalWrite(buttonConfig[2], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[2], HIGH); 
      }
    }
    if(buttonConfig[3] != -1)
    {
      if(X == 1)
      {
        //Serial.println("Send - B");
        digitalWrite(buttonConfig[3], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[3], HIGH); 
      }
    }
    if(buttonConfig[4] != -1)
    {
      if(Y == 1)
      {
        //Serial.println("Send - C");
        digitalWrite(buttonConfig[4], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[4], HIGH); 
      }
    }
    if(buttonConfig[5] != -1)
    {
      if(Z == 1)
      {
        //Serial.println("Send - D");
        digitalWrite(buttonConfig[5], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[5], HIGH); 
      }
    }
    if(buttonConfig[6] != -1)
    {
      if(L == 1)
      {
        //Serial.println("Send - L");
        digitalWrite(buttonConfig[6], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[6], HIGH); 
      }
    }
    if(buttonConfig[7] != -1)
    {
      if(R == 1)
      {
        //Serial.println("Send - R");
        digitalWrite(buttonConfig[7], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[7], HIGH); 
      }
    }
    if(buttonConfig[8] != -1)
    {
      if(ST == 1)
      {
        //Serial.println("Send - Start");
        digitalWrite(buttonConfig[8], LOW); 
      }
      else
      {
        digitalWrite(buttonConfig[8], HIGH); 
      }
    }
  }
  else
  {
    CaptureReprogramInput();
    ToggleRapidFire();
  }
  
  CheckForReprogram();
  CheckForRapid();
}

// 1st bit of the demuxer,
void Saturn1stBitRead()
{
  //delay(5);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  //delay(5);// This sets the timing of the select pulses (default 5 = 100hz)

  val = digitalRead(D0);
  if (val == LOW)
  {             // check if the data input is LOW (button pressed)
    Z = 1;
    //Serial.println("Z");
  }
  val = digitalRead(D1); 
  if (val == LOW)
  {       
    Y = 1;
    //Serial.println("Y");
  }
  val = digitalRead(D2);
  if (val == LOW)
  {       
    X = 1;
    //Serial.println("X");
  }
  val = digitalRead(D3); 
  if (val == LOW)
  {      
    R = 1;
    //Serial.println("R");
  }  
}

// 2nd bit from the demuxer,
void Saturn2ndBitRead()
{
  //delay(5);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  //delay(5);// This sets the timing of the select pulses (default 5 = 100hz)

  val = digitalRead(D0);        // read input value from data line
  
  if (val == LOW)
  {             // check if the data input is LOW (button pressed)
    B = 1;                        // Stores the B button as pressed.
    //Serial.println("B");
  }
  val = digitalRead(D1); 
  if (val == LOW)
  {       
    C = 1;
    //Serial.println("C");
  }
  val = digitalRead(D2);
  if (val == LOW)
  {       
    A = 1;
    //Serial.println("A");
  }
  val = digitalRead(D3); 
  if (val == LOW)
  {      
    ST = 1;
   //Serial.println("ST");
  }  
}

// 3rd bit from the demuxer,
void Saturn3rdBitRead()
{
  //delay(5);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  //delay(5);// This sets the timing of the select pulses (default 5 = 100hz)

  val = digitalRead(D0);
  if (val == LOW)
  {            
    UP = 1;                        
    //Serial.println("UP");
  }
  val = digitalRead(D1); 
  if (val == LOW)
  {       
    DN = 1;
   //Serial.println("Down");
  }
  val = digitalRead(D2);
  if (val == LOW)
  {       
    LT = 1;
    //Serial.println("Left");
  }
  val = digitalRead(D3); 
  if (val == LOW)
  {      
    RT = 1;
   //Serial.println("Right");
  }  
}

// 4th bit from the demuxer,
void Saturn4thBitRead()
{
  //delay(5);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  //delay(5);// This sets the timing of the select pulses (default 5 = 100hz)

  val = digitalRead(D3);
  if (val == LOW)
  {             // check if the data input is LOW (button pressed)
    L = 1;                        // Stores the B button as pressed.
    //Serial.println("L");
  }
}

void CheckForReprogram()
{
  if(ST == 1 && A == 1 && Z == 1)
  {
    //Serial.println("detect reprogram");
    reprogrammingEnabled = !reprogrammingEnabled;
    //Serial.println(reprogrammingEnabled);
    if(reprogrammingEnabled)
    {
      digitalWrite(reproLED_Pin, HIGH);
      buttonIndex = 0;
      // this is to reset all buttons
      int i = 0;
      for(i; i < 9; i++)
      {
        buttonConfig[i] = -1;
      }
    }
    else
    {
      digitalWrite(reproLED_Pin, LOW); 
    }
    delay(500);
  }
}
void CaptureReprogramInput()
{
    if(reprogrammingEnabled)
      return;
  
    if(DN == 1)
    {
      //Serial.println("Send - Down");
      //digitalWrite(6, LOW); 
    }
    if(UP == 1)
    {
      //Serial.println("Send - Up");
      //digitalWrite(5, LOW); 
    }
    if(LT == 1)
    {
      //Serial.println("Send - Left");
      //digitalWrite(7, LOW); 
    }
    if(RT == 1)
    {
      //Serial.println("Send - Right");
      //digitalWrite(8, LOW); 
    }
    if(A == 1)
    { 
      buttonConfig[0] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(B == 1)
    {
      buttonConfig[1] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(C == 1)
    { 
      buttonConfig[2] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(X == 1)
    {
      buttonConfig[3] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(Y == 1)
    {
      buttonConfig[4] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(Z == 1)
    {
      buttonConfig[5] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(L == 1)
    {
      buttonConfig[6] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(R == 1)
    {
      buttonConfig[7] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    if(ST == 1)
    {
      buttonConfig[8] = pinOut[buttonIndex];
      FlashLED();
      buttonIndex++;
    }
    
    if(buttonIndex == 8)
    {
      rapidConfigEnabled = false;
      //buttonIndex = 0;
      digitalWrite(reproLED_Pin, LOW); 
    }
}

void CheckForRapid()
{
  if(ST == 1 && C == 1 && X == 1)
  {
    //Serial.println("detect rapid");
    rapidConfigEnabled = !rapidConfigEnabled;
    //Serial.println(rapidConfigEnabled);
    if(rapidConfigEnabled)
    {
      digitalWrite(reproLED_Pin, HIGH);
    }
    else
    {
      digitalWrite(reproLED_Pin, LOW); 
    }
    delay(500);
  }
}
void ToggleRapidFire()
{
    if(rapidConfigEnabled)
      reutrn;
  
    rapidConfigTimer++;
    
    if(A == 1)
    { 
      rapidFireConfig[0] = !rapidFireConfig[0];
      FlashLED();
    }
    if(B == 1)
    {
      rapidFireConfig[1] = !rapidFireConfig[1];
      FlashLED();
    }
    if(C == 1)
    { 
      rapidFireConfig[2] = !rapidFireConfig[2];
      FlashLED();
    }
    if(X == 1)
    {
      rapidFireConfig[3] = !rapidFireConfig[3];
      FlashLED();
    }
    if(Y == 1)
    {
      rapidFireConfig[4] = !rapidFireConfig[4];
      FlashLED();
    }
    if(Z == 1)
    {
      rapidFireConfig[5] = !rapidFireConfig[5];
      FlashLED();
    }
    if(L == 1)
    {
      rapidFireConfig[6] = !rapidFireConfig[6];
      FlashLED();
    }
    if(R == 1)
    {
      rapidFireConfig[7] = !rapidFireConfig[7];
      FlashLED();
    }
    if(ST == 1)
    {
      rapidFireConfig[8] = !rapidFireConfig[8];
      FlashLED();
    }
    
    if(rapidConfigTimer == 3000)
    {
      rapidConfigEnabled = false;
      digitalWrite(reproLED_Pin, LOW); 
    }
}

void FlashLED()
{
    digitalWrite(reproLED_Pin, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
    digitalWrite(reproLED_Pin, HIGH);    // turn the LED off by making the voltage LOW
}
