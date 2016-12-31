/* This is the code for project Aumi, a DIY portable color changing night light
 * made by Sachin Soni.
 *
 * If you want to know in detail aboout this project, goto website
 * www.techiesms.com
 * here you'll find link for DIY videos.
 *
 *  Components require for this project:-
 *
 *  - Arduino Pro mini
 *  - HC-05 Bluetooth module
 *  - Rotary Encoder
 *  - RGB LED Strip
 *
 *
 *
 *         techiesms
 *  explore | learn | share
 */

// pins for all the components
#define redPin 3
#define greenPin 5
#define bluePin 6
#define clk 7
#define dt 8


int r = 0;
int g = 0;
int b = 0;
int rr = 0;
int gg = 0;
int bb = 0;
int now = 0;
int previous = 0;
int counter = 0;

void setup()
{
  //Enabling Serial communication at 9600  baudrate
  Serial.begin(9600); // Baud rate = 9600

  //Declaring Input/Output pins
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initial Testing for LEDs
  setColor(255, 0, 0); // Red
  delay(500);
  setColor(0, 255, 0); // Green
  delay(500);
  setColor(0, 0, 255); // Blue
  delay(500);
  setColor(255, 255, 255); /// White (Almost)

  previous = digitalRead(clk);
}


void loop()
{
  // If anything is received from bluetooth device
  while (Serial.available() > 0)
  {

    // Seperating values for Red, Green and Blue
    int redInt = Serial.parseInt();
    int greenInt = Serial.parseInt();
    int blueInt = Serial.parseInt();

    // Limiting the values between 0 to 255
    redInt = constrain(redInt, 0, 255);
    greenInt = constrain(greenInt, 0, 255);
    blueInt = constrain(blueInt, 0, 255);

    // again checking If anything is received from bluetooth device
    if (Serial.available() > 0)
    {
      // Set the received colors to output pin of LED Strip
      setColor(redInt, greenInt, blueInt);

    }
  }

// This is the logic to increase and decrease brightness using rotary encoder
  now = digitalRead(clk);


  if (now != previous)
  {
    if (digitalRead(dt) != now)
    {
      if (counter >= 255);
      else
      {
        rr = (255 - r) / (51 - (counter / 5));
        gg = (255 - g) / (51 - (counter / 5));
        bb = (255 - b) / (51 - (counter / 5));


        analogWrite(redPin, r += rr);
        analogWrite(greenPin, g += gg);
        analogWrite(bluePin, b += bb);
        counter += 5;
      }
     
    }
    else
    {
      if (counter <= 0);
      else
      {

        analogWrite(redPin, r -= rr);
        analogWrite(greenPin, g -= gg);
        analogWrite(bluePin, b -= bb);
        counter -= 5;
      }
      

    }

    previous  = now;
  }
}

void setColor(int red, int green, int blue)
{
  // Doing this subtraction because my LED strip is common anode 
  r = 255 - red;
  g = 255 - green;
  b = 255 - blue;
  // Resetting all variables 
  rr = 0;
  gg = 0;
  bb = 0;
  counter = 0;

  // writing the received color 
  analogWrite(redPin, r);
  analogWrite(greenPin,g);
  analogWrite(bluePin,b);

}
