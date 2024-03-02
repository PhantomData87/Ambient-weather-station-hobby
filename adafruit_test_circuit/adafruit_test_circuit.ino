// Consumption:
// @ 0.865A with 5.1V

int led = 13;
int mainled = 12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led, OUTPUT);
  pinMode(mainled, OUTPUT);
}
// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(mainled, LOW);  // turn the LED off (LOW is the voltage level)
  delay(2000);  // wait for a second
  digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
  digitalWrite(mainled, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(2000); // wait for a second
}
