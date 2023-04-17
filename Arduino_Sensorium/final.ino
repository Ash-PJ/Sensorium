const int numValues = 15;
int values[numValues];
int motors[numValues];

void setup() {
  Serial.begin(9600);
  // Map the pixel blocks to the corresponding GPIO pins
  pinMode(2, OUTPUT); // Pixel block 1, digital pin 2
  pinMode(3, OUTPUT); // Pixel block 2, digital pin 3
  pinMode(4, OUTPUT); // Pixel block 3, digital pin 4
  pinMode(5, OUTPUT); // Pixel block 4, digital pin 5
  pinMode(6, OUTPUT); // Pixel block 5, digital pin 6
  pinMode(7, OUTPUT); // Pixel block 6, digital pin 7
  pinMode(8, OUTPUT); // Pixel block 7, digital pin 8
  pinMode(9, OUTPUT); // Pixel block 8, digital pin 9
  pinMode(10, OUTPUT); // Pixel block 9, digital pin 10
  pinMode(11, OUTPUT); // Pixel block 10, digital pin 11
  pinMode(12, OUTPUT); // Pixel block 11, digital pin 12
  pinMode(A0, OUTPUT); // Pixel block 12, analog pin A0
  pinMode(A1, OUTPUT); // Pixel block 13, analog pin A1
  pinMode(A2, OUTPUT); // Pixel block 14, analog pin A2
  pinMode(A3, OUTPUT); // Pixel block 15, analog pin A3
  for (int i = 0; i < numValues; i++) {
    motors[i] = 0;
  }
}

void loop() {
  // Wait for incoming data on the serial port
  while (Serial.available() < 2) {
    // Wait until at least 2 bytes are available (1 for the digit and 1 for the comma)
  }
  
  // Read incoming data from the serial connection
  for (int i = 0; i < numValues; i++) {
    values[i] = Serial.parseInt();
    // Wait for the comma separator between values
    while (Serial.peek() != ',' && Serial.available() > 0) {
      Serial.read(); // Discard any non-comma characters
    }
    if (Serial.peek() == ',') {
      Serial.read(); // Discard the comma character
    }
  }
  
  // Update the motor values based on the incoming data
  for (int i = 0; i < numValues; i++) {
    int motorIntensity = 0;
    if (values[i] == 0) {
      // Black pixel block, set motor to 95% intensity
      motorIntensity = 242;
    } else if (values[i] == 128) {
      // Grey pixel block, set motor to 20% intensity
      motorIntensity = 51;
    } else {
      // White pixel block, set motor to 0% intensity
      motorIntensity = 0;
    }
    motors[i] = motorIntensity;
    if (i < 10) {
      digitalWrite(i+2, motors[i]);
    } else if (i < 14) {
      analogWrite(i-10 + A0, motors[i]);
    } else {
      break;
    }
  }
}
