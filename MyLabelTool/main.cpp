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

		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			string tmp;
			getline(infile, tmp, '\n');//��ȡһ�У��Ի��з����������� a[] ��
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
				// //����pngֱ�����Ҳûʲô���⣬��Ϊ����uchar������˵��255+255=255
				//	img_out.at<Vec3b>(i, j)[k] =img.at<Vec3b>(i, j)[k]+img_out.at<Vec3b>(i, j)[k];
				//	//img_out.at<Vec3b>(i, cols - 1 - j)[k] = t;
				//	//cout << img_out.at<Vec3b>(i, j)[k] << " ";
				//}
				if (0 == img_out.at<Vec3b>(i, j)[0] && 0== img_out.at<Vec3b>(i, j)[1] && 0== img_out.at<Vec3b>(i, j)[2])
				{ 
					//˵����ԭ��δ��ע�ĵط������±�ע�ĵط����ؼ���,���򲻸ı�ԭ���ı�ע
					img_out.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0];
					img_out.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1];
					img_out.at<Vec3b>(i, j)[2] =  img.at<Vec3b>(i, j)[2];
					//ͨ��˳��ΪBGR
				}
			
		
			}

		}
	}
	//return img_out;
}

int main()
{
	// ����һ��ͼƬ��poyanghu��Сͼ��    
	//Mat img1 = imread("F:\\woman_1024_��˹����.png");
	string path = "F://0224//bus//label//" ;


	string filename = path +"LIST.TXT";
	
	vector<string> imgNameVec = getImgName(filename);

	Mat img1 = imread("F://0224//bus//0888_Fix.png");

	for (int i = 0; i < imgNameVec.size(); i++) {

		string ImgName = path+imgNameVec[i];
		Mat img2 = imread(ImgName);
		twoImgAdd(img1, img2);
		cv::imwrite("F://0224//bus//my_fixed_label//" + imgNameVec[i], img2);
		cout << "ͼƬ"+ImgName+"�ѱ���" << endl;
	}

	//namedWindow("ͼƬ1");
	//imshow("ͼƬ1", img1);
	//waitKey(100000);
	
	//namedWindow("ͼƬ2");
	//imshow("img2", img2);
	//waitKey(10);

	system("pause");
	return 0;
}



