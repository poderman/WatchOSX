//This is for displaying and running the stopwatch feature on the watch.

int Stopwatch_On = 0; //0 = stopwatch off, 1 = stopwatch on.

const unsigned long SW_interval = 1000;  // Time interval in milliseconds
unsigned long SW_previousMillis = 0;    // Store the last time an action was taken

int SW_Seconds = 0;
int SW_Minutes = 0;
int SW_Hours = 0;

void StopwatchManager()
{
  if (Stopwatch_On == 1)
  {
    //Waits a second so that the Stopwatch works!!
    unsigned long SW_currentMillis = millis();  // Get the current time

    // Check if the desired interval has passed
    if (SW_currentMillis - SW_previousMillis >= interval) 
    {
      // Save the current time for the next interval
      SW_previousMillis = SW_currentMillis;

      SW_Seconds += 1;
      if (SW_Seconds == 60)
      {
        SW_Seconds = 0;
        SW_Minutes += 1;
      } 
      if (SW_Minutes == 60)
      {
        SW_Minutes = 0;
        SW_Hours += 1;
      }
    }
  }
}

void ShowStopwatch()
{
  if (ButtonSelect == 1)
  {
    if (Stopwatch_On == 0)
    {
      Stopwatch_On = 1;
    }
    else if (Stopwatch_On == 1)
    {
      Stopwatch_On = 0;
    }
  }

  
  // Clear the buffer
  display.clearDisplay();

  // Set text color
  display.setTextColor(SSD1306_WHITE);

  //This is displaying StopWatch on the top of the display.
  display.setTextSize(2);
  display.setCursor(11, 0);
  display.print("StopWatch");

  // Set the cursor position and display
  display.setTextSize(3);
  display.setCursor(21, 20);
  if (SW_Hours < 10)
  {
    display.print("0");
  }
  display.print(SW_Hours);
  display.print(":");
  if (SW_Minutes < 10)
  {
    display.print("0");
  }
  display.print(SW_Minutes);
  //display.print(":");
  
  display.setTextSize(2);
  display.setCursor(55, 50);
  if (SW_Seconds < 10)
  {
    display.print("0");
  }
  display.print(SW_Seconds);

  // Display the buffer contents
  display.display();
}
