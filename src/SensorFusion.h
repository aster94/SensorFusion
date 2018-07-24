//=============================================================================================
// SensorFusion.h
//=============================================================================================
//
// Madgwick's implementation of Mahony's AHRS algorithm.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// Date			Author			Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
// 23/11/2017   Aster			Optimised time handling and melted in one library
//
//=============================================================================================
#ifndef SensorFusion_h
#define SensorFusion_h

#include <math.h>
#include "Arduino.h"

//--------------------------------------------------------------------------------------------
// Variable declaration

class SF {
//-------------------------------------------------------------------------------------------
// Function declarations

public:

	SF();
	
	void MahonyUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float deltat);
	void MahonyUpdate(float gx, float gy, float gz, float ax, float ay, float az, float deltat);
	
	void MadgwickUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float deltat);
    void MadgwickUpdate(float gx, float gy, float gz, float ax, float ay, float az, float deltat);
	
	//these values are already defined by arduino
	//const float DEG_TO_RAD = 0.0174532925199433f; //PI/180.0f;	
	//const float RAD_TO_DEG = 57.29577951308233f; //180.0f/PI
	
	float deltatUpdate (){
		Now = micros();
		deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
		lastUpdate = Now;
		return deltat;
	}

	float getRoll() {
		if (!anglesComputed) computeAngles();
		return roll * RAD_TO_DEG;
	}
	float getPitch() {
		if (!anglesComputed) computeAngles();
		return pitch * RAD_TO_DEG;
	}
	float getYaw() {
		if (!anglesComputed) computeAngles();
		return yaw * RAD_TO_DEG + 180.0f;
	}
	float getRollRadians() {
		if (!anglesComputed) computeAngles();
		return roll;
	}
	float getPitchRadians() {
		if (!anglesComputed) computeAngles();
		return pitch;
	}
	float getYawRadians() {
		if (!anglesComputed) computeAngles();
		return yaw;
	}

private:
	float beta;				//Madgwick: 2 * proportional gain
	float twoKp;			//Mahony: 2 * proportional gain (Kp)
	float twoKi;			//Mahony: 2 * integral gain (Ki)
	float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame
	float integralFBx, integralFBy, integralFBz;  // integral error terms scaled by Ki
	bool anglesComputed;
	static float invSqrt(float x);
	void computeAngles();
	float roll, pitch, yaw;
	float Now,lastUpdate,deltat;
	
};

#endif
