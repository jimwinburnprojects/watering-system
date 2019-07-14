#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
//#include <Adafruit_SSD1306.h>

// Define OLED object
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET 4
//#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define constant for RTC I2C Address
#define DS1307_CTRL_ID 0x68

// Define range constants for Moisture Sensor
const int wetProbe      = 300;   // wet readings are around 1.5v or analog input value ~300
const int dryProbe      = 620;   // dry readings are around   3v or analog input value ~620
// Moisture Sensor Input Pin
int sensorInput0         = 0;    // soil probe is on analog input 0
int sensorInput1         = 1;    // soil probe is on analog input 1
int sensorInput2         = 2;    // soil probe is on analog input 2

// Moisture Sensor varibles
int validSensorReading  = 0;    // valid sensor analog reading to record
int sensorReading;              // new sensor reading to evaluate and record or discard
int sensorResult;               // scaled sensor data [0..3] = [wet, damp, moist, dry]

// Timer constants
const int OnHour = 19;
const int OffHour = 20;


String disTime;
String moisture0;
String moisture1;
String moisture2;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  
  // Init OLED Display
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C address of the display
  //display.clearDisplay();  

  // Set up pump ports
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
}

void loop() {

  
  
  getMoisture0();
  getMoisture1();
  getMoisture2();
  
      
  tmElements_t tm;

  if (RTC.read(tm)) {
    
    disTime = String(tm.Hour) + ':' + String(tm.Minute) + ":" + String(tm.Second);

        
    Serial.println(disTime);
    Serial.println(moisture0);
    Serial.println(moisture1);
    Serial.println(moisture2);

  if(tm.Hour == OnHour){ // check for 7 to 8 pm
      digitalWrite(LED_BUILTIN,HIGH);

  // check sensor
        if (moisture0 == "Dry" ) {
          //turn  pump on
          digitalWrite(3,HIGH);          
        }else{
          digitalWrite(3,LOW);
        }

        if (moisture1 == "Dry") {
          //turn  pump on
          digitalWrite(4,HIGH);          
        } else {
          digitalWrite(4,LOW);
        }

        if (moisture2 == "Dry") {
          //turn  pump on
          digitalWrite(5,HIGH);          
        } else {
          digitalWrite(5,LOW);
        }
  } else if(tm.Hour == OffHour){
        digitalWrite(LED_BUILTIN,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
      }// check for 7 to 8 pm

   

      
    
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    } 
    //delay(1000);
  }
  
  delay(500);
 
   
} // end of void loop

// Functions-------------------------------------------

// Print Sensor Readngs
void getMoisture0() {

  // Read moisture with noise reduction
    sensorReading = analogRead(sensorInput0);
      if (abs(validSensorReading - sensorReading) > 10) {
      validSensorReading = sensorReading;
      }
    
    sensorResult = map(validSensorReading, wetProbe, dryProbe, 0, 4);  // scale analog input to a smaller range for wet to dry

    
    // display the correct soil moisture level on the display
    // lower voltages represent more wet levels
    switch (sensorResult) {
      case 0:
        moisture0 = "Wet";
        break;
      case 1:
        moisture0 = "Damp";
        break;
      case 2:
        moisture0 = "Moist";
        break;
      case 3:
        moisture0 = "Dry";
        break;
      case 4:    // same as case 3, due to how map works.
        moisture0 = "Dry";
        break;
    }
    //delay(100);
}

void getMoisture1() {

  // Read moisture with noise reduction
    sensorReading = analogRead(sensorInput1);
      if (abs(validSensorReading - sensorReading) > 10) {
      validSensorReading = sensorReading;
      }
    
    sensorResult = map(validSensorReading, wetProbe, dryProbe, 0, 4);  // scale analog input to a smaller range for wet to dry

    
    // display the correct soil moisture level on the display
    // lower voltages represent more wet levels
    switch (sensorResult) {
      case 0:
        moisture1 = "Wet";
        break;
      case 1:
        moisture1 = "Damp";
        break;
      case 2:
        moisture1 = "Moist";
        break;
      case 3:
        moisture1 = "Dry";
        break;
      case 4:    // same as case 3, due to how map works.
        moisture1 = "Dry";
        break;
    }
    //delay(100);
}

void getMoisture2() {

  // Read moisture with noise reduction
    sensorReading = analogRead(sensorInput2);
      if (abs(validSensorReading - sensorReading) > 10) {
      validSensorReading = sensorReading;
      }
    
    sensorResult = map(validSensorReading, wetProbe, dryProbe, 0, 4);  // scale analog input to a smaller range for wet to dry

    
    // display the correct soil moisture level on the display
    // lower voltages represent more wet levels
    switch (sensorResult) {
      case 0:
        moisture2 = "Wet";
        break;
      case 1:
        moisture2 = "Damp";
        break;
      case 2:
        moisture2 = "Moist";
        break;
      case 3:
        moisture2 = "Dry";
        break;
      case 4:    // same as case 3, due to how map works.
        moisture2 = "Dry";
        break;
    }
    //delay(100);
}
