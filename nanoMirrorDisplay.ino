// jomwells
// code to operate the power button of a display inside a Smart Mirror
// using a PIR sensor in the side to wake (wave gesture), and one at the front to keep awake when someone is in front

int powerbutton = 13;         // output for power button D7
int sidepirsensor = 5;        // input (digital) for PIR pin D2
int frontpirsensor = 3;       // input (digital) for PIR pin D3
int displaysensor = A4;       // input (Analog) for display Sensor A0
int displaydigitalout = 10;   // output (digital) for display sensor D8
int displayval = 0;           // measurements of display sensor
int sidepirval = 0;           // measurements of side PIR sensor
int frontpirval = 0;          // measurements of front PIR sensor
int buttondelay = 100;        // length (time) of button presses [milliseconds]
int powerondelay = 4000;      // delay time for screen to turn on [milliseconds]
int poweroffdelay = 500;      // delay time for screen to turn off [milliseconds]
int displayontime = 20;       // time for which sceeen stays awale after each detection [seconds]
int resetcooldown = 4;        // time fot timer reset cool down [seconds]
int waitafterpoweroff = 4000; // time to wait after powering screen off before continuing [milliseconds]

unsigned long last_event = 0;  // variable for saving time code of last PIR sensor detection
unsigned long last_reset = 0;  // variable for saving time code of last timer reset

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(powerbutton, OUTPUT);      // initalize powerbutton as an output
  pinMode(displaydigitalout, OUTPUT);      // initalize display power pin as an output
  pinMode(sidepirsensor, INPUT);     // initialize side PIR sensor as an input
  pinMode(frontpirsensor, INPUT);    // initialize front PIR sensor as an input
  pinMode(displaysensor, INPUT);     // initialize display sensor as an input
  digitalWrite(displaydigitalout, HIGH);
  // ectract of main loop for determining starting condions

  displayval = analogRead(displaysensor);
  sidepirval = digitalRead(sidepirsensor);
  frontpirval = digitalRead(frontpirsensor);

  if (displayval > 450){ // if the display is on

    if (frontpirval == HIGH){ // if the display is on & motion is detected ****!!! change to front !!!****
      Serial.println("Display is already ON");
      Serial.println("Motion Detected! - Timer Restarted");
      last_event = millis(); // starts timer
      last_reset = millis(); // starts reset timer
      }
    if (frontpirval == LOW){ // if the display is on & motion is not detected ****!!! change to front !!!****
      Serial.println("Display is already ON");
      Serial.println("Timer Restarted Anyway");
      last_event = millis(); // starts timer
      last_reset = millis(); // starts reset timer
    }
  }

  if (displayval < 450){ // if the display is off

    if (sidepirval == HIGH){ // if the display is off & motion is detected
      Serial.println("Motion Detected!");
      power_on();
      last_event = millis(); // starts timer
      Serial.println("Timer Started");
      }
    if (sidepirval == LOW){ // if the display is off & motion is not detected
      Serial.println("Display is OFF");
      // do nothing
    }
  }

  // end extract
}

void loop() { // ********** main loop beigns **********

  displayval = analogRead(displaysensor);
  sidepirval = digitalRead(sidepirsensor);
  frontpirval = digitalRead(frontpirsensor);

  if (displayval > 450){ // if the display is on

    if (frontpirval == HIGH){ // if the display is on & motion is detected ****!!! change to front !!!****
      if ( millis() > (last_reset + (resetcooldown*1000)) ) {
        Serial.println("Motion Detected! - Timer Restarted");
        last_event = millis(); // starts timer
        last_reset = millis(); // starts reset timer
       }
     }
    if (frontpirval == LOW){ // if the display is on & motion is not detected ****!!! change to front !!!****
      // do nothing
    }

    if (millis() > (last_event + (displayontime*1000))){ // if the timer has run out
      Serial.println("Timer Ended");
      power_off();
      }
  }

  if (displayval < 450){ // if the display is off

    if (sidepirval == HIGH){ // if the display is off & motion is detected
      Serial.println("Motion Detected!");
      power_on();
      last_event = millis();
      last_reset = millis();
      Serial.println("Timer Started");
      }
    if (sidepirval == LOW){ // if the display is off & motion is not detected
      // do nothing
    }
  }
}



void power_on() { // Function to Power ON

  displayval = analogRead(displaysensor);
  if (displayval < 450){
  digitalWrite(powerbutton, HIGH);
  delay(buttondelay);
  digitalWrite(powerbutton, LOW);
  delay(powerondelay);
  Serial.println("Display Turned ON");
  }
  else {
  Serial.println("Error! Display is already ON"); // error flag if power_on ran when power is already on
  }

}

void power_off() { // Function to Power Off

  displayval = analogRead(displaysensor);
  if (displayval > 450){
  digitalWrite(powerbutton, HIGH);
  delay(buttondelay);
  digitalWrite(powerbutton, LOW);
  delay(poweroffdelay);
  Serial.println("Display Turned OFF");
  delay(waitafterpoweroff);
  }
  else {
  Serial.println("Error! Display is already OFF"); // error flag if power_off ran when power is already off
  }
}
