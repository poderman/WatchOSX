void ShowFlashLight()
{
  if (ButtonSelect == 1)
  {
    if (digitalRead(ledPin) == HIGH)
    {
      digitalWrite(ledPin, LOW);
    }
    else
    {
      digitalWrite(ledPin, HIGH);
    }
  }

  display.clearDisplay();

  // Set text size and color
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 30);
  display.print("FlashLight");

  display.display();
}
