/**
  ******************************************************************************
    @file     ePaper_library_test
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     02-January-2024
    @modified 16-Feburary-2024
    @brief    A sketchpad to test the various functions that I had written. Let's see if these "tests" are at all helpful for the likes of you
    @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere
    @mention  If you have questions on why things are defined the way they are. Feel free to read "README.md" to obtain some answers.
    @stats    At the time of writing. This program when barely initialized takes up 182 bytes of memory, and 1484 bytes in "program storage space"
*/

#include "epdConf.h"
epd epd;

void setup()
{
  // Turn on the screen
  SerialUSB.begin(9600);
  epd.turnOn();

  // Ensure we have a fresh screen & Start the testing
  epd.clearScreen();
  screenTest();

  // Shutdown test
  epd.turnOff();
  SerialUSB.println("Off");
}

// Unnecesarry main loop, but cannot remove it
void loop() {
}

/*
  A simple function that will test the screen in it's behavior when running this library. These were test that can from the top of my head so it's likely their is more testing that can be done
  It also serves as a self learning tutorial of how to use this library
*/
void screenTest() {
  // Variables defined
  float someNum = 10.249;
  unsigned char* testing = (unsigned char *)"Testing"; // Readability

  // Pixel test; See if rounding error occurs.
  SerialUSB.println("Testing pixel accuracy");
  epd.drawRectangleArea(16, 21, 1, 1);
  epd.drawRectangleArea(15, 22, 1, 1);
  epd.drawRectangleArea(14, 23, 1, 1);
  epd.drawRectangleArea(13, 24, 1, 1);

  // Draw basic permimeter test
  SerialUSB.println("Testing basic shapes");
  epd.drawRectangleArea(15, 10, 10, 10);
  epd.drawCircle(32, 100, 3); // 7 pixel widths

  // Rotation test
  SerialUSB.println("Testing rotation");
  epd.drawCharArray(32, 5, testing, 7, &Font8); // No rotation
  epd.switchXRotation();
  epd.drawCharArray(33, 20, testing, 7, &Font8); // X rotation
  epd.switchXRotation();
  epd.switchYRotation();
  epd.drawCharArray(34, 45, testing, 7, &Font8); // Y rotation
  epd.switchXRotation();
  epd.drawCharArray(35, 60, testing, 7, &Font8); // X & Y rotation
  epd.switchXRotation();

  // Inverse test
  SerialUSB.println("Testing inverse colors");
  epd.drawCharArray(36, 75, testing, 7, &Font8); // No inverse
  epd.invertColorSelection();
  epd.drawCharArray(39, 90, testing, 7, &Font8); // With inverse
  epd.drawCharArray(40, 102, testing, 7, &Font8); // Show pixel precision
  epd.invertColorSelection();
  epd.switchYRotation();

  // Shape filled test
  SerialUSB.println("Filled shape test");
  // Circle
  epd.drawCircle(134, 14, 3); // 7 pixel widths
  epd.drawCircle(134, 44, 3, 5); // 10 pixel circumference + 7 pixel circumference
  epd.switchFilled();
  epd.drawCircle(134, 64, 3); // 7 pixel widths
  epd.drawCircle(134, 94, 3, 5); // 10 pixel circumference + 7 pixel circumference
  epd.switchFilled();
  // Rectangle
  epd.drawRectangleArea(100, 120, 8, 10);
  epd.switchFilled();
  epd.drawRectangleArea(100, 131, 8, 10); // Should be 1 pixel away
  epd.switchFilled();

  // Display the progress
  epd.displayFrame();
  epd.sleepScreen();
  SerialUSB.println("Printed full refresh drawings. First sleep performed");
  delay(2000);
  SerialUSB.println("Awakening screen");
  // Turning back on test & clear screen
  epd.awakeScreen();
  epd.clearScreen();

  // Draw partial test
  SerialUSB.println("Testing partial refresh now");
  epd.changeRefreshType();
  // Circle
  epd.drawCircle(44, 54, 3); // 7 pixel widths
  epd.drawCircle(72, 54, 3, 5); // 10 pixel circumference + 7 pixel circumference
  epd.switchFilled();
  epd.displayFrame(); // Invoke partial refresh
  epd.drawCircle(44, 85, 3); // 7 pixel widths
  epd.drawCircle(72, 85, 3, 5); // 10 pixel circumference + 7 pixel circumference
  epd.switchFilled();
  epd.displayFrame(); // Invoke partial refresh
  // Rectangle
  epd.drawRectangleArea(120, 120, 8, 10);
  epd.switchFilled();
  epd.displayFrame(); // Invoke partial refresh
  epd.drawRectangleArea(120, 131, 8, 10); // Should be 1 pixel away
  epd.switchFilled();
  epd.displayFrame(); // Invoke partial refresh

  // Sleeping the screen
  epd.changeRefreshType();
  epd.sleepScreen();
  SerialUSB.println("Printed partial refresh drawings. Second sleep performed");
  delay(500);
  SerialUSB.println("Awakening screen");
  // Turning back on test & clear screen
  epd.awakeScreen();
  epd.clearScreen();

  // Error correction test with some rotation
  SerialUSB.println("Testing error correction");
  epd.switchXRotation();
  epd.switchYRotation();
  epd.invertColorSelection();
  epd.drawRectangleArea(180, 35, 20, 5);
  epd.drawCircle(180, 45, 10); // 21 pixel circumference
  epd.invertColorSelection();
  epd.drawCharArray(175, 70, testing, 7, &Font8); // No rotation
  epd.switchXRotation();
  epd.switchYRotation();
  epd.drawImage(180, 80, &Battery); // A little early, but whatever
  epd.drawRectangleArea(180, 110, 20, 5);
  epd.drawCircle(180, 120, 10); // 21 pixel circumference
  epd.drawCharArray(180, 155, testing, 7, &Font8); // No rotation
  epd.drawCircle(70, 190, 10); // 21 pixel circumference

  // Drawing where "Coordinates" begin and end
  SerialUSB.println("Drawing coordinates. Showing inverse for area");
  epd.invertColorSelection();
  epd.drawCharArray(0, 0, (unsigned char *)"0,0", 3, &Font12);
  epd.drawCharArray(144, 189, (unsigned char *)"199,199", 7, &Font12); // Relying on that error correction for the X coordinate & Y coordinate
  epd.invertColorSelection();

  // Image test & Inverse
  SerialUSB.println("Draw custom images test");
  epd.drawImage(50, 20, &Battery, 1);
  epd.switchXRotation();
  epd.invertColorSelection();
  epd.drawImage(50, 50, &Battery, 2);
  epd.switchYRotation();
  epd.drawImage(50, 80, &Battery, 3);
  epd.invertColorSelection();
  epd.switchXRotation();
  epd.drawImage(50, 110, &Battery, 4);
  epd.switchYRotation();

  // Finish testing
  epd.displayFrame();
  epd.sleepScreen();
  SerialUSB.println("Finish error correction & image drawing. Last sleep performed");
  delay(2000);
}
