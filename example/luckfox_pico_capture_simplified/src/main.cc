// Copyright (c) 2023 by Rockchip Electronics Co., Ltd. All Rights Reserved.
//
// ... licence banner unchanged ...

/*-------------------------------------------
                Includes
-------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

// #include "retinaface_facenet.h"
#include <time.h>
#include <sys/time.h>

#include "dma_alloc.cpp"

#include <opencv2/opencv.hpp> // <-- was transitively included before, keep explicitly

#define USE_DMA 0

/*-------------------------------------------
                  Main Function
-------------------------------------------*/
int main(int argc, char **argv)
{
    /*――― 1. argument list simplified ―――*/
    if (argc != 2)
    {
        printf("%s <output.jpg>\n", argv[0]);
        return -1;
    }
    const char *output_path = argv[1];

    /*――― 2. open camera exactly as before ―――*/
    cv::VideoCapture cap;
    cap.open(0); // same call style as original
    if (!cap.isOpened())
    {
        printf("Cannot open camera\n");
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);  // optional
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480); // optional

    cv::Mat frame;
    printf("Grabbing a frame\n");
    cap >> frame; // grab one frame
    printf("Writing a frame\n");
    if (!cv::imwrite(output_path, frame))
    {
        printf("Failed to write %s\n", output_path);
        return -1;
    }
    printf("Saving the frame\n");
    printf("Snapshot saved to %s\n", output_path);
    return 0;
}
