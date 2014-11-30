/************************************************************************
* Virtual Whiteboard System Based on Image Processing
* Main file
*
* Author: Alankar Kotwal <alankarkotwal13@gmail.com>
************************************************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <string>
#include "path.hpp"

using namespace cv;

int main() {

	std::stringstream configPath;
	configPath<<REPO_ROOT<<"/config/config.xml";

	boost::property_tree::ptree config;
	boost::property_tree::read_xml(configPath.str(), config);

	VideoCapture cap(config.get<int>("whiteboard.capture.captureNo"));
	
	Mat frame;
	cap >> frame;
	
	Mat draw = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
	namedWindow("Drawing", WINDOW_AUTOSIZE);
	
	Moments mom;
	int xC, yC;
	
	while(1) {
	
		boost::property_tree::read_xml(configPath.str(), config);
	
		cap >> frame;
		
		Mat channels[3];
		split(frame, channels);
		
		Mat red = channels[2];		// OpenCV follows BGR
		threshold(red, red, config.get<int>("whiteboard.imgproc.threshold"), config.get<int>("whiteboard.imgproc.maxVal"), THRESH_BINARY);
		
		mom = moments(red, true);
		xC = mom.m10 / mom.m00;
		yC = mom.m01 / mom.m00;
		
		Point cen(xC, yC);
		Scalar color(config.get<int>("whiteboard.rendering.b"), config.get<int>("whiteboard.rendering.g"), config.get<int>("whiteboard.rendering.r"));
		
		if(mom.m00 > config.get<int>("whiteboard.imgproc.minPixelNo")) {
			circle(draw, cen, config.get<int>("whiteboard.rendering.lineWidth"), color, 0, 8, 0);
		}
		
		imshow("Drawing", draw);
		
		waitKey(1);
	}
	
	return 0;
}
