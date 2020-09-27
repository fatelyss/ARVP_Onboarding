#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "ros/ros.h"
#include "std_msgs/String.h"

/**
 * Process 1
 **/

// Callback function for subscriber
void additionCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("%s", msg->data.c_str());
}

int main(int argc, char **argv)
{
    // Initialize ROS
    // Specify our node 'process_1'
    ros::init(argc, argv, "process_1");

    // Create a handle to this process' node.
    ros::NodeHandle n;
    ros::NodeHandle r;

    // Publish data on topic 'number'
    ros::Publisher number_pub = n.advertise<std_msgs::String>("first", 10);

    // Get user input
    std::string inputString;
    std::cout << "Enter a Number between 1 and 1000: ";
    std::getline(std::cin, inputString);
    std_msgs::String msg;

    // Check if the user entered an input
    if (!inputString.empty())
    {
        // Turn data to a string msg
        std::stringstream ss;
        ss << inputString;
        msg.data = ss.str();

        // Publish the data
        number_pub.publish(msg);
        
        while(ros::ok())
        {
            // Recieve messages
            ros::Subscriber sub = r.subscribe("second", 10, additionCallback);

            ros::spin();
        }
        
    }
    
    return 0;
}