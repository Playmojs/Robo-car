// #include <Servo.h>

// Servo servo;
// float angle = 0;
// int active_input;
// float shift = 5;
// float initial_shift = 0;

// void setup()
// {
//     Serial.begin(9600);
//     servo.attach(5);
// }

// void ShiftAngle(float angle)
// {
//     servo.write(angle);
// }

// float CorrectAngle(float angle, bool not_differential = true)
// {
//     return (angle-12*not_differential) * 10 / 9; 
// }

// void loop()
// {
//     String in = "";
//     const char* input;
//     if (Serial.available())
//     {
//         in = Serial.readStringUntil(':');   
//         input = in.c_str();
//         if (*input != 0 && *input != active_input)
//         {
//             active_input = *input;
//             Serial.print("V:Verify ");
//             Serial.print(active_input);
//             Serial.println(":");
//             Serial.flush();
//         }
//     }
//     if (*input == 't')
//     {
//         ShiftAngle(angle);
//         angle += CorrectAngle(shift, false);
//         if (angle >= 180)
//         {
//             angle = 0;
//         }
//     }
//     if (*input == 'q')
//     {
//         delay(50);
//         if (Serial.available())
//         {
//             String classifier = Serial.readStringUntil(':');
//             initial_shift = classifier.toFloat();
//             Serial.print("V:Verify ");
//             Serial.print(initial_shift);
//             Serial.println(":");
//         }
//         for(int i = CorrectAngle(initial_shift); i <= 180; i+=50/9)
//         {
//             servo.write(i);
//             delay(100);
//         }
//         servo.write(CorrectAngle(90));
//     }
// }