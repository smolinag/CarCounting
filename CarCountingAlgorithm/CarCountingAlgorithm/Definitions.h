#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <opencv2/opencv.hpp>

//-- Preprocessing --
#define FRAME_RESIZE cv::Size(480,320)

//-- Foreground Postprocessing -- 
#define REL_MIN_REGION_AREA 0.001
#define MORPH_ELEM_SIZE 5

//-- Feature Extractor --
#define SHAPE_ANGLE_STEP 15
#define PI 3.141592

#endif;