//Version 0.1

//WatchOSX was developed for the Seeeduino XIAO using a 0.96 inch oled but could possible work on
//other Arduinos. This is a open source project and all the files, photos, code and information on this
//project can be found on my Github https://github.com/poderman/WatchOSX

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

const unsigned long interval = 1000;  // Time interval in milliseconds
unsigned long previousMillis = 0;    // Store the last time an action was taken

int Year = 2023;
int Month = 8;
int Day = 10;
int Hours = 20;
int Minutes = 23;
int Seconds = 0;

// 1 = Clock. 2 = StopWatch. 3 = Light.
int CurrentDisplay = 1;

//This is for setting up the left button on the watch.
const int LeftButton = 2;
int LeftButton_ButtonState = 0;
int PreviousLeftButton_ButtonState = 0;

//This is for setting up the right button on the watch.
const int RightButton = 3;
int RightButton_ButtonState = 0;
int PreviousRightButton_ButtonState = 0;

int ButtonSelect = 0;

int Can_Switch_Display = 0; //0 = can switch, 1 = can not switch.

const int ledPin =  7;      // the number of the LED pin

//int Stopwatch_On = 0; //0 = stopwatch off, 1 = stopwatch on.


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{
  Serial.begin(9600);
  
  // Initialize the OLED display with the I2C address
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the buffer
  display.clearDisplay();

  pinMode(LeftButton, INPUT);
  pinMode(RightButton, INPUT);
  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //This has to always go first in the loop
  ButtonManager();
  
  TimeManager();
  StopwatchManager();

  //This is for choosing what display to display
  if (CurrentDisplay == 1)
  {
    ShowTime();
  }
  else if (CurrentDisplay == 2)
  {
    ShowStopwatch();
  }
  else if (CurrentDisplay == 3)
  {
    ShowFlashLight();
  }


  ButtonSelect = 0;
}


void ButtonManager()
{
  //This is for both buttons
  LeftButton_ButtonState = digitalRead(LeftButton);
  RightButton_ButtonState = digitalRead(RightButton);

  if (LeftButton_ButtonState == LOW && PreviousLeftButton_ButtonState == HIGH && RightButton_ButtonState == HIGH)
  {
    ButtonSelect = 1;
  }
  else if (RightButton_ButtonState == LOW && PreviousRightButton_ButtonState == HIGH && LeftButton_ButtonState == HIGH)
  {
    ButtonSelect = 1;
  }
  else if (LeftButton_ButtonState == LOW && PreviousLeftButton_ButtonState == HIGH && RightButton_ButtonState == LOW && PreviousRightButton_ButtonState == HIGH)
  {
    ButtonSelect = 1;
  }
  

  if (LeftButton_ButtonState == HIGH && RightButton_ButtonState == HIGH)
  {
    Can_Switch_Display = 1;
  }
  
  //This is for the LeftButton
  if (LeftButton_ButtonState == LOW && PreviousLeftButton_ButtonState == HIGH && Can_Switch_Display == 0)
  {
    CurrentDisplay -= 1;

    if (CurrentDisplay < 1)
    {
      CurrentDisplay = 3;
    }
  }

  //This is for the RightButton
  if (RightButton_ButtonState == LOW && PreviousRightButton_ButtonState == HIGH && Can_Switch_Display == 0)
  {
    CurrentDisplay += 1;

    if (CurrentDisplay > 3)
    {
      CurrentDisplay = 1;
    }
  }

  if (LeftButton_ButtonState == LOW && RightButton_ButtonState == LOW)
  {
    Can_Switch_Display = 0;
  }
  
  PreviousLeftButton_ButtonState = LeftButton_ButtonState;
  PreviousRightButton_ButtonState = RightButton_ButtonState;
}
