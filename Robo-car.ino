int pinLB=6; // define pin6 as left back connect with IN1
int pinLF=9; // define pin9 as left forward connect with IN2
int pinRB=10; // define pin10 as right back connect with IN3
int pinRF=11; // define pin11 as right forward connect with IN4
int EnA = 8;
int EnB = 7;
int active_input = 1000;


void setup()
{
Serial.begin(115200);
Serial.setTimeout(1);
pinMode(pinLB,OUTPUT);
pinMode(pinLF,OUTPUT);
pinMode(pinRB,OUTPUT);
pinMode(pinRF,OUTPUT);
pinMode(EnA, OUTPUT);
pinMode(EnB, OUTPUT);

}
void advance() // forward
{
digitalWrite(pinRB,LOW);
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,LOW);
digitalWrite(pinLF,HIGH);
analogWrite(EnA, 255);
analogWrite(EnB, 255);
}
void turnL() //turn left
{
digitalWrite(pinRB,LOW);
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,LOW);
analogWrite(EnA, 150);
analogWrite(EnB, 150);
}
void turnR() //turn right
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,LOW);
digitalWrite(pinLB,LOW);
digitalWrite(pinLF,HIGH);
analogWrite(EnA, 150);
analogWrite(EnB, 150);
}
void stop() //stop
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH);
}
void back() //back
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,LOW);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,LOW);
analogWrite(EnA, 180);
analogWrite(EnB, 180);
}

void loop()
{
   String in = "";
   if (Serial.available())
   {
      in = Serial.readString();   
      const char* input = in.c_str();
      if (input != 0 && *input != active_input)
      {
         active_input = *input;
      
      }
   }

   if (active_input == 'w')
   {
      advance();
   }
   else if (active_input =='a')
   {
      turnL();
   }
   else if (active_input =='s')
   {
      back();
   }
   else if (active_input =='d')
   {
      turnR();
   }
   else
   {
      stop();
   }
   delay(20);
}
