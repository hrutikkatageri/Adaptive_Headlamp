
/*
  Project: Adaptive Matrix Headlamp System
  Board: Arduino UNO

  Input:
    LDR sensor -> A0

  Outputs:
    Matrix LED 1 -> D3
    Matrix LED 2 -> D5
    Matrix LED 3 -> D6

  Function:
    LEDs turn ON in darkness.
    LEDs turn OFF when sufficient ambient
    light is detected.
*/

const int LDR_PIN = A0;

const int LED1_PIN = 3;
const int LED2_PIN = 5;
const int LED3_PIN = 6;

// Adjust this value after checking sensor readings.
const int LIGHT_THRESHOLD = 500;

// Hysteresis prevents rapid switching near threshold.
const int DARK_THRESHOLD = 470;
const int BRIGHT_THRESHOLD = 530;

bool headlampOn = false;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  Serial.begin(9600);

  // Start with all LEDs switched off.
  setHeadlamp(false);

  Serial.println("Adaptive Matrix Headlamp System");
  Serial.println("System initialized");
}

void loop() {
  int lightValue = analogRead(LDR_PIN);

  Serial.print("LDR Reading: ");
  Serial.print(lightValue);

  // Lower readings indicate darkness with
  // the specified LDR voltage-divider wiring.
  if (lightValue < DARK_THRESHOLD) {
    headlampOn = true;
  }
  else if (lightValue > BRIGHT_THRESHOLD) {
    headlampOn = false;
  }

  setHeadlamp(headlampOn);

  Serial.print(" | Headlamp: ");
  Serial.println(headlampOn ? "ON" : "OFF");

  delay(200);
}

void setHeadlamp(bool state) {
  digitalWrite(LED1_PIN, state ? HIGH : LOW);
  digitalWrite(LED2_PIN, state ? HIGH : LOW);
  digitalWrite(LED3_PIN, state ? HIGH : LOW);
}
