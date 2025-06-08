#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

union BtoF {
  byte b[16];
  float fval;
} u;

const int buffer_size = 16;
byte buf[buffer_size];

#define sensor3 A3
#define sensor2 A2
#define sensor1 A1
#define red 10
#define green 8
#define yello 9
#define relay 11
#define buzzer 7
#define RUN_BUTTON_PIN 6 // Define the button pin

enum RobotState { FLUX, ELECTRIC, MAGNETIC };
RobotState currentState = FLUX; // Start with FLUX state
bool buttonPressed = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void toggleState();
void displayFlux();
void displayElectric();
void displayMagnetic();
void controlLEDs(bool greenState, bool yellowState, bool redState);
void writeToMatLab(float number);
float readFromMatlab();

void setup() {
  Serial.begin(115200, SERIAL_8N1);

  pinMode(sensor3, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yello, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(RUN_BUTTON_PIN, INPUT_PULLUP); // Configure button with pull-up resistor

  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {

  // Check button state
  if (digitalRead(RUN_BUTTON_PIN) == LOW) {
    if (!buttonPressed) { // Detect button press transition
      buttonPressed = true;
      toggleState(); // Change the state
    }
  } else {
    buttonPressed = false; // Reset when button is released
  }

  // Display and logic based on the current state
  switch (currentState) {
    case FLUX:
      lcd.setCursor(0, 0);
      lcd.print("EMI DETECTOR MODE ");
      displayFlux();
      break;

    case ELECTRIC:
      lcd.setCursor(0, 0);
      lcd.print("ELECTRIC PROBE    ");
      displayElectric();
      break;

    case MAGNETIC:
      lcd.setCursor(0, 0);
      lcd.print("MAGNETIC PROBE    ");
      displayMagnetic();
      break;
  }

  delay(10); // Small delay to prevent rapid polling
}

// Function to toggle between states
void toggleState() {
  currentState = static_cast<RobotState>((currentState + 1) % 3); // Cycle through states
}

void displayFlux() {
  lcd.setCursor(0, 1);
  float sensor_3 = float(-((analogRead(sensor3) - 515) / 3.75) + 250);
  lcd.print(sensor_3); // showing the field strength value
  writeToMatLab(sensor_3);
  float sensor_M3 = readFromMatlab();
  lcd.setCursor(9, 1);
  lcd.print(sensor_M3);

  // LED and relay logic for Flux mode
  if (sensor_M3 < 200) {
    controlLEDs(HIGH, LOW, LOW);
    digitalWrite(buzzer, LOW);
  } else if (sensor_M3 < 300) {
    controlLEDs(LOW, HIGH, LOW);
    digitalWrite(buzzer, LOW);
  } else {
    controlLEDs(LOW, LOW, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  digitalWrite(relay, sensor_M3 < 300 ? HIGH : LOW);
}

void displayElectric() {
  lcd.setCursor(0, 1);
  float sensor_2 = analogRead(sensor2);
  lcd.print("E_Field: ");
  lcd.print(sensor_2);
  lcd.print(" V      "); // Ensure padding to clear display
  writeToMatLab(sensor_2);
}

void displayMagnetic() {
  lcd.setCursor(0, 1);
  int sensor_1 = analogRead(sensor1);
  lcd.print("H_Field: ");
  lcd.print(sensor_1 - 500);
  lcd.print(" T      "); // Ensure padding to clear display
  writeToMatLab(sensor_1);
}

// Helper function to control LEDs
void controlLEDs(bool greenState, bool yellowState, bool redState) {
  digitalWrite(green, greenState);
  digitalWrite(yello, yellowState);
  digitalWrite(red, redState);
}

void writeToMatLab(float number) {
  byte *b = (byte *)&number;
  Serial.write(b, 4);
  Serial.write(13);
  Serial.write(10);
}

float readFromMatlab() {
  int rein = Serial.readBytesUntil('\n', buf, buffer_size);
  for (int i = 0; i < buffer_size; i++) {
    u.b[i] = buf[i];
  }
  return u.fval;
}
