// #include <SoftwareSerial.h>

// int state = 0;
// SoftwareSerial mySerial(2,3); 


// void setup() {
//     pinMode(LED_BUILTIN, OUTPUT);
//     digitalWrite(LED_BUILTIN, HIGH);
//     mySerial.begin(9600);
// }

// void loop() {
//     if(mySerial.available() > 0){ // Checks whether data is comming from the serial port
//       state = mySerial.read(); // Reads the data from the serial port
//   }

//   if (state == '0') {
//     digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
//     mySerial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
//     state = 0;
//   }
//   else if (state == '1') {
//     digitalWrite(LED_BUILTIN, HIGH);
//     mySerial.println("LED: ON");;
//     state = 0;
//   } 
// }