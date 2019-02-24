#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include <fstream>
#include<vector>

vector<string> getImgName(string filename) {


	vector<string> a;
	ifstream infile;
	//infile.open("F:\0224\air\Img\LIST.TXT", ios::in);
	infile.open(filename, ios::in);

	if (infile) {

		while (!infile.eof())            // 若未到文件结束一直循环 
		{
			string tmp;
			getline(infile, tmp, '\n');//读取一行，以换行符结束，存入 a[] 中
			//cout << tmp << endl;
			a.push_back(tmp);
		}

	}
	else {

		cout << "no such file" << endl;
	}

	infile.close();

	return a;
}



void twoImgAdd(Mat &img,Mat &img_out)
{
	int rows = img.rows;
	int cols = img.cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			uchar t;
			if (img.channels() == 1)
			{
				t = img.at<uchar>(i, j);
				img.at<uchar>(i, j) = img.at<uchar>(i, cols - 1 - i);
				img.at<uchar>(i, cols - 1 - i) = t;
			}
			else if (img.channels() == 3 && img_out.channels() == 3)
			{
				//for (int k = 0; k < 3; k++)
				//{
				// //两张png直接相加也没什么问题，因为对于uchar类型来说，255+255=255
				//	img_out.at<Vec3b>(i, j)[k] =img.at<Vec3b>(i, j)[k]+img_out.at<Vec3b>(i, j)[k];
				//	//img_out.at<Vec3b>(i, cols - 1 - j)[k] = t;
				//	//cout << img_out.at<Vec3b>(i, j)[k] << " ";
				//}
				if (0 == img_out.at<Vec3b>(i, j)[0] && 0== img_out.at<Vec3b>(i, j)[1] && 0== img_out.at<Vec3b>(i, j)[2])
				{ 
					//说明是原来未标注的地方，将新标注的地方加载即可,否则不改变原来的标注
					img_out.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0];
					img_out.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1];
					img_out.at<Vec3b>(i, j)[2] =  img.at<Vec3b>(i, j)[2];
					//通道顺序为BGR
				}
			
		
			}

		}
	}
	//return img_out;
}

int main()
{
	// 读入一张图片（poyanghu缩小图）    
	//Mat img1 = imread("F:\\woman_1024_高斯噪声.png");
	string path = "F://0224//bus//label//" ;


	string filename = path +"LIST.TXT";
	
	vector<string> imgNameVec = getImgName(filename);

	Mat img1 = imread("F://0224//bus//0888_Fix.png");

	for (int i = 0; i < imgNameVec.size(); i++) {

		string ImgName = path+imgNameVec[i];
		Mat img2 = imread(ImgName);
		twoImgAdd(img1, img2);
		cv::imwrite("F://0224//bus//my_fixed_label//" + imgNameVec[i], img2);
		cout << "图片"+ImgName+"已保存" << endl;
	}

	//namedWindow("图片1");
	//imshow("图片1", img1);
	//waitKey(100000);
	
	//namedWindow("图片2");
	//imshow("img2", img2);
	//waitKey(10);

	system("pause");
	return 0;
}



