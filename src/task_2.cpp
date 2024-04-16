/**********************************************************************
   File    task_2.cpp
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
using namespace cv;
using namespace std;

int main() {
    // 動画ファイルを開く
    VideoCapture cap("/home/mogami/ais-project/catkin_ws/src/members/takeda_ros_pkgs/test/newcomer_opencv_2024/image_date/sample.mp4");
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open video file" << endl;
        return -1;
    }

    // 最初のフレームを背景画像として保持
    Mat background;
    cap >> background;


    // 手が画角から出たことを検出したかどうかを示すフラグ
    bool handEnteredFrame = false;
    bool after = false;

    while (true) {
        Mat frame;
        cap >> frame; // フレームをキャプチャ

        if (frame.empty()) {
            cerr << "Error: Blank frame grabbed" << endl;
            break;
        }


        // 手が画角から出たタイミングで背景差分を計算
        if (!handEnteredFrame) {
            // HSV色空間に変換
            cvtColor(frame, frame, COLOR_BGR2HSV);
            // 手が画角に入ったタイミングを判断
            Mat whitePixels;
            inRange(frame, Scalar(5, 100, 100), Scalar(15, 255, 255), whitePixels); // 二値化された白ピクセルのマスク
            cvtColor(frame, frame, COLOR_HSV2BGR);            
            int whitePixelCount = countNonZero(whitePixels);
            if (whitePixelCount > 200) {
                handEnteredFrame = true; // 手が画角に入ったことを検出
            }
        } 
        if(!handEnteredFrame && after) {
            // 背景差分を計算
            Mat diff;
            absdiff(frame, background, diff);

            // 背景差分画像を2値化
            Mat mask;
            threshold(diff, mask, 50, 255, THRESH_BINARY);

            // 検出された物体に色を重ねる処理
            frame.setTo(Scalar(0, 0, 255), mask); // 赤色を付ける (HSV空間での赤色)
        }

        // 手が画角から出たかどうかの判定
        if (handEnteredFrame) {
            // HSV色空間に変換
            cvtColor(frame, frame, COLOR_BGR2HSV);
            // 手が画角から出た場合に背景差分を行うためのフラグをリセット
            Mat whitePixels;
            inRange(frame, Scalar(5, 100, 100), Scalar(15, 255, 255), whitePixels); // 二値化された白ピクセルのマスク
            cvtColor(frame, frame, COLOR_HSV2BGR);
            int whitePixelCount = countNonZero(whitePixels);
            if (whitePixelCount < 200) {
                handEnteredFrame = false; // 手が画角から出たことを検出
                after = true;
            }
        }

        imshow("Frame", frame); // 結果を表示

        // ESCキーが押されたらループを抜ける
        if (waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}