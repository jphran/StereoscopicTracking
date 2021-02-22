#include <iostream>
#include <sl/Camera.hpp>

int ObjectDetection3D() {
    // Create ZED objects
    sl::Camera zed;
    sl::InitParameters initParameters;
    initParameters.camera_resolution = sl::RESOLUTION::HD720;
    initParameters.depth_mode = sl::DEPTH_MODE::ULTRA;
    initParameters.sdk_verbose = true;

    // Open the camera
    sl::ERROR_CODE zed_error = zed.open(initParameters);
    if (zed_error != sl::ERROR_CODE::SUCCESS) {
        std::cout << "Error " << zed_error << ", exit program.\n";
        return 1; // Quit if an error occurred
    }

    // Define the Object Detection module parameters
    sl::ObjectDetectionParameters detection_parameters;
    detection_parameters.image_sync = true;
    detection_parameters.enable_tracking = true;
    detection_parameters.enable_mask_output = true;

// Object tracking requires camera tracking to be enabled
    if (detection_parameters.enable_tracking)
        zed.enablePositionalTracking();

    std::cout << "Object Detection: Loading Module..." << std::endl;
    auto err = zed.enableObjectDetection(detection_parameters);
    if (err != sl::ERROR_CODE::SUCCESS) {
        std::cout << "Error " << err << ", exit program.\n";
        zed.close();
        return 1;
    }



    // Set runtime parameter confidence to 40
    sl::ObjectDetectionRuntimeParameters detection_parameters_runtime;
    detection_parameters_runtime.detection_confidence_threshold = 40;

    sl::Objects objects;

    // Grab new frames and detect objects
    while (zed.grab() == sl::ERROR_CODE::SUCCESS) {
        err = zed.retrieveObjects(objects, detection_parameters_runtime);

        if (objects.is_new) {
            // Count the number of objects detected
            std::cout << objects.object_list.size() << " Object(s) detected";

            auto first_object = objects.object_list[0];
            // Display the 3D location of an object
            std::cout << " 3D position: " << first_object.position;

            // Display its 3D bounding box coordinates
            std::cout << " Bounding box 3D \n";
            for (auto it : first_object.bounding_box)
                std::cout << "    " << it;
        }
    }

    // Disable object detection and close the camera
    zed.disableObjectDetection();
    zed.close();
    return 0;
}

int HelloWorld(){
    // HELLO WORLD ---------------------------------------------
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

int ImageCapture() {
    // Create a ZED camera object
    sl::Camera zed;

    // Set configuration parameters
    sl::InitParameters init_params;
    init_params.camera_resolution = sl::RESOLUTION::HD1080; // Use HD1080 video mode
    init_params.camera_fps = 30; // Set fps at 30

    // Open the camera
    sl::ERROR_CODE err = zed.open(init_params);
    if (err != sl::ERROR_CODE::SUCCESS)
        exit(-1);

    // Grab an image
    if (zed.grab() == sl::ERROR_CODE::SUCCESS) {
        // A new image is available if grab() returns ERROR_CODE::SUCCESS
    }

    // Capture 50 frames and stop
    int i = 0;
    sl::Mat image;
    while (i < 50) {
        // Grab an image
        if (zed.grab() == sl::ERROR_CODE::SUCCESS) {
            // A new image is available if grab() returns ERROR_CODE::SUCCESS
            zed.retrieveImage(image, sl::VIEW::LEFT); // Get the left image
            auto timestamp = zed.getTimestamp(sl::TIME_REFERENCE::IMAGE); // Get image timestamp
            printf("Image resolution: %d x %d  || Image timestamp: %llu\n", image.getWidth(), image.getHeight(), timestamp);
            i++;
        }
    }

    // Close the camera
    zed.close();
    return 0;
}

int DepthPerception() {
    // Create a ZED camera object
    sl::Camera zed;

    // Set configuration parameters
    sl::InitParameters init_parameters;
    init_parameters.depth_mode = sl::DEPTH_MODE::PERFORMANCE; // Use PERFORMANCE depth mode
    init_parameters.coordinate_units = sl::UNIT::MILLIMETER; // Use millimeter units (for depth measurements)

    // Open the camera
    auto returned_state = zed.open(init_parameters);
    if (returned_state != sl::ERROR_CODE::SUCCESS) {
        std::cout << "Error " << returned_state << ", exit program." << std::endl;
        return EXIT_FAILURE;
    }

    // Set runtime parameters after opening the camera
    sl::RuntimeParameters runtime_parameters;
    runtime_parameters.sensing_mode = sl::SENSING_MODE::STANDARD; // Use STANDARD sensing mode

    // Capture 50 images and depth, then stop
    int i = 0;
    sl::Mat image, depth, point_cloud;

    while (i < 50) {
        // A new image is available if grab() returns ERROR_CODE::SUCCESS
        if (zed.grab(runtime_parameters) == sl::ERROR_CODE::SUCCESS) {
            // Retrieve left image
            zed.retrieveImage(image, sl::VIEW::LEFT);
            // Retrieve depth map. Depth is aligned on the left image
            zed.retrieveMeasure(depth, sl::MEASURE::DEPTH);
            // Retrieve colored point cloud. Point cloud is aligned on the left image.
            zed.retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA);

            // Get and print distance value in mm at the center of the image
            // We measure the distance camera - object using Euclidean distance
            int x = image.getWidth() / 2;
            int y = image.getHeight() / 2;
            sl::float4 point_cloud_value;
            point_cloud.getValue(x, y, &point_cloud_value);

            if(std::isfinite(point_cloud_value.z)){
                float distance = sqrt(point_cloud_value.x * point_cloud_value.x + point_cloud_value.y * point_cloud_value.y + point_cloud_value.z * point_cloud_value.z);
                std::cout<<"Distance to Camera at {"<<x<<";"<<y<<"}: "<<distance<<"mm"<<std::endl;
            }else
                std::cout<<"The Distance can not be computed at {"<<x<<";"<<y<<"}"<<std::endl;

            // Increment the loop
            i++;
        }
    }
    // Close the camera
    zed.close();
    return EXIT_SUCCESS;
}
int main() {
    return DepthPerception();
}
