//std
#include <iostream>

//opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
    Mat img,gray,bin,edge;
    vector<Vec4i> lines;
    string path = "/Users/sho/Google ドライブ/OpenCV資料/img/5.jpg";
    //read img
    img = cv::imread(path, 1);
    if (img.empty()) {
        cout << "読み込み失敗" << endl;
    }
    //read grayImg
    gray = imread(path, 0);
    //binarization
    threshold(gray, bin, 190, 255, THRESH_BINARY);
//    threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
    //canny
    Canny(bin, edge, 125, 255);
    //houghLine
    HoughLinesP(edge, lines, 1, 3.14/180, 60);
    //lineDraw
    for(auto i = lines.begin(); i != lines.end(); i++){
        line(img, Point(i[0][0],i[0][1]), Point(i[0][2],i[0][3]), Scalar(0,0,255));
    }
    //write Img
    imwrite("/Users/sho/Google ドライブ/OpenCV資料/img/5b.jpg", img);
    imwrite("/Users/sho/Google ドライブ/OpenCV資料/img/5bin.jpg", bin);
    imwrite("/Users/sho/Google ドライブ/OpenCV資料/img/5edge.jpg", edge);
    
    
    return 0;
}
