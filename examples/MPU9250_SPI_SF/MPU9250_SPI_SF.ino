//the Serial needs this library https://github.com/geneReeves/ArduinoStreaming

#include "MPU9250.h"
#include "SensorFusion.h"
#include "Streaming.h"
float gx, gy, gz, ax, ay, az, mx, my, mz, temp;
float pitch, roll, yaw;
float deltat;
SF filter;
#define SS_PIN PB12
SPIClass mySPI (2);
MPU9250 IMU(mySPI, SS_PIN);
int status;

//#define EULER_DATA
//#define RAW_DATA
#define PROCESSING


void setup() {
  // serial to display data
  Serial.begin(115200);
  while (!Serial) {}

  // start communication with IMU
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {}
  }
}

void loop() {

  IMU.readSensor();

  ax = IMU.getAccelX_mss();
  ay = IMU.getAccelY_mss();
  az = IMU.getAccelZ_mss();
  gx = IMU.getGyroX_rads();
  gy = IMU.getGyroY_rads();
  gz = IMU.getGyroZ_rads();
  mx = IMU.getMagX_uT();
  my = IMU.getMagY_uT();
  mz = IMU.getMagZ_uT();
  temp = IMU.getTemperature_C();

#ifdef RAW_DATA
  Serial << "From last Update:\t"; Serial.println(deltat, 6);
  Serial << "GYRO:\tx:" << gx << "\t\ty:" << gy << "\t\tz:" << gz << newl;
  Serial << "ACC:\tx:" << ax << "\t\ty:" << ay << "\t\tz:" << az << newl;
  Serial << "MAG:\tx:" << mx << "\t\ty:" << my << "\t\tz:" << mz << newl;
  Serial << "TEMP:\t" << temp << newl << newl;
#endif

  deltat = filter.deltatUpdate();
  //filter.MahonyUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);  //mahony is suggested if there isn't the mag
  filter.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);  //else use the magwick

  roll = filter.getRoll();
  pitch = filter.getPitch();
  yaw = filter.getYaw();

#ifdef EULER_DATA
  Serial << "Pitch:\t" << pitch << "\t\tRoll:\t" << roll << "\t\tYaw:\t" << yaw << newl << newl;
#endif

#ifdef PROCESSING
  roll = filter.getRollRadians();
  pitch = filter.getPitchRadians();
  yaw = filter.getYawRadians();
  Serial  << pitch << ":" << roll << ":" << yaw << newl;
#endif

  //delay(200); //for readability

}
