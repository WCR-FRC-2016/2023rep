# Winner's Circle Robotics 2023 Rep

## This Year's Goals

- Teleop Automation
- Swerve

## Game Info

[Charged Up!](https://firstroboticsbc.org/first-robotics-competition/charged-up-game-and-season/)

## Tools

### Standard Tools

- [WPILib 2023](https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html)
    - [What's new in 2023](https://docs.wpilib.org/en/stable/docs/yearly-overview/yearly-changelog.html)
- [Limelight](https://docs.limelightvision.io/en/latest/)

### VsCode Extensions

- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools): IntelliSense & Beautifier
    - Uses [Clang syntax](https://clang.llvm.org/docs/ClangFormatStyleOptions.html) for settings
    - [Clang Format Quick Tutorial](https://leimao.github.io/blog/Clang-Format-Quick-Tutorial/)

## Helpful Links

- [Google's c++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## Tasks for the Year

- [x] Update code for new swerve modules
- [ ] Add variable speed
- [ ] Fix acceleration?
- [ ] Write autonomous routines
    - [ ] Routine A: Score two from furthest-from-loading-bay
    - [ ] Routine B: Score one
    - [ ] Routine C: Score one and auto-balance
    - [ ] Routine D: Taxi
    - [ ] Finalize list
- [ ] Create subsystems for robot code
    - [ ] Drivebase
        - [ ] Snap to rotation
    - [ ] Arm
    - [ ] Collector
- [ ] Controller Design
    - [ ] Document and share controller design
- [ ] Tele-auto scoring
    - [x] Detect AprilTags
    - [ ] Align robot to AprilTags
    - [ ] Align robot to reflective tape
    - [ ] Auto extend arm to right height
    - [ ] Auto score
- [ ] Tele-auto balance
    - [ ] Get balance of robot
    - [ ] Maneuver robot based on balance
- [ ] Tele-auto loading
    - [ ] AprilTags work for scoring repurposed
    - [ ] Auto collect
- [ ] Tele-auto arm levels
- [ ] Color detection?
- [ ] Driver camera
- [ ] Limelight 3 configured
- [ ] ~~Auto-mono-piece-control~~
- [ ] LED Panel
    - [ ] Request indicator for human player
    - [ ] Align indicator based on reflective tape in case Limelight visual fails
- [ ] Sound effects!
- [ ] Care for code
    - [ ] Document
    - [x] Refactor
    - [x] Level based logging
        - [ ] Update to include units library
    - [ ] JSON/YAML config instead of flat text
