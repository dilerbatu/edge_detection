#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


namespace edge_detection
{
class EdgeDetector
{

	public:
		// Empty "images" vector. Unprocessed images will be added to it. (Class attribute)
		vector <string> images;

		// Empty "processed_images" vector. Processed images will be added to it. (Class attribute)
		vector <cv::Mat> processed_images;

		//Method Decleration
		void getImages();
		void processImages();
		void showProcessedImages();
		void saveProcessedImages();

};

}
