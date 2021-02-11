#include <iostream>
#include <sl/Camera.hpp>

int main() {
    // Create a ZED camera object
    sl::Camera zed;

    // Set configuration parameters
    sl::InitParameters init_params;
    init_params.camera_resolution = sl::RESOLUTION::HD1080 ;
    init_params.camera_fps = 30 ;

    // Open the camera
    auto err = zed.open(init_params);
    if (err != sl::ERROR_CODE::SUCCESS)
        exit(-1);

    // Get camera information (serial number)
    int zed_serial = zed.getCameraInformation().serial_number;
    printf("Hello! This is my serial number: %d\n", zed_serial);

    // Close the camera
    zed.close();
    return 0;
}
