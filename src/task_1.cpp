/**********************************************************************
   File    task_1.cpp
   Author  takeda tomoki (24w)
   Environment    ROS_noetic
   OS       Ubuntu 20.04
   StartDay 2024/04/
**********************************************************************/


/**********************************************************************
   Include Libraries
**********************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


/**********************************************************************
   Declare variables
**********************************************************************/


/**********************************************************************
   Globle
**********************************************************************/



/**********************************************************************
   Proto_type_Declare functions
**********************************************************************/



/**********************************************************************
   Main
**********************************************************************/
int main(int argc, char** argv){

  /* imageという変数を作る */
  cv::Mat image;


  /* sample.pngを読み込む(pathは各自の環境に合わせてください) */
  


  /* 生データを表示してみよう */



  /* グレースケール変換をしてみよう */



  /* 二値化をしてみよう */



  /* HSVを用いて緑色を抽出してみよう*/
  cv::Mat hsv_image;
  cv::Mat mask_green;
  cv::Mat output_hsv;
  cv::namedWindow("display_hsv",cv::WINDOW_AUTOSIZE);
  cvtColor(image,hsv_image,cv::COLOR_BGR2HSV);
  // cv::imshow("display_hsv",hsv_image);
  int green_hue_max = 75;
  int green_hue_min = 70;
  int saturation_max = 255;
  int saturation_min = 100;
  int value_max = 255;
  int value_min = 100;
  cv::Scalar green_max = cv::Scalar(green_hue_max, saturation_max, value_max);
  cv::Scalar green_min = cv::Scalar(green_hue_min, saturation_min, value_min);

  /*HSVの範囲で二値化する関数を探してみてください*/


  image.copyTo(output_hsv,mask_green);
  cv::imshow("display_hsv", output_hsv);

  cv::waitKey(0);
  return 0;
}