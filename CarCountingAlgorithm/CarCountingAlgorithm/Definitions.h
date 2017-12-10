#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <opencv2/opencv.hpp>

//-- Color Library --
const static uchar ColorLib[20][3] = { { 200, 0, 0 },{ 0, 0, 200 },{ 0, 200, 0 },{ 200, 200, 0 },{ 0, 200, 200 },{ 200, 0, 200 },
{ 0, 80, 255 },{ 220, 150, 200 },{ 0, 250, 100 },{ 100, 0, 250 },{ 100, 250, 0 },{ 240, 240, 100 },{ 180, 250, 20 },{ 160, 190, 20 },
{ 25, 255, 155 },{ 180, 130, 70 },{ 32, 165, 220 },{ 120, 150, 255 },{ 125, 25, 25 },{ 105, 180, 180 } };

//-- Preprocessing --
#define FRAME_RESIZE cv::Size(480,320)

//-- Foreground Postprocessing -- 
#define REL_MIN_REGION_AREA 0.001
#define MORPH_ELEM_SIZE 5

//-- Feature Extractor --
#define SHAPE_ANGLE_STEP 15
#define PI 3.141592

#endif;