//std
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
//opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {

	int z;
	float rho, theta, ct, st;
	Mat img, gray, bin, fil, fil2, edge;
	vector<Vec2f> lines;
	//Win用パス
	string path = "../../img_in/2.jpg";


	//read img
	img = cv::imread(path, 1);
	if (img.empty()) {
		cout << "読み込み失敗" << endl;
	}
	//read grayImg
	gray = imread(path, 0);

	//filter
	//ガウシアンフィルタ
	//GaussianBlur(gray, fil, Size(27, 27), 3);
	//メディアンフィルタ
	//medianBlur(gray, fil, 9);
	//高速エッジ保存画像平滑化フィルタ
	//edgePreservingFilter(gray, fil);

	//binarization
	//threshold(fil, bin, 210, 255, THRESH_BINARY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//medianBlur(bin, fil2, 31);


	//canny
	Canny(bin, edge, 80, 255);

	//houghLine
	HoughLines(edge, lines, 1, CV_PI / 180, 200);
	//HoughLinesP(edge, lines, 1, 3.14 / 180, 60);
	z = edge.cols;

	//lineDraw
	for (auto i = lines.begin(); i != lines.end(); i++) {
		rho = i[0][0];
		theta = i[0][1];
		ct = cos(theta);
		st = sin(theta);

		line(img, Point(rho*ct - z*st, rho*st + z*ct), Point(rho*ct + z*st, rho*st - z*ct), Scalar(0, 0, 255));
	}

	//write Img
	imwrite("../../img_out/2c.jpg", img);
	imwrite("../../img_out/2bin.jpg", bin);

}