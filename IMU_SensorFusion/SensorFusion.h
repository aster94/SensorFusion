//=============================================================================================
// MahonyAHRS.h
//=============================================================================================
//
// Madgwick's implementation of Mayhony's AHRS algorithm.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// Date			Author			Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=============================================================================================
#ifndef MahonyAHRS_h
#define MahonyAHRS_h
#include <math.h>
#include "Arduino.h"

//--------------------------------------------------------------------------------------------
// Variable declaration

class SF {
private:
	float beta;				// algorithm gain
	float twoKp;		// 2 * proportional gain (Kp)
	float twoKi;		// 2 * integral gain (Ki)
	float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame
	float integralFBx, integralFBy, integralFBz;  // integral error terms scaled by Ki
	char anglesComputed;
	static float invSqrt(float x);
	void computeAngles();
	float roll, pitch, yaw;
	float Now,lastUpdate,elapsedTime;

//-------------------------------------------------------------------------------------------
// Function declarations

public:

	SF(void);
	
	void MahonyUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float deltat);
	void MahonyUpdate(float gx, float gy, float gz, float ax, float ay, float az, float deltat);
	
	void MadgwickUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float deltat);
    void MadgwickUpdate(float gx, float gy, float gz, float ax, float ay, float az, float deltat);
	
	float deltatUpdate (){
		Now = micros();
		elapsedTime = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
		lastUpdate = Now;
		return elapsedTime;
	}

	float getRoll() {
		if (!anglesComputed) computeAngles();
		return roll * 57.29578f;
	}
	float getPitch() {
		if (!anglesComputed) computeAngles();
		return pitch * 57.29578f;
	}
	float getYaw() {
		if (!anglesComputed) computeAngles();
		return yaw * 57.29578f + 180.0f;
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
};

#endif
