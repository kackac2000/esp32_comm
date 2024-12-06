import rclpy
from rclpy.node import Node
import serial

class ESP32CommNode(Node):
    def __init__(self):
        super().__init__('esp32_comm_node')
        self.serial_port = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.last_data = None

    def timer_callback(self):
        if self.serial_port.in_waiting > 0:
            data = self.serial_port.readline().decode('utf-8').strip()
            if data != self.last_data:
                self.get_logger().info(f'Received: {data}')
                self.last_data = data

def main(args=None):
    rclpy.init(args=args)
    node = ESP32CommNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()