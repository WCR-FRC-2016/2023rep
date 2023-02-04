/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <vector>

#include "RobotMap.h"

#include <rev/CANSparkMax.h>
#include <frc/controller/PIDController.h>

class SwerveModule {
    private:
        rev::CANSparkMax* angleMotor; // Motor to rotate the module
        rev::CANSparkMax* driveMotor; // Motor to move the robot

        // Angle Encoder (Through Bore)
        // This is a vector. It's really annoying, but it won't build otherwise.
        std::vector<rev::SparkMaxAbsoluteEncoder> encoder;

        frc2::PIDController pid;

        bool m_debug; // Print debug information to the console?
        double m_sensorScale;// All drive motor outputs for this module are scaled by this value.
        
    public:
        SwerveModule();
        void Initialize(int angleID, int driveID, bool debug, double sensorScale);
        void drive(double speed, double angle, bool allow_invert = true);
        void drive(double speed);
        void turn(double speed);
        void Reset(double sensorScale);
        //void ResetEncoder();
        double GetRawAngle();
};