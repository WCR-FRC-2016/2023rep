/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoAlignCommand.h"
#include "RobotMap.h"

AutoAlignCommand::AutoAlignCommand(DriveBase& drivebase, Limelight& limelight) : m_drivebase(drivebase), m_limelight(limelight) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({&drivebase, &limelight});
}

// Called when the command is initially scheduled.
void AutoAlignCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoAlignCommand::Execute() {
    double x = m_limelight.GetX()+robotConfig["autoTargetX"];
    double z = m_limelight.GetZ()+robotConfig["autoTargetZ"];
    double angle = m_limelight.GetHeading();
    
    wpi::outs() << std::to_string(x) << " " << std::to_string(z) << " " << std::to_string(angle) << "\n";

    x = std::clamp(5*x, -1.0, 1.0);
    z = std::clamp(-5*z, -1.0, 1.0);
    angle = std::clamp(-angle/30, -1.0, 1.0);

    wpi::outs() << std::to_string(x) << " " << std::to_string(z) << " " << std::to_string(angle) << "\n";

    m_drivebase.Swerve(x, z, angle);
}

// Called once the command ends or is interrupted.
void AutoAlignCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoAlignCommand::IsFinished() {return false;}
