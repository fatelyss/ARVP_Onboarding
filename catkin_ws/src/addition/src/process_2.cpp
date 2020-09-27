#include <iostream>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include "std_msgs/String.h"

// Callback function for subscriber
void numberCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("%s", msg->data.c_str());

    ros::NodeHandle r;

    // Publish data on topic 'number'
    ros::Publisher number_pub = r.advertise<std_msgs::String>("second", 10);

    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        // Get user input
        std::string inputString;
        std::cout << "How much would you like to add to that number (between 1 and 1000): ";
        std::getline(std::cin, inputString);
        std_msgs::String new_msg;

        // Check if the user entered an input
        if (!inputString.empty())
        {
            int num1 = std::stoi(msg->data.c_str());
            int num2 = std::stoi(inputString);
            int sum = num1 + num2;

            std::stringstream ss;
            ss << msg->data.c_str() << " + " << inputString << " = " << sum;
            new_msg.data = ss.str();

            // Publish the data
            number_pub.publish(new_msg);
        }

        ros::spinOnce();

        loop_rate.sleep();
    }

    // // Get user input
    // std::string inputString;
    // std::cout << "How much would you like to add to that number (between 1 and 1000): ";
    // std::getline(std::cin, inputString);
    // std_msgs::String new_msg;

    // // Check if the user entered an input
    // if (!inputString.empty())
    // {
    //     int num1 = std::stoi(msg->data.c_str());
    //     int num2 = std::stoi(inputString);
    //     int sum = num1 + num2;

    //     std::stringstream ss;
    //     ss << msg->data.c_str() << " " << inputString << " " << sum;
    //     new_msg.data = ss.str();

    //     // Publish the data
    //     number_pub.publish(new_msg);
    //     //ros::spinOnce();
    // }

}

int main(int argc, char **argv)
{
    // Initialize ROS
    // Specify our node 'process_1'
    ros::init(argc, argv, "process_2");

    // Create a handle to this process' node.
    ros::NodeHandle n;

    // Recieve messages
    ros::Subscriber sub = n.subscribe("first", 10, numberCallback);

    // For callbacks
    ros::spin();
    
    return 0;
}