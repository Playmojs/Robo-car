#include <Servo.h>
#include <QMC5883LCompass.h>

bool stopped = false;
int pinLB=6; // define pin6 as left back connect with IN1
int pinLF=9; // define pin9 as left forward connect with IN2
int pinRB=10; // define pin10 as right back connect with IN3
int pinRF=11; // define pin11 as right forward connect with IN4
int EnA = 8;
int EnB = 7;
int input_pin = A1;
int output_pin = A2;
int active_input = 1000;
float initial_angle = 0;
float scan_angle_interval = 50/9; // The applied head-rotation between each scan is 10/9 times the wanted angle, to correct for limited range in the servo
Servo servo;
QMC5883LCompass compass;

void setup()
{
   Serial.begin(9600);
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
   servo.attach(5);
   Wire.begin();
   compass.init();
   compass.setCalibration(0, 1710, 0, 2116, -2132, 0);
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

void FloatToBytes(float val,byte* bytes_array){
  // Create union of shared memory space
  union {
    float float_variable;
    byte temp_array[4];
  } u;
  // Overite bytes of union with float variable
  u.float_variable = val;
  // Assign bytes to input array
  memcpy(bytes_array, u.temp_array, 4);
}

float CorrectAngle(float angle, bool not_differential = true)
{
    return (angle-12*not_differential) * 10 / 9; 
}

template <typename value>
void Verify(value to_print)
{
    Serial.print("V:Verify ");
    Serial.print(to_print);
    Serial.println(":");
}

void loop()
{
    String in = "";
    if (Serial.available())
    {
        in = Serial.readStringUntil(':');
        const char* input = in.c_str();
        if (*input != 0 && *input != active_input)
        {
            active_input = *input;
            Verify(active_input);
        }
    }

    if (active_input == 'w')
    {
        Advance();
        stopped = false;
    }
    else if (active_input =='a')
    {
        TurnL();
        stopped = false;
    }
    else if (active_input =='s')
    {
        Back();
        stopped = false;
    }
    else if (active_input =='d')
    {
        TurnR();
        stopped = false;
    }
    else if (active_input =='q')
    {
        Stop();
        
        int num_scans = ceil((180-initial_angle)/scan_angle_interval);
        byte distances[4*num_scans];
        byte dist[4];
        for(int i = 0; i < num_scans; i++)
        {
            servo.write(initial_angle + i * scan_angle_interval);
            FloatToBytes(Distance(), dist);
            for (int j= 0; j<4; j++)
            {
                distances[4*i + j] = dist[j];
            }
            delay(100);
        }
        Serial.print("D:");
        Serial.print(num_scans);
        Serial.print(":");
        Serial.write(distances, 4*num_scans);
        Serial.println(":");
        servo.write(CorrectAngle(90));
        Serial.flush();
        active_input = 1000;
    }
    else if (active_input == 'c')
    {
        Stop();
        compass.read();
        Serial.print("C:");
        Serial.print(compass.getAzimuth());
        Serial.print(":");
        delay(500);
        active_input = 1000;
    }
    else if (!stopped)
    {
        Stop();
        stopped = true;
    }
    
    //delay(20);
}