#include <iostream>
#include <Camera.hpp>

int main() {
    // Initialize and open the camera
    // Create a ZED camera object
    Camera zed;

    // Set configuration parameters
    InitParameters init_params;
    init_params.camera_resolution = RESOLUTION::HD1080 ;
    init_params.camera_fps = 30 ;

    zed.open();

    // Create a matrix to store the image
    sl::Mat image;
    int i = 0;

    while(i++ < 1000){
        // Grab a frame and retrieve the left image
        zed.grab();
        zed.retrieveImage(image, sl::VIEW::LEFT);
    }

    return 0;
}
