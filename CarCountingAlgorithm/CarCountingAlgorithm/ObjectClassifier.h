#ifndef ObjectClassifier_H
#define ObjectClassifier_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "ForegroundObject.h"

class ObjectClassifier {

public:
	ObjectClassifier();

	void classifyObject(ForegroundObject fObj, int &label, float &confidence);
};
#endif;