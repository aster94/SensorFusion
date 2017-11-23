#include <Streaming.h>
#include <MPU9250.h>
float gx, gy, gz, ax, ay, az, mx, my, mz, temp;
#define SPI_CLOCK 16000000  // 16MHz
#define SPI_BUS 2
#define SS_PIN  PB12

MPU9250 mpu(SPI_CLOCK, SS_PIN, SPI_BUS, BITS_DLPF_CFG_98HZ, BITS_DLPF_CFG_98HZ);

#include "SensorFusion.h"
float pitch, roll, yaw;
float deltat;
SF filter;


#define WAITFORINPUT(){            \
    while(!Serial.available()){};  \
    while(Serial.available()){     \
      Serial.read();             \
    };                             \
  }

//output
//#define RAW_DATA
#define EULER_DATA


void setup() {
  Serial.begin(115200);

  WAITFORINPUT();
  Serial.println("starting...");

  mpu.init(true, true);

  uint8_t wai = mpu.IMU_wai();
  Serial << "WAI imu: " << _HEX(wai) << newl;
  if (wai == 0x71 || wai == 0x73) Serial.println("Successful connection");
  else Serial.println("Failed connection");

  wai = mpu.AK8963_wai();
  Serial << "WAI mag: " << _HEX(wai) << newl;
  if (wai == 0x48)Serial.println("Successful connection to mag");
  else Serial.println("Failed connection to mag");

  mpu.calib_acc();
  mpu.calib_mag();

  Serial.println("Send any char to begin main loop.");
  WAITFORINPUT();
}

void loop() {

  mpu.read_all();
  // mpu.read_mag();
  // mpu.read_acc();
  // mpu.read_gyro();

  gx = mpu.gyro_data[0];
  gy = mpu.gyro_data[1];
  gz = mpu.gyro_data[2];
  ax = mpu.accel_data[0];
  ay = mpu.accel_data[1];
  az = mpu.accel_data[2];
  mx = mpu.mag_data[0];
  my = mpu.mag_data[1];
  mz = mpu.mag_data[2];
  temp = mpu.temperature;

#ifdef RAW_DATA
  Serial << "From last Update:\t" << deltat << newl;
  Serial << "GYRO:\tx:" << gx << "\t\ty:" << gy << "\t\tz:" << gz << newl;
  Serial << "ACC:\tx:" << ax << "\t\ty:" << ay << "\t\tz:" << az << newl;
  Serial << "MAG:\tx:" << mx << "\t\ty:" << my << "\t\tz:" << mz << newl;
  Serial << "TEMP:\7" << temp << newl << newl;
#endif

  deltat = filter.deltatUpdate();
  filter.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);
  //filter.MadgwickUpdate(gx, gy, gz, ax, ay, az, deltat);

  roll = filter.getRoll();
  pitch = filter.getPitch();
  yaw = filter.getYaw();

#ifdef EULER_DATA
  Serial << "Pitch:\t" << pitch << "\t\tRoll:\t" << roll << "\t\tYaw:\t" << yaw << newl << newl;
#endif

  //Serial  << pitch << ":" << roll << ":" << yaw << newl;
}
