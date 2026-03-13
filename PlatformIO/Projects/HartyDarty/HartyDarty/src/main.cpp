/**
Documentation block
03/04/26 - RH - Modified HTML code to look better
03/12/26 - RH - Cleaned up comments and created separate file for File mangement/logging
03/13/26 - LT - Forked from "Code" branch to create this simplified branch for easy testing of functions




**/
#include <Arduino.h>
#include <Adafruit_LSM6DSO32.h>
#include <MS5611.h>
#include <test_functions.h>

// Check that all components are up and running

// Init IMU
Adafruit_LSM6DSO32 dso32;

// Set I2C adress for barometer - Ignore any error here relating to "not a class name"
MS5611 MS5611(0x77);
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp2;

// Define pins for continuity testing
// NOTE! Reflects ports on final flight computer, not breadboard computer!
#define ig1 2
#define cont1 1
#define ig2 4
#define cont2 3
#define ig3 9
#define cont3 8


void setup(void) {
  Serial.begin(115200);
  delay(100); // will pause Zero, Leonardo, etc until serial console opens

  // All sensor initializations offloaded to 
  sensor_init(dso32,MS5611);

  //Setup PinModes for continuity testing
  //Setting low for continuity testing

  // Mostfet 1
  analogSetPinAttenuation(cont1,ADC_11db);
  pinMode(ig1,OUTPUT);
  pinMode(cont1,INPUT);
  digitalWrite(ig1,LOW); // Sets mosfet, LOW means off, HIGH means on
  float ADC = 0;
  // Mostfet 2
  analogSetPinAttenuation(cont2,ADC_11db);
  pinMode(ig2,OUTPUT);
  pinMode(cont2,INPUT);
  digitalWrite(ig2,LOW); // Sets mosfet, LOW means off, HIGH means on
  // Mosfet 3
  analogSetPinAttenuation(cont3,ADC_11db);
  pinMode(ig3,OUTPUT);
  pinMode(cont3,INPUT);
  digitalWrite(ig3,LOW); // Sets mosfet, LOW means off, HIGH means on

  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(115200);
  Serial.println();
}

void loop() {
  // Prints sensor data (Commented out for now)
  data_print_test(dso32,MS5611,1);
  
  // Tests continuity
  // Turn the GPIO ports for ignition and continuity into integer arrays for input to function
  int ig[3]={ig1,ig2,ig3};
  int cont[3]={cont1,cont2,cont3};
  // continuity_test(0,ig,cont); // Commented out for ease of testing

  // NOTE: Below code may be redundant, commented out for now but delete if confirmed redundant with testing 
/*   float zG = accel.acceleration.z;
  float xG = accel.acceleration.x;
  float yG = accel.acceleration.y;

  float gyroX = gyro.gyro.x;
  float gyroY = gyro.gyro.y;
  float gyroZ = gyro.gyro.z;

  dso32.getEvent(&accel, &gyro, &temp2); // Gets data from IMU */
  // End Note!
}