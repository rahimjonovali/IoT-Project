// int ledPin = 13; // choose the pin for the LED

// int inputPin = 2; // choose the input pin (for PIR sensor)

// int pirState = LOW; // we start, assuming no motion detected

// int val = 0; // variable for reading the pin status

// //variables needed to store values

// long pulse, inches, cm;

// void setup() {

// pinMode(ledPin, OUTPUT); // declare LED as output

// pinMode(inputPin, INPUT); // declare sensor as input

// Serial.begin(9600);

// }

// void loop(){

// val = digitalRead(inputPin); // read input value

// if (val == HIGH) { // check if the input is HIGH

// setColor(250,0,255,ledPin); // choose the color value

// digitalWrite(ledPin, HIGH); // turn LED ON

// if (pirState == LOW) {

// // we have just turned on

// Serial.println(“Motion detected!”);

// // We only want to print on the output change, not state

// pirState = HIGH;

// pulse = pulseIn(inputPin, HIGH);

// //147uS per inch

// inches = pulse/147;

// //change inches to centimetres

// cm = inches * 2.54;

// Serial.print(inches); // print for the inches value

// Serial.print(“in, “);

// Serial.print(cm);

// Serial.print(“cm”); // print for the centinetres value

// Serial.println();

// delay(500);

// }

// } else {

// digitalWrite(ledPin, LOW); // turn LED OFF

// if (pirState == HIGH){

// // we have just turned of

// Serial.println(“Motion ended!”);

// // We only want to print on the output change, not state

// pirState = LOW;

// }

// }

// }

// void setColor(int red, int green, int blue,int led) // color function to set the color you want for the LED

// {

// #ifdef COMMON_ANODE

// red = 255 – red; // the red channel value

// green = 255 – green; // the green channel value

// blue = 255 – blue; // the blue channel value

// #endif

// // dedicate every channel value to get one color

// analogWrite(led, red);

// analogWrite(led, green);

// analogWrite(led, blue);

// }