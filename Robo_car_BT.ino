// #include <SoftwareSerial.h>
// #include <Servo.h>
// #include <QMC5883LCompass.h>

// bool stopped = false;
// int pinLB=6; // define pin6 as left back connect with IN1
// int pinLF=9; // define pin9 as left forward connect with IN2
// int pinRB=10; // define pin10 as right back connect with IN3
// int pinRF=11; // define pin11 as right forward connect with IN4
// int EnA = 8;
// int EnB = 7;
// int input_pin = A1;
// int output_pin = A2;
// int active_input = 1000;
// SoftwareSerial mySerial(2,3); 
// Servo servo;
// QMC5883LCompass compass;

// void setup()
// {
//    mySerial.begin(9600);
//    mySerial.setTimeout(1);
//    pinMode(pinLB,OUTPUT);
//    pinMode(pinLF,OUTPUT);
//    pinMode(pinRB,OUTPUT);
//    pinMode(pinRF,OUTPUT);
//    pinMode(EnA, OUTPUT);
//    pinMode(EnB, OUTPUT);
//    pinMode(LED_BUILTIN, OUTPUT);
//    pinMode(input_pin, INPUT);
//    pinMode(output_pin, OUTPUT);
//    servo.attach(5);
//    Wire.begin();
//    compass.init();
//    compass.setCalibration(0, 1710, 0, 2116, -2132, 0);
// }
// void Advance() // forward
// {
//    digitalWrite(pinRB,LOW);
//    digitalWrite(pinRF,HIGH);
//    digitalWrite(pinLB,LOW);
//    digitalWrite(pinLF,HIGH);
//    analogWrite(EnA, 255);
//    analogWrite(EnB, 255);
// }
// void TurnL() //turn left
// {
//    digitalWrite(pinRB,LOW);
//    digitalWrite(pinRF,HIGH);
//    digitalWrite(pinLB,HIGH);
//    digitalWrite(pinLF,LOW);
//    analogWrite(EnA, 150);
//    analogWrite(EnB, 150);
// }
// void TurnR() //turn right
// {
//    digitalWrite(pinRB,HIGH);
//    digitalWrite(pinRF,LOW);
//    digitalWrite(pinLB,LOW);
//    digitalWrite(pinLF,HIGH);
//    analogWrite(EnA, 150);
//    analogWrite(EnB, 150);
// }
// void Stop() //stop
// {
//    digitalWrite(pinRB,HIGH);
//    digitalWrite(pinRF,HIGH);
//    digitalWrite(pinLB,HIGH);
//    digitalWrite(pinLF,HIGH);
// }
// void Back() //back
// {
//    digitalWrite(pinRB,HIGH);
//    digitalWrite(pinRF,LOW);
//    digitalWrite(pinLB,HIGH);
//    digitalWrite(pinLF,LOW);
//    analogWrite(EnA, 180);
//    analogWrite(EnB, 180);
// }

// float Distance() // test forward distance
// {
//     digitalWrite(output_pin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(output_pin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(output_pin, LOW);
//     float Fdistance = pulseIn(input_pin, HIGH);
//     Fdistance= Fdistance/5.8/10;
//     return(Fdistance);
// }

// void FloatToBytes(float val,byte* bytes_array){
//   // Create union of shared memory space
//   union {
//     float float_variable;
//     byte temp_array[4];
//   } u;
//   // Overite bytes of union with float variable
//   u.float_variable = val;
//   // Assign bytes to input array
//   memcpy(bytes_array, u.temp_array, 4);
// }

// void loop()
// {
//     String in = "";
//     if (mySerial.available())
//     {
//         in = mySerial.readStringUntil(':');   
//         const char* input = in.c_str();
//         if (input != 0 && *input != active_input)
//         {
//             active_input = *input;
//             mySerial.print("V:Verify ");
//             mySerial.print(active_input);
//             mySerial.println(":");
//         }
//     }

//     if (active_input == 'w')
//     {
//         Advance();
//         stopped = false;
//     }
//     else if (active_input =='a')
//     {
//         TurnL();
//         stopped = false;
//     }
//     else if (active_input =='s')
//     {
//         Back();
//         stopped = false;
//     }
//     else if (active_input =='d')
//     {
//         TurnR();
//         stopped = false;
//     }
//     else if (active_input =='q')
//     {
//         Stop();
//         byte distances[4*37];
//         byte dist[4];
//         for(int i=0; i < 37; i++)
//         {
//             servo.write(5*i);
//             FloatToBytes(Distance(), dist);
//             for (int j= 0; j<4; j++)
//             {
//                 distances[4*i + j] = dist[j];
//             }
//             delay(100);
//         }
//         mySerial.print("D:");
//         mySerial.write(distances, 148);
//         mySerial.println(":");
//         servo.write(90);
//         mySerial.flush();
//         active_input = 1000;
//     }
//     else if (active_input == 'c')
//     {
//         Stop();
//         compass.read();
//         mySerial.print(compass.getAzimuth());
//         delay(500);
//         active_input = 1000;
//     }
//         else if (!stopped)
//     {
//         Stop();
//         stopped = true;
//     }
    
//     //delay(20);
// }