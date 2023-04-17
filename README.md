# Sensorium
This project captures and processes depth data from a Kinect sensor, segments the depth image into smaller groups, thresholds the depth values into discrete levels, and sends the processed data to an Arduino via serial communication. The primary applications of this project include depth-based interaction and real-time visualization of depth data.

# Kinect Depth Processing and Serial Communication
This repository contains a C++ program that uses OpenCV and the Kinect SDK to process depth data from a Kinect sensor, dividing the depth image into groups, thresholding the depth values, and sending the processed data to an Arduino via serial communication.

# Dependencies
OpenCV (version 4.x recommended)
Kinect for Windows SDK v1.8

# Overview
The program does the following:
Initializes the Kinect sensor and opens the depth stream.
Captures depth data from the Kinect and converts it into an OpenCV Mat object.
Normalizes the depth values between 0 and 255.
Divides the depth image into groups and calculates the average pixel value for each group.
Thresholds the groups' pixel values into three levels: 0, 128, or 255, based on the average value.
Sends the thresholded pixel values to an Arduino via serial communication.

# Usage
Ensure you have the required dependencies installed (OpenCV and Kinect for Windows SDK v1.8).
Compile the program using your preferred C++ compiler and IDE (e.g., Visual Studio, Code::Blocks).
Connect the Kinect sensor to your computer and ensure it is powered on.
Connect the Arduino to your computer via a USB cable.
Update the serial port (e.g., COM3) in the program to match your Arduino's serial port.
Run the program. The depth data will be displayed in two windows: the raw Kinect depth image and the processed image with thresholded values.
The thresholded pixel values are sent to the Arduino through the serial port.

# Notes
This program is designed for the Kinect for Xbox 360 (Model 1414) and Kinect for Windows (Model 1517) sensors. It may not work with the Kinect for Xbox One or Kinect v2 sensors.
The serial communication parameters (baud rate, data bits, stop bits, and parity) can be adjusted in the program to match your Arduino's configuration.
You may need to adjust the group size and number of groups based on your application requirements.
