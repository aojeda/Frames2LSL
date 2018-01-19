#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv)
{
  std::string filename = "FrameMarker.avi";
  if (argc > 1)
    filename = std::string(argv[1]);

  float fps = 30;
  if (argc > 2)
    fps = (float)std::stoi(argv[2]);

  int width = 640;
  if (argc > 3)
    width = std::stoi(argv[3]);

  int height = 480;
  if (argc > 4)
    height = std::stoi(argv[4]);
  int isColor = true;

  std::string winName = "Frames2LSL";
  int loc = filename.find_last_of("/");
  if (loc!=-1)
    winName = filename.substr(loc+1,-1);
  loc = winName.find_last_of(".");
  if (loc!=-1)
    winName = winName.substr(0,loc);

  //int codec = CV_FOURCC('M', 'P', 'E', 'G');
  int codec = CV_FOURCC('t', 'h', 'e', 'o');
  VideoWriter frameWriter;
  frameWriter.open(filename, codec, fps, cv::Size(width, height), isColor);

  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  //Mat edges;
  namedWindow(winName,1);
  float frameCounter = 0;
  while(cvGetWindowHandle(winName.c_str()))
  {
    Mat frame;
    cap >> frame; // get a new frame from camera
    //cvtColor(frame, edges, COLOR_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //Canny(edges, edges, 0, 30, 3);
    //imshow("edges", edges);
    //frameWriter << edges;
    frameWriter << frame;
    imshow(winName, frame);
    frameCounter += 1;
    //std::cout<<"frame number: " << frameCounter << "\n";
    if(waitKey(fps) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  std::cout<<"Video file closed\n";
  frameWriter.release();
  return 0;
}
