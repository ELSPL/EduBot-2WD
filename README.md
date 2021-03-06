# EduBot-2WD

![Overview](/Gazebo/screenshot/overview.png)

EduBot-2WD is an open-source Two Wheel Robot based on NVIDIA Jetson Nano/RPiv3 for study of Autonomous Mobile Robotics.

This bot is compatible with both Jetbot project and Duckietown Project.

----------------------------------------------------------------------

### Gazebo Model Provided:
- This Bot is designed in Onshape.
- It is then converted to URDF using Onshape-to-URDF Repository.
- Finally made small changes to convert it xacro format for gazebo.

![edubot-banner](/Gazebo/screenshot/edubot-banner.png)

### Needs to be Fixed:
- Errors exists in RobotModel visualization in RViz.
- Camera works with rqt_image_view but fails in RViz.

----------------------------------------------------------------------

### Wiki Pages
- Home
- Hardware
    - BOM
    - Design 
    - Assembly 
    - Config
    - Datasheets
- Software 
    - Nano SD card setup
- Getting Started


### Files
- Docs
    - Design (.svg, .scad, .stl, .pdf)
    - Datasheets
    - Resources
- gazebo
    - edubot_2wd
        - meshes (.dae)
        - urdf (.xacro, .gazebo)
        - sdf (.sdf, .config)
    - install_edubot_model.sh
    - Readme.md
- scripts
- notebooks
- src 
