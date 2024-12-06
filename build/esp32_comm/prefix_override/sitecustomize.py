import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/kmagier/ros2_ws/src/esp32_comm/install/esp32_comm'
