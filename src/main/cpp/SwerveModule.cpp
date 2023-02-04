/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SwerveModule.h"

SwerveModule::SwerveModule() : pid{frc2::PIDController(robotConfig["angleP"], robotConfig["angleI"], robotConfig["angleD"])} {
}

void SwerveModule::Initialize(int angleID, int driveID, bool debug, double sensorScale) {
    m_debug = debug; 
    m_sensorScale = sensorScale; 

    // Initialize motors.
    angleMotor = new rev::CANSparkMax(angleID, rev::CANSparkMax::MotorType::kBrushless);
    driveMotor = new rev::CANSparkMax(driveID, rev::CANSparkMax::MotorType::kBrushless);
    encoder.push_back(angleMotor->GetAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle));

    // Configure motors.
    angleMotor->RestoreFactoryDefaults();
    driveMotor->RestoreFactoryDefaults();

    angleMotor->SetInverted(false);
    driveMotor->SetInverted(false);

    angleMotor->SetSmartCurrentLimit(15);
    angleMotor->SetSmartCurrentLimit(30);
    
    // Initialize and configure PID.
	pid.SetPID(robotConfig["angleP"], robotConfig["angleI"], robotConfig["angleD"]);
	pid.SetSetpoint(0);
	pid.SetTolerance(2.5/180); // Tolerance of +/- 2.5 degrees.

    // This tells the PID controller that the input is circular; the endpoints (-1 and +1) are the same point.
    pid.EnableContinuousInput(-1.0, 1.0);
}

void SwerveModule::drive(double speed, double angle, bool allow_invert) {
    // Read the sensor angle from the encoder.
    double current_angle = encoder[0].GetPosition();
    //if (m_debug) wpi::outs() << "Sensor angle: " << std::to_string((double) current_angle) << "\n";

    // Scale it so that 2 units is a full rotation.
    current_angle *= m_sensorScale;
    //if (m_debug) wpi::outs() << "Scaled sensor angle: " << std::to_string((double) current_angle) << "\n";

    // Wrap it to an equivalent value between -1 and +1.
    while (current_angle<-1.0) current_angle+=2.0;
    while (current_angle>1.0) current_angle-=2.0;
    //if (m_debug) wpi::outs() << "Wrapped sensor angle: " << std::to_string((double) current_angle) << "\n";

    bool invert = false;
    double iangle = angle;

    if (allow_invert) {
        // Find the diametrically opposite angle.
        iangle = (angle<0)?angle+1:angle-1;

        // Find the distance between the current angle and the goal angle.
        double angle_dist = std::abs(current_angle-angle);
        if (angle_dist>1) angle_dist = 2-angle_dist;

        // If they're too far apart, use the (closer) opposite angle instead.
        if (angle_dist>robotConfig["invertThreshold"]) invert = true;
    }

    // Use the PID controller to calculate the right motor output.
    double output = pid.Calculate(current_angle, invert?iangle:angle);
    output = std::clamp(output, -1.0, 1.0);
    
    /*
    if (m_debug) {
        wpi::outs() << "Goal angle: " << std::to_string((double) angle) << "\n";
        wpi::outs() << "Invert angle: " << std::to_string((double) iangle) << "\n";
        wpi::outs() << "Output: " << std::to_string((double) output) << "\n";
        wpi::outs() << "At setpoint: " << (pid.AtSetpoint()?"True":"False") << "\n";
        wpi::outs() << "Inverting: " << (invert?"True":"False") << "\n";
        wpi::outs() << "Drive motor: " << std::to_string((double) speed*robotConfig["driveScale"]) << "\n";
        wpi::outs() << "\n";
        wpi::outs().flush();
    }
    */

    // Don't turn the module if it's already at the right angle.
    if (pid.AtSetpoint()) angleMotor->Set(0);
    else angleMotor->Set(output);

    // Drive backwards if turning to opposite angle.
    driveMotor->Set((invert?-1:1)*speed*robotConfig["driveScale"]);
}

// Drive without turning the module
void SwerveModule::drive(double speed) {
    // Feed the PIDController.
    // "Failure to do this will result in unintended loop behavior", which doesn't sound good.
    // See above function for explanation.
    double current_angle = encoder[0].GetPosition();
    //if (m_debug) wpi::outs() << "Sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";
    current_angle *= m_sensorScale;
    //if (m_debug) wpi::outs() << "Scaled sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";
    while (current_angle<-1.0) current_angle+=2.0;
    while (current_angle>1.0) current_angle-=2.0;
    //if (m_debug) wpi::outs() << "Wrapped sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";

    pid.Calculate(current_angle, current_angle);
    
    /*if (m_debug) {
        wpi::outs() << "At setpoint (not turning): " << (pid.AtSetpoint()?"True":"False") << "\n";
        wpi::outs() << "\n";
        wpi::outs().flush();
    }*/
 
    angleMotor->Set(0);

    driveMotor->Set(speed*robotConfig["driveScale"]);
}

void SwerveModule::turn(double speed) {
    // Feed the PIDController.
    // "Failure to do this will result in unintended loop behavior", which doesn't sound good.
    // See above function for explanation.
    double current_angle = encoder[0].GetPosition();
    //if (m_debug) wpi::outs() << "Sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";
    current_angle *= m_sensorScale;
    //if (m_debug) wpi::outs() << "Scaled sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";
    while (current_angle<-1.0) current_angle+=2.0;
    while (current_angle>1.0) current_angle-=2.0;
    //if (m_debug) wpi::outs() << "Wrapped sensor angle (not turning): " << std::to_string((double) current_angle) << "\n";

    pid.Calculate(current_angle, current_angle);
    
    angleMotor->Set(speed);

    driveMotor->Set(0);
}

void SwerveModule::Reset(double sensorScale) {
    // Update the PID's parameters and reset its integrator.
	pid.SetPID(robotConfig["angleP"], robotConfig["angleI"], robotConfig["angleD"]);
    pid.Reset();
    
    // Update the sensor scale.
    m_sensorScale = sensorScale;

    // Reset the angle encoder[0].
    //angleMotor->SetSelectedSensorPosition(0,0,0);
}

double SwerveModule::GetRawAngle() {
    return encoder[0].GetPosition();
}