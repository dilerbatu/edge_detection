#include <EdgeDetector.hpp>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace edge_detection;
using namespace cv;


void EdgeDetector::getImages(){
	//This method serves to get all images in the data folder.

	//Getting all images with glob.
	glob("data/*", images);
	
	cout << "All images fetched succesfuly." << endl;
}


void EdgeDetector::processImages(){
	//This method serves to process all images.

	//All photos in images vector are processed one by one.
	for (string image: images){

		Mat img = imread(image, IMREAD_COLOR); //Reading the image

		Mat gray;
		cvtColor(img, gray, COLOR_BGR2GRAY); //Grayscaling the image

		Mat blurred;
		GaussianBlur(gray, blurred, Size(3,3), 0, 0); //Bluring the image

		Mat edges;
		Canny(blurred, edges, 150, 200, 3 ); //Applying Canny Filter to image and getting edges

		vector<Vec4i> lines; //Vector for holding x1,y1,x2,y2 data.

		//Using probabilistic hough line tranformation to find lines on the image. To get better performance, this paramaters can be changed.
		HoughLinesP(edges, lines, 1, CV_PI / 180, 40, 30, 200);


		/*
		lines is a vector that holds all data of lines like start and end point of lines.
        lines = [[line 0 = [x1,y1,x2,y2],
                  line 1 = [x3,y3,x4,y4],
                  line i = ...........]]
		*/


		for(size_t i = 0; i < lines.size(); i++){ //i indicates indice of lines vector
			Vec4i points = lines[i]; //Points vector holds line i's x1,y1,x2,y2 pixel coordinates.
			
			//Indicating start and end point of the line.
			int x1 = points[0];
			int y1 = points[1];
			int x2 = points[2];
			int y2 = points[3];

			//Drawing lines over the image.
			line(img, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2 , LINE_AA);
		}
		
		//Adding image into processed_images vector.
		processed_images.push_back(img);
	}

	cout << "All images processed succesfuly." << endl;
}


void EdgeDetector::showProcessedImages(){
	//This method serves to display the processed images.

	//Checking "processed_images" vector's size
	if (processed_images.size() != 0){

		//#Showing all resized images one by one
		for(size_t i = 0; i <= processed_images.size() - 1; i++){ // i indicates indice of processed_images vector.
			Mat resized;
			resize(processed_images[i], resized, Size(600, 600)); // For better view
			imshow("Results", resized);
			waitKey(0);
		}

	}
	else{
		cout << "Process the images first, to see the processed images.";
	}	
}


void EdgeDetector::saveProcessedImages(){
	//This method serves to save the processed images.

	//Checking "processed_images" vector's size
	if (processed_images.size() != 0){

		for(size_t i = 0; i <= processed_images.size() -1 ; i++){

			//Saving all images into output_cpp file.
			imwrite("outputs_cpp/output_" + to_string(i) + ".jpg", processed_images[i]);

		}
		
		cout << "Images saved to outputs_cpp file";

	}
	else{
		cout << "Process the images first, to save the processed images.";
	}
	
}


int main()
{
	edge_detection::EdgeDetector detector;

	detector.getImages();
	detector.processImages();
	detector.saveProcessedImages();
	detector.showProcessedImages();
	
	return 0;
}
