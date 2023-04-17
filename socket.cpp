#include <boost/asio.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <opencv2/highgui.hpp>
#include <NuiApi.h>

using boost::asio::ip::tcp;

int main()
{
    // Initialize Kinect sensor
    INuiSensor* sensor;
    HRESULT hr = NuiCreateSensorByIndex(0, &sensor);
    if (FAILED(hr)) {
        std::cerr << "Failed to create Kinect sensor!" << std::endl;
        return -1;
    }

    hr = sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH);
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize Kinect sensor!" << std::endl;
        return -1;
    }

    // Open Kinect depth stream
    HANDLE depthStreamHandle = NULL;
    hr = sensor->NuiImageStreamOpen(
        NUI_IMAGE_TYPE_DEPTH, // Image type
        NUI_IMAGE_RESOLUTION_640x480, // Image resolution
        0, // Image stream flags
        2, // Number of frames to buffer
        NULL, // Event handle (auto-create)
        &depthStreamHandle // Stream handle
    );
    if (FAILED(hr)) {
        std::cerr << "Failed to open Kinect depth stream!" << std::endl;
        return -1;
    }

    // Get depth stream size
    NUI_IMAGE_RESOLUTION depthResolution = NUI_IMAGE_RESOLUTION_640x480;
    DWORD depthWidth, depthHeight;
    NuiImageResolutionToSize(depthResolution, depthWidth, depthHeight);

    // Initialize Boost ASIO
    boost::asio::io_service io_service;
    tcp::socket socket(io_service);
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("RASPBERRY_PI_IP_ADDRESS", "PORT_NUMBER"); // Replace with actual IP address and port number
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Connect to Raspberry Pi
    boost::asio::connect(socket, endpoint_iterator);

    // Split the output image video into 15 groups of resolution 128X160
    const int numCols = 5; // Number of columns
    const int numRows = 3; // Number of rows
    const int groupWidth = depthWidth / numCols; // Width of each group
    const int groupHeight = depthHeight / numRows; // Height of each group

    while (true) {
        // Get latest depth frame
        NUI_IMAGE_FRAME depthFrame = { 0 };
        HRESULT hr = sensor->NuiImageStreamGetNextFrame(
            depthStreamHandle, // Stream handle
            0, // Timeout (0 = infinite)
            &depthFrame // Output image frame
        );

        if (SUCCEEDED(hr)) {
            // Get depth frame data
            NUI_LOCKED_RECT depthLockedRect;
            hr = depthFrame.pFrameTexture->LockRect(0, &depthLockedRect, NULL, 0);
            if (SUCCEEDED(hr)) {
                // Convert depth frame data to OpenCV format
                cv::Mat depthMat(depthHeight, depthWidth, CV_16
