// // int input_pin = A1;
// // int output_pin = A2;

// // void setup() {
// //     Serial.begin(115200);
// //     pinMode(LED_BUILTIN, OUTPUT);
// //     pinMode(input_pin, INPUT);
// //     pinMode(output_pin, OUTPUT);
// // }

// // float F_Distance() // test forward distance
// // {
// //     digitalWrite(output_pin, LOW);
// //     delayMicroseconds(2);
// //     digitalWrite(output_pin, HIGH);
// //     delayMicroseconds(10);
// //     digitalWrite(output_pin, LOW);
// //     float Fdistance = pulseIn(input_pin, HIGH);
// //     Fdistance= Fdistance/5.8/10;
// //     return(Fdistance);
// // }

// // void loop() {
// //     float distance = F_Distance();
// //     Serial.println(distance);
// //     if (distance == 0){return;}
// //     if (distance < 10)
// //         {digitalWrite(LED_BUILTIN, HIGH);} 
// //     else                     
// //         {digitalWrite(LED_BUILTIN, LOW);}
// // }    

// /*
// QMC5883LCompass.h Library Calibration Example Sketch
// Learn more at [https://github.com/mprograms/QMC5883LCompass]

// Upload this calibration sketch onto your Arduino to provide calibration for your QMC5883L chip.
// After upload, run the serial monitor and follow the directions.
// When prompted, copy the last line into your project's actual sketch.

// ===============================================================================================================
// Release under the GNU General Public License v3
// [https://www.gnu.org/licenses/gpl-3.0.en.html]
// ===============================================================================================================











//                                           UTILITY SKETCH
//                                     NO SERVICABLE PARTS BELOW












// */
// #include <QMC5883LCompass.h>

// QMC5883LCompass compass;

// int calibrationData[3][2];
// bool changed = false;
// bool done = false;
// int t = 0;
// int c = 0;

// void setup() {
//   Serial.begin(9600);
//   compass.init();
  
//   Serial.println("This will provide calibration settings for your QMC5883L chip. When prompted, move the magnetometer in all directions until the calibration is complete.");
//   Serial.println("Calibration will begin in 5 seconds.");
//   delay(5000);
  
// }

// void loop() {
//   int x, y, z;
  
//   // Read compass values
//   compass.read();

//   // Return XYZ readings
//   x = compass.getX();
//   y = compass.getY();
//   z = compass.getZ();

//   changed = false;

//   if(x < calibrationData[0][0]) {
//     calibrationData[0][0] = x;
//     changed = true;
//   }
//   if(x > calibrationData[0][1]) {
//     calibrationData[0][1] = x;
//     changed = true;
//   }

//   if(y < calibrationData[1][0]) {
//     calibrationData[1][0] = y;
//     changed = true;
//   }
//   if(y > calibrationData[1][1]) {
//     calibrationData[1][1] = y;
//     changed = true;
//   }

//   if(z < calibrationData[2][0]) {
//     calibrationData[2][0] = z;
//     changed = true;
//   }
//   if(z > calibrationData[2][1]) {
//     calibrationData[2][1] = z;
//     changed = true;
//   }

//   if (changed && !done) {
//     Serial.println("CALIBRATING... Keep moving your sensor around.");
//     c = millis();
//   }
//     t = millis();
  
  
//   if ( (t - c > 5000) && !done) {
//     done = true;
//     Serial.println("DONE. Copy the line below and paste it into your projects sketch.);");
//     Serial.println();
      
//     Serial.print("compass.setCalibration(");
//     Serial.print(calibrationData[0][0]);
//     Serial.print(", ");
//     Serial.print(calibrationData[0][1]);
//     Serial.print(", ");
//     Serial.print(calibrationData[1][0]);
//     Serial.print(", ");
//     Serial.print(calibrationData[1][1]);
//     Serial.print(", ");
//     Serial.print(calibrationData[2][0]);
//     Serial.print(", ");
//     Serial.print(calibrationData[2][1]);
//     Serial.println(");");
//     }
  
 
// }