#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
  float fps = 30;
  //int codec = CV_FOURCC('M', 'P', 'E', 'G');
  int codec = CV_FOURCC('t', 'h', 'e', 'o');
  VideoWriter frameWriter;
  frameWriter.open("output.avi", codec, fps, cv::Size(640, 480), true);

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    float frameCounter = 0;
    while(cvGetWindowHandle("edges"))
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        //imshow("edges", edges);
        //frameWriter << edges;
        frameWriter << frame;
        imshow("edges", frame);
        frameCounter += 1;
        //std::cout<<"frame number: " << frameCounter << "\n";
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    std::cout<<"Video file closed\n";
    frameWriter.release();
    return 0;
}
