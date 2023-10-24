// #include <Arduino.h>
// #include <TinyGPSPlus.h>
// #include <SoftwareSerial.h>

// // Choose two Arduino pins to use for software serial
// int RXPin = 16;
// int TXPin = 17;

// int GPSBaud = 9600;

// // Create a TinyGPS++ object
// TinyGPSPlus gps;

// // Create a software serial port called "gpsSerial"
// SoftwareSerial gpsSerial(RXPin, TXPin, false, 256);

// void setup()
// {
//   // Start the Arduino hardware serial port at 9600 baud
//   Serial.begin(115200);

//   // Start the software serial port at the GPS's default baud
//   gpsSerial.begin(GPSBaud);
// }

// void loop()
// {
//   // This sketch displays information every time a new sentence is correctly encoded.
//   Serial.println(gpsSerial.available());
//   while (gpsSerial.available() > 0) {
//     Serial.println("..");
//     if (gps.encode(gpsSerial.read())) {
//       if (gps.location.isValid()) {
//         Serial.print("Latitude: ");
//         Serial.println(gps.location.lat(), 6);
//         Serial.print("Longitude: ");
//         Serial.println(gps.location.lng(), 6);
//         Serial.print("Altitude: ");
//         Serial.println(gps.altitude.meters());
//       } else {
//         Serial.println("Location: Not Available");
//       }
//       Serial.print("Date: ");
//       if (gps.date.isValid()) {
//         Serial.print(gps.date.month());
//         Serial.print("/");
//         Serial.print(gps.date.day());
//         Serial.print("/");
//         Serial.println(gps.date.year());
//       } else {
//         Serial.println("Not Available");
//       }
//       Serial.print("Time: ");
//       if (gps.time.isValid()) {
//         if (gps.time.hour() < 10) {
//           Serial.print(F("0"));
//         }
//         Serial.print(gps.time.hour());
//         Serial.print(":");
//         if (gps.time.minute() < 10) {
//           Serial.print(F("0"));
//         }
//         Serial.print(gps.time.minute());
//         Serial.print(":");
//         if (gps.time.second() < 10) {
//           Serial.print(F("0"));
//         }
//         Serial.print(gps.time.second());
//         Serial.print(".");
//         if (gps.time.centisecond() < 10) {
//           Serial.print(F("0"));
//         }
//         Serial.println(gps.time.centisecond());
//       } else {
//         Serial.println("Not Available");
//       }
//       Serial.println();
//       Serial.println();
//       delay(1000);
//     }
//   }
//   // If 5000 milliseconds pass and there are no characters coming in
//   // over the software serial port, show a "No GPS detected" error
//   // if (millis() > 5000 && gps.charsProcessed() < 10)
//   // {
//   //   Serial.println("No GPS detected");
//   // }
// }

// static const int RXPin = 16, TXPin = 17;
// static const uint32_t GPSBaud = 115200;

// SoftwareSerial ss(RXPin, TXPin);

// // The TinyGPS++ object
// TinyGPSPlus gps;

// // The serial connection to the GPS device
// // SoftwareSerial ss(RXPin, TXPin);

// void setup(){
//   Serial.begin(115200);
//   ss.begin(GPSBaud);
//   Serial.println("Serial Txd is on pin: "+String(TX));
//   Serial.println("Serial Rxd is on pin: "+String(RX));
// }

// void loop(){
//   // This sketch displays information every time a new sentence is correctly encoded.
//   Serial.println(ss.available());
//   while (ss.available() > 0){
//     Serial.println(ss.read());
//     gps.encode(ss.read());
//     if (gps.location.isUpdated()){
//       Serial.print("Latitude= "); 
//       Serial.print(gps.location.lat(), 6);
//       Serial.print(" Longitude= "); 
//       Serial.println(gps.location.lng(), 6);
//     }
//   }

//   // //Choose Serial1 or Serial2 as required
//   // while (gps_serial.available()) {
//   //   if (gps.location.isUpdated()){
//   //     Serial.print("Latitude= "); 
//   //     Serial.print(gps.location.lat(), 6);
//   //     Serial.print(" Longitude= "); 
//   //     Serial.println(gps.location.lng(), 6);
//   //   }
//   // }
// }

/*some obs:
 *  * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * on the code, i use the u2uxd. Dont forget to invert the rx/tx with the sensor ;)
 */
/*some obs:
 *  * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * on the code, i use the u2uxd. Dont forget to invert the rx/tx with the sensor ;)
 */

#include <HardwareSerial.h>
#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17

TinyGPSPlus gps;

void setup() {
 Serial.begin(115200);
 Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); //gps baud
}

void loop() {
 bool recebido = false;
  while (Serial2.available()) {
     char cIn = Serial2.read();
     recebido = gps.encode(cIn);
  }
  if (gps.location.isUpdated() && gps.altitude.isUpdated()) {
    Serial.print("D/M/A: ");
    Serial.print(gps.date.value());
    Serial.print(" | alt: ");
    Serial.print(gps.altitude.feet());
    Serial.print(" | satellites: ");
    Serial.println(gps.satellites.value());
    Serial.print(" | Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" | Lang: ");
    Serial.println(gps.location.lng(), 6);
    delay(500);
  } else {
    Serial.println("No GPS");
    delay(500);
  }
}