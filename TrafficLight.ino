// Damon Nguyen 
// ---------------------------------------------------
// Traffic light with count-down bar-led
// ---------------------------------------------------


// LED Pins
int ledRed = 9;
int ledGreen = 10;
int ledYellow = 11;

// Bar Graph Pins (connected to pins 2 to 8)
int barGraphPins[] = {2, 3, 4, 5, 6, 7, 8};
int barCount = 7;

void setup() {
  // Set traffic light pins as OUTPUT
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  // Set bar graph pins as OUTPUT
  for (int i = 0; i < barCount; i++) {
    pinMode(barGraphPins[i], OUTPUT);
  }
}

void loop() {
  // RED light — 8 seconds countdown
  digitalWrite(ledRed, HIGH);                         // Turn on RED light
  countdownBarGraphBySeconds(8);                      // Start 8-second countdown on bar graph
  digitalWrite(ledRed, LOW);                          // Turn off RED light

  // Bar charge-up before GREEN light (represents green light duration)
  clearBarGraph();                                    // Reset bar LEDs
  delay(100);                                         // Small delay before charge-up
  chargeUpBarQuick(7, 1000);                          // Charge bar to 7 segments in 1 second (right to left)

  // GREEN light — 7 seconds countdown
  digitalWrite(ledGreen, HIGH);                       // Turn on GREEN light
  countdownBarGraphBySeconds(7);                      // Start 7-second countdown
  digitalWrite(ledGreen, LOW);                        // Turn off GREEN light

  // Bar charge-up before YELLOW light
  clearBarGraph();
  delay(100);
  chargeUpBarQuick(3, 1000);                          // Charge bar to 3 segments for yellow light duration

  // YELLOW light — 3 seconds countdown
  digitalWrite(ledYellow, HIGH);
  countdownBarGraphBySeconds(3);
  digitalWrite(ledYellow, LOW);

  // Bar charge-up before RED light
  clearBarGraph();
  delay(100);
  chargeUpBarQuick(8, 1000);                          // Charge bar to 8 segments for red light duration
}

// Lights up bar LEDs and turns off one each second to count down, starting from right to left
void countdownBarGraphBySeconds(int durationSeconds) {
  int displaySeconds = min(durationSeconds, barCount);

  clearBarGraph();                                    // Ensure all LEDs start OFF

  // Light up LEDs for full countdown
  for (int i = 0; i < displaySeconds; i++) {
    int index = barCount - 1 - i;                     // Right to left
    digitalWrite(barGraphPins[index], HIGH);
  }

  // Turn off one LED each second (countdown effect)
  for (int i = 0; i < displaySeconds; i++) {
    delay(1000);                                      // Wait 1 second
    int index = barCount - displaySeconds + i;        // LEDs turn off left to right
    digitalWrite(barGraphPins[index], LOW);
  }
}

// Quickly charges the bar LEDs from right to left based on given number of bars and total delay
void chargeUpBarQuick(int targetBars, int totalDelayMs) {
  int barsToLight = min(targetBars, barCount);
  int delayPerBar = totalDelayMs / barsToLight;       // Delay between each LED turning on

  for (int i = 0; i < barsToLight; i++) {
    int index = barCount - 1 - i;                     // Right to left
    digitalWrite(barGraphPins[index], HIGH);
    delay(delayPerBar);
  }
}

// Turns off all LEDs in the bar graph
void clearBarGraph() {
  for (int i = 0; i < barCount; i++) {
    digitalWrite(barGraphPins[i], LOW);
  }
}
