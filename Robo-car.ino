int pinLB=6; // define pin6 as left back connect with IN1
int pinLF=9; // define pin9 as left forward connect with IN2
int pinRB=10; // define pin10 as right back connect with IN3
int pinRF=11; // define pin11 as right forward connect with IN4
int EnA = 8;
int EnB = 7;
int input_pin = A2;
int output_pin = A3;
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
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(input_pin, INPUT);
   pinMode(output_pin, OUTPUT);

}
void Advance() // forward
{
   digitalWrite(pinRB,LOW);
   digitalWrite(pinRF,HIGH);
   digitalWrite(pinLB,LOW);
   digitalWrite(pinLF,HIGH);
   analogWrite(EnA, 255);
   analogWrite(EnB, 255);
}
void TurnL() //turn left
{
   digitalWrite(pinRB,LOW);
   digitalWrite(pinRF,HIGH);
   digitalWrite(pinLB,HIGH);
   digitalWrite(pinLF,LOW);
   analogWrite(EnA, 150);
   analogWrite(EnB, 150);
}
void TurnR() //turn right
{
   digitalWrite(pinRB,HIGH);
   digitalWrite(pinRF,LOW);
   digitalWrite(pinLB,LOW);
   digitalWrite(pinLF,HIGH);
   analogWrite(EnA, 150);
   analogWrite(EnB, 150);
}
void Stop() //stop
{
   digitalWrite(pinRB,HIGH);
   digitalWrite(pinRF,HIGH);
   digitalWrite(pinLB,HIGH);
   digitalWrite(pinLF,HIGH);
}
void Back() //back
{
   digitalWrite(pinRB,HIGH);
   digitalWrite(pinRF,LOW);
   digitalWrite(pinLB,HIGH);
   digitalWrite(pinLF,LOW);
   analogWrite(EnA, 180);
   analogWrite(EnB, 180);
}

float Distance() // test forward distance
{
    digitalWrite(output_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(output_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(output_pin, LOW);
    float Fdistance = pulseIn(input_pin, HIGH);
    Fdistance= Fdistance/5.8/10;
    return(Fdistance);
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
      Advance();
   }
   else if (active_input =='a')
   {
      TurnL();
   }
   else if (active_input =='s')
   {
      Back();
   }
   else if (active_input =='d')
   {
      TurnR();
   }
   else
   {
      Stop();
   }
   float distance = Distance();
   Serial.println(distance);
   if (distance == 0){return;}
   if (distance < 10)
      {digitalWrite(LED_BUILTIN, HIGH);} 
   else                     
      {digitalWrite(LED_BUILTIN, LOW);}
   delay(20);
}