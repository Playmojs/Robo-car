// int input_pin = A1;
// int output_pin = A2;

// void setup() {
//     Serial.begin(115200);
//     pinMode(LED_BUILTIN, OUTPUT);
//     pinMode(input_pin, INPUT);
//     pinMode(output_pin, OUTPUT);
// }

// float F_Distance() // test forward distance
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

// void loop() {
//     float distance = F_Distance();
//     Serial.println(distance);
//     if (distance == 0){return;}
//     if (distance < 10)
//         {digitalWrite(LED_BUILTIN, HIGH);} 
//     else                     
//         {digitalWrite(LED_BUILTIN, LOW);}
// }                    