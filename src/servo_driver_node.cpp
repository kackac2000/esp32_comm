#include <rclcpp/rclcpp.hpp>
#include <SCServo.h>
#include <math.h>

class ServoDriverNode : public rclcpp::Node
{
public:
    ServoDriverNode() : Node("servo_driver_node")
    {

        servoInit();


        feedback_publisher_ = this->create_publisher<std_msgs::msg::String>("servo_feedback", 10);
        set_mode_subscriber_ = this->create_subscription<std_msgs::msg::Int32>(
            "set_servo_mode", 10, std::bind(&ServoDriverNode::setModeCallback, this, std::placeholders::_1));
    }

private:
    void servoInit()
    {
        Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
        st_.pSerial = &Serial1;
        while (!Serial1) {}

        for (int i = 0; i < MAX_ID; i++)
        {
            Torque_List[i] = true;
        }
    }

    void setModeCallback(const std_msgs::msg::Int32::SharedPtr msg)
    {
        byte InputID = static_cast<byte>(msg->data);
        byte InputMode = 3; 
        setMode(InputID, InputMode);
    }

    void setMode(byte InputID, byte InputMode)
    {
        st_.unLockEprom(InputID);
        if (InputMode == 0)
        {
            if (SERVO_TYPE_SELECT == 1)
            {
                st_.writeWord(InputID, 11, 4095);
                st_.writeByte(InputID, SMS_STS_MODE, InputMode);
            }
            else if (SERVO_TYPE_SELECT == 2)
            {
                st_.writeWord(InputID, SCSCL_MIN_ANGLE_LIMIT_L, 20);
                st_.writeWord(InputID, SCSCL_MAX_ANGLE_LIMIT_L, 1003);
            }
        }
        else if (InputMode == 3)
        {
            if (SERVO_TYPE_SELECT == 1)
            {
                st_.writeByte(InputID, SMS_STS_MODE, InputMode);
                st_.writeWord(InputID, 11, 0);
            }
            else if (SERVO_TYPE_SELECT == 2)
            {
                st_.writeWord(InputID, SCSCL_MIN_ANGLE_LIMIT_L, 0);
                st_.writeWord(InputID, SCSCL_MAX_ANGLE_LIMIT_L, 0);
            }
        }
        st_.LockEprom(InputID);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr feedback_publisher_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr set_mode_subscriber_;
    SCSCL st_;
    bool Torque_List[253];
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServoDriverNode>());
    rclcpp::shutdown();
    return 0;
}