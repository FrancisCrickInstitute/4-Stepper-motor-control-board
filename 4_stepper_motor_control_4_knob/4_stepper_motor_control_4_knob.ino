#include "TeensyStep.h"
#include <Encoder.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Encoder knob(26, 27);
Encoder knob_2(23, 24);
Encoder knob_3(20, 21);
Encoder knob_4(15, 16);

const int encoder_SW = 25;
const int encoder_SW_2 = 22;
const int encoder_SW_3 = 17;
const int encoder_SW_4 = 14;

const int Enable = 2;
const int Enable_2 = 5;
const int Enable_3 = 8;
const int Enable_4 = 11;

Stepper pump(3, 4);       // STEP pin: 7, DIR pin: 6  // The stepper class encapsulates the physical properties of a stepper motor like pin numbers of the STEP and DIR signals, speed and acceleration of the motor.
Stepper pump_2(6, 7);
Stepper pump_3(9, 10);  
Stepper pump_4(12, 13);  

//StepControl step_controller;    // The StepControl class is used to synchronously move up to 10 motors to their target positions.
RotateControl rotate_controller; // The RotateControl class is used to synchronously rotate up to 10 motors.
RotateControl rotate_controller_2;
RotateControl rotate_controller_3;
RotateControl rotate_controller_4;

int speed_ = 0;
int speed_2 = 0;
int speed_3 = 0;
int speed_4 = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MS1 = 28;
const int MS2 = 29;
const int MS3 = 30;

float flow_rate;
float flow_rate_2;
float flow_rate_3;
float flow_rate_4;

void setup()
{
  pinMode(MS1, OUTPUT);    // set the MS1, MS2, MS3 and Enable as an outputs
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  
  pinMode(Enable, OUTPUT);
  pinMode(Enable_2, OUTPUT);
  pinMode(Enable_3, OUTPUT);
  pinMode(Enable_4, OUTPUT);

  digitalWrite(MS1, HIGH); // sets the digital pin MS1, MS2, MS3 to HIGH
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  
  digitalWrite(Enable, LOW); // set the enables to LOW
  digitalWrite(Enable_2, LOW); 
  digitalWrite(Enable_3, LOW); 
  digitalWrite(Enable_4, LOW); 
  
  // Set the motor max acceleration
  pump.setAcceleration(1000)   // stp/s^2
      .setInverseRotation(true);

  pump_2.setAcceleration(1000)   // stp/s^2
      .setInverseRotation(true);

  pump_3.setAcceleration(1000)   // stp/s^2
      .setInverseRotation(true);
      
  pump_4.setAcceleration(1000)   // stp/s^2
      .setInverseRotation(true);
      
  pinMode(encoder_SW, INPUT_PULLUP);
  
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(1000); 
  display.clearDisplay();
}

void loop() 
{ 

  speed_ = knob.read();
  speed_2 = knob_2.read();
  speed_3 = knob_3.read();
  speed_4 = knob_4.read();
  
  //Serial.println(speed_);
  pump.setMaxSpeed(speed_);
  pump_2.setMaxSpeed(speed_2);
  pump_3.setMaxSpeed(speed_3);
  pump_4.setMaxSpeed(speed_4);
  
  //Serial.println(speed_);
  rotate_controller.overrideSpeed(speed_);
  rotate_controller_2.overrideSpeed(speed_2);
  rotate_controller_3.overrideSpeed(speed_3);
  rotate_controller_4.overrideSpeed(speed_4);
  
  //rotate_controller.rotateAsync(pump, pump_2, pump_3, pump_4);
  rotate_controller.rotateAsync(pump);
  rotate_controller_2.rotateAsync(pump_2);
  rotate_controller_3.rotateAsync(pump_3);
  rotate_controller_4.rotateAsync(pump_4);
  

  flow_rate = 0.004*speed_;
  flow_rate_2 = 0.004*speed_2;
  flow_rate_3 = 0.004*speed_3;
  flow_rate_4 = 0.004*speed_4;
  
  //flow_rate =speed_;
  //Serial.print(flow_rate);
  //Serial.println("mL/min");
  
   display.clearDisplay();
   display.setTextColor(WHITE);        // Draw white text
   display.setCursor(0, 0);
   display.setTextSize(1);
   display.print(flow_rate);
   display.println(F(" mL/min"));
   display.println(" ");
   display.setCursor(0, 15);
   display.print(flow_rate_2);
   display.println(F(" mL/min"));
   display.println(" ");
   display.setCursor(0, 30);
   display.print(flow_rate_3);
   display.println(F(" mL/min"));
   display.println(" ");
   display.setCursor(0, 45);
   display.print(flow_rate_4);
   display.println(F(" mL/min"));
   display.println();
   display.display(); 
}
