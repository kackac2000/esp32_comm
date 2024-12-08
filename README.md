# ESP32 Serial Communication for RoArm-M1 WebApp

This ROS 2 package enables serial communication with the RoArm-M1 robotic arm when using its web application. The node receives messages and outputs detailed logs for better understanding of executed WebApp functions.

## Installation

1. Clone the repository:
   ```sh
   cd ~/ros2_ws/src
   git clone https://github.com/kackac2000/esp32_comm.git
   ```
2. Build the ROS 2 package:
    ```sh
    cd ~/ros2_ws
    colcon build --packages-select esp32_comm
    ```
## Usage

1. Source the workspace:
    ```sh
    source install/setup.bash
    ```
2. Connect to the robotic arm via USB cable and run the commands:
```bash
sudo chmod 777 /dev/ttyUSB0
ros2 run serial_ctrl serial_ctrl
```
    
3. Connect to the [RoArm-M1 WebApp](https://www.waveshare.com/wiki/RoArm-M1_Tutorial_I:_How_To_Use) following linked steps.


4. Run the node to receive messages:
    ```sh
    ros2 run esp32_comm esp_ros_node
    ```
The terminal will output messages of the executed WebApp functions helping you gain insight into the actions performed.
    
