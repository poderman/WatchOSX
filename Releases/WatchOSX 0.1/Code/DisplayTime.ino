void TimeManager()
{
  //Waits a second so that the clock works!!
  unsigned long currentMillis = millis();  // Get the current time

  // Check if the desired interval has passed
  if (currentMillis - previousMillis >= interval) 
  {
    // Save the current time for the next interval
    previousMillis = currentMillis;

    Seconds += 1;
    if (Seconds == 60)
    {
      Seconds = 0;
      Minutes += 1;
    } 
    if (Minutes == 60)
    {
      Minutes = 0;
      Hours += 1;
    }
    if (Hours == 25)
    {
      Hours = 1;
      Day += 1;
    }
    if (Day > 31) //This still needs some work so that it can work with the different amounts of days in a month and leap years.
    {
      Day = 1;
      Month += 1;
    }
    if (Month > 12)
    {
      Month = 1;
      Year += 1;
    }
  }
}


void ShowTime()
{
  // Clear the buffer
  display.clearDisplay();

  // Set text color
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(19, 5);
  display.print("D:");
  display.print(Day);
  
  display.print(" M:");
  display.print(Month);

  display.print(" Y:");
  display.print(Year);
  

  display.setTextSize(3);
  display.setCursor(20, 20);
  if (Hours < 10)
  {
    display.print("0");
  }
  display.print(Hours);
  display.print(":");
  if (Minutes < 10)
  {
    display.print("0");
  }
  display.print(Minutes);
  //display.print(":");
  
  display.setTextSize(2);
  display.setCursor(55, 50);
  if (Seconds < 10)
  {
    display.print("0");
  }
  display.print(Seconds);

  // Display the buffer contents
  display.display();
}
