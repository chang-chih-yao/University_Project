// Elevator_Scan.cpp: 主要專案檔。

#include "stdafx.h"
#include "Myform.h"
#include "Allview.h"
#include "information.h"
#include "VideoWall.h"
#include <iostream>

#define Scalar_red_a Scalar(0, 70, 110)
#define Scalar_red_b Scalar(8, 255, 255)
#define Scalar_red_c Scalar(172, 70, 110)
#define Scalar_red_d Scalar(180, 255, 255)

#define Scalar_yello_a Scalar(0, 70, 220)
#define Scalar_yello_b Scalar(32, 255, 255)
#define Scalar_yello_c Scalar(180, 70, 220)
#define Scalar_yello_d Scalar(180, 255, 255)

#define left cvRect(0, 100, 350, 550)
#define right cvRect(370, 100, 350, 550)

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

HANDLE mutex;

static void download(const gpu::GpuMat& d_mat, vector<Point2f>& vec)
{
	vec.resize(d_mat.cols);
	Mat mat(1, d_mat.cols, CV_32FC2, (void*)&vec[0]);
	d_mat.download(mat);
}

void train(){
	vector<string> img_path;//输入文件名变量     
	vector<int> img_catg;  //标签    
	int nLine = 0;
	string buf;
	ifstream svm_data(file_path);//训练样本图片的路径都写在这个txt文件中,bat批处理  
	unsigned long n;
	while (svm_data)//将训练样本文件依次读取进来      
	{
		if (getline(svm_data, buf))    //将输入流svm_data中读到的字符存入buf中  
		{
			nLine++;
			if (nLine % 2 == 0)//注：奇数行是图片全路径，偶数行是标签   
			{
				img_catg.push_back(atoi(buf.c_str()));
				//atoi将字符串转换成整型，标志(0,1，2，...，9)，注意这里至少要有两个类别，否则会出错    
				// 函数声明：const char *c_str(); c_str()函数返回一个指向正规字符串的指针, 内容与本字符串相同  
			}
			else
			{
				img_path.push_back(buf);//图像路径
			}
		}
	}
	svm_data.close();//关闭文件      
	//system("PAUSE");
	CvMat *data_mat, *res_mat;  //定义样本矩阵，类型矩阵    
	int nImgNum = nLine / 2; //nImgNum：横坐标是样本数量，只有文本行数的一半，另一半是标签    

	data_mat = cvCreateMat(nImgNum, 324, CV_32FC1);  //样本矩阵  
	//第二个参数，即矩阵的列是由下面的descriptors的大小决定的，可以由descriptors.size()得到，  
	//且对于不同大小的输入训练图片，这个值是不同的    
	cvSetZero(data_mat);
	//类型矩阵,存储每个样本的类型标志      
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);

	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(32, 32), 8, 3);
	//需要分析的图片，这里默认设定图片是28*28大小，所以上面定义了324，如果要更改图片大小，  
	//可以先用debug查看一下descriptors是多少，然后设定好再运行      

	//处理HOG特征    
	for (string::size_type i = 0; i != img_path.size(); i++)
	{
		src = cvLoadImage(img_path[i].c_str(), 1);
		if (src == NULL)
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}

		//cout << " 處理: " << img_path[i].c_str() << endl;

		cvResize(src, trainImg); //读取图片，归一化处理
		HOGDescriptor *hog = new HOGDescriptor(cvSize(32, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float>descriptors;//存放结果，数组
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++) //迭代器
		{
			cvmSet(data_mat, i, n, *iter);//存储HOG特征到data_mat矩阵中
			n++;
		}
		cvmSet(res_mat, i, 0, img_catg[i]);
		//cout << " 處理完畢:" << img_path[i].c_str() << " " << img_catg[i] << endl;
	}



	CvSVM svm;//新建一个SVM        
	CvSVMParams param;//SVM训练相关参数    
	CvTermCriteria criteria;

	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);

	//data_mat样本矩阵存储上面提取到的HOG特征，存储 m 个样本的 n 个特征， res_mat 是标签矩阵  
	svm.train(data_mat, res_mat, NULL, NULL, param);
	svm.save("HOG_SVM_DATA.xml");
	cout << "HOG_SVM_DATA is created." << endl;
}

DWORD WINAPI threadfunc(int tik){

	struct mystruct{
		int gar = 0;
		int frame_num = 1;
		int initial_floor = 1;
	} frame;

	string video_name = video[tik];
	

	//system("PAUSE");


	/*********************************************************************************************************/



	VideoCapture cap(video_name);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if (!cap.isOpened())
		return -1;
	int fps = cap.get(CV_CAP_PROP_FPS);
	char name[30];
	sprintf(name, "video-%d.avi", tik);
	VideoWriter out_capture(name, CV_FOURCC('M', 'J', 'P', 'G'), fps, Size(720, 1280), true);


	char face_cascade_name[50] = "haarcascade_mcs_upperbody.xml";
	//sprintf(face_cascade_name, "haarcascade_mcs_upperbody.xml", tik);
	gpu::CascadeClassifier_GPU face_cascade;
	if (!face_cascade.load(face_cascade_name)){ printf("--(!)Error loading\n"); return -1; };
	Mat img;
	cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());

	int count = 0, floor = -1;
	time_t t;
	//namedWindow("video capture", CV_WINDOW_AUTOSIZE);

	vector<struct mystruct> arr;
	vector<int> floors;
	vector<int> humans;
	frame.gar = 1;
	frame.frame_num = 0;
	frame.initial_floor = 1;
	int now_num = 0;
	int min_digit_len = 999;
	int max_digit_len = 5;
	int min_temp = 0;
	int floor_change_cou = 0;
	int change_floor = 0;  // a label
	int next_floor;
	int range_bound_x = 0, range_bound_y = 0, range_x_l = 1, range_x_r = 719, range_y_up = 1, range_y_down = 599;

	Mat hsv, mask, hue, hist, backproj, gbackground, background_8U, background_32F, target, gray;
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;
	int hsize = 32;
	int initw[10], inith[10];
	int elavator_stay = 1;
	int ledtop = 0;
	int human = 0;
	int newtrack[10];
	int shiftx[10][10] = { 0 };
	int shifty[10][10] = { 0 };

	gpu::GpuMat prevgray, nowgray;
	gpu::GpuMat status[10];
	prevgray.release();
	Rect trackWindow[10];
	vector<Point2f> points1[10];        // point0为特征点的原来位置，point1为特征点的新位置
	vector<Point2f> points2[10];
	gpu::GpuMat prevpoint[10];
	gpu::GpuMat nowpoint[10];
	vector<Point2f> initial[10];        // 初始化跟踪点的位置
	vector<Point2f> features[10];
	int maxCount = 500;        // 检测的最大特征数
	double qLevel = 0.01;        // 特征检测的等级
	double minDist = 10.0;        // 两特征点之间的最小距离
	//vector<uchar> status[10];        // 跟踪特征的状态，特征的流发现为1，否则为0
	//vector<float> err[10];
	int origin_x, origin_y;
	CvSVM svm_p;
	svm_p.load("HOG_SVM_DATA.xml");
	while (true)
	{
		if (!cap.read(img))
		{
			cout << "finish" << endl;
			//system("pause");
			break;
		}
		//cap >> img;
		if (!img.data)
			break;
		if (img.empty()){
			break;
		}
		frame.frame_num++;           // 影片中真正的禎數

		transpose(img, img);                                  // 旋轉畫面(順時針90度)
		flip(img, img, 1);

		IplImage *image = &IplImage(img);
		
		if (ledside[tik] == 1) cvSetImageROI(image, right);
		else if (ledside[tik] == 1) cvSetImageROI(image, left);

		Mat detect, track;
		img.copyTo(detect);
		img.copyTo(track);

		if (frame.frame_num == 1){
			img.copyTo(gbackground);
			cvtColor(gbackground, gbackground, CV_BGR2GRAY);
			
			gbackground.convertTo(background_32F, CV_32F);
			//range_x_l = 1, range_x_r = img.cols / 2, range_y_up = 1, range_y_down = img.rows / 2;
		}
		background_32F.convertTo(background_8U, CV_8U);


		//Mat number = Mat(img, Rect(img.cols / 2, 0, img.cols / 2, 2 * img.rows / 5));

		Mat hsvImg, skinImg, skinImg2;
		Mat number(image, 0);
		Mat mask = Mat::zeros(number.rows, number.cols, CV_8U);
		cvtColor(number, hsvImg, CV_BGR2HSV);

		if (ledcolor[tik] == 1){
			inRange(hsvImg, Scalar_red_a, Scalar_red_b, skinImg);
			inRange(hsvImg, Scalar_red_c, Scalar_red_d, skinImg2);
		}
		else if (ledcolor[tik] == 2){
			inRange(hsvImg, Scalar_yello_a, Scalar_yello_b, skinImg);
			inRange(hsvImg, Scalar_yello_c, Scalar_yello_d, skinImg2);
		}

		mask = skinImg + skinImg2;
		//imshow("OpenCV Demo", skinImg);
		//string maskshow = video_name;
		//maskshow += "_mask";
		//imshow(maskshow, mask); //show mask
		//imshow("mat", mat);   //show原圖片
		//imshow("result", dst);//show結果

		/*----------------------------------------------------------------- contour ----------------------------------------------------------------------*/
		int contour_num = 0;

		//bool label_num = true;            // 一個frame只會有一個數字，判斷完一個數字，label就會變成false，以防框出其他非數字的影像

		Mat threshold_img;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		threshold(mask, threshold_img, 125.0, 255.0, THRESH_BINARY);
		//將skin_img二值化

		findContours(threshold_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		//在threshold_img影像中尋找所有的輪廓

		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		int lednum = 0;
		/*vector<vector<Point> > contours_poly2(contours.size());
		vector<Rect> boundRect2(contours.size());

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly2[i], 1, true);
			//計算可以包含輪廓的最小長方形區域

			boundRect2[i] = boundingRect(Mat(contours_poly2[i]));
			if (boundRect2[i].area() > 120)
				contour_num++;
		}*/
		//cout << contour_num << endl;

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 1, true);
			//計算可以包含輪廓的最小長方形區域

			boundRect[i] = boundingRect(Mat(contours_poly[i]));

			Scalar color = Scalar(0, 255, 0);
			Scalar color_red = Scalar(0, 0, 255);

			int len = boundRect[i].br().x - boundRect[i].tl().x;                                        // 框起來的長方形"左右寬"
			int w = boundRect[i].br().y - boundRect[i].tl().y;                                          // 框起來的長方形"上下高"

			Point p1(range_x_l, range_y_up);
			Point p2(range_x_r, range_y_down);

			if (frame.gar >= 6) rectangle(number, p1, p2, color_red, 2, 8, 0);
			if (frame.gar <= 5) min_digit_len = w;
			if (boundRect[i].area() > 80 && boundRect[i].tl().x <= range_x_r && boundRect[i].tl().x >= range_x_l && boundRect[i].tl().y <= range_y_down && boundRect[i].tl().y >= range_y_up){
				lednum++;
				if (w >= min_digit_len - 3)  //長方形框框，畫在影像上
				{
					drawContours(number, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
					rectangle(number, boundRect[i].tl(), boundRect[i].br(), color, 1, 8, 0);                   // boundRect[i].tl()是左上角，boundRect[i].br()是右下角
					//printf("%d: %d  %d  %d\n", gar, boundRect[i].br().y - boundRect[i].tl().y, boundRect[i].area(), min_digit_len);
					int qq;
					if (w >= min_digit_len + 3) qq = (min_digit_len - len) / 2;
					else qq = (w - len) / 2;
					//IplImage *ffff = &IplImage(mask);
					Mat final_img;
					if (w >= min_digit_len + 3)  final_img = Mat(mask, Rect(boundRect[i].tl().x - qq, boundRect[i].tl().y + (w - min_digit_len), min_digit_len + 1, min_digit_len));   // 截取圖片(並置中)，依序，左上角x，左上角y，長，寬
					else final_img = Mat(mask, Rect(boundRect[i].tl().x - qq, boundRect[i].tl().y, w + 1, w));   // 截取圖片(並置中)，依序，左上角x，左上角y，長，寬
					//Mat temp(ffff, 0);

					if (w >= min_digit_len + 3) resize(final_img, final_img, Size(), 32.0 / (min_digit_len + 1), 32.0 / (min_digit_len));
					else resize(final_img, final_img, Size(), 32.0 / (w + 1), 32.0 / (w));         // 重新調整大小，讓他變成32*32
					//IplImage *final_img = &IplImage(temp);
					//cout << final_img->height << " " << final_img->width<<endl;
					//cvShowImage("Red", ffff);
					//imshow("GG", final_img);

					/*------------------------------------------------ 辨識 -------------------------------------------------*/

					//IplImage *image = &IplImage(dst);
					//cvSetImageROI(image, cvRect(0, 0, 400, 400));

					HOGDescriptor *hogg = new HOGDescriptor(cvSize(32, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
					vector<float>descriptors;
					hogg->compute(final_img, descriptors, Size(1, 1), Size(0, 0));
					CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);

					int n = 0;
					for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++){
						cvmSet(SVMtrainMat, 0, n, *iter);
						n++;
					}

					int ret = svm_p.predict(SVMtrainMat);
					if (ret == 10) continue;             // ret = 0 代表偵測到箭頭
					else if (ret == 11) continue;
					else {                                                          // 圖片是數字
						//cvShowImage("GG", final_img);
						if (frame.gar <= 5){
							min_temp += w;                                                                      // 分析前5張數字的圖片的平均"長度"
							range_bound_x += boundRect[i].tl().x;
							range_bound_y += boundRect[i].tl().y;
							frame.initial_floor = ret;
						}

						if (ret < (frame.initial_floor - 1) || ret >(frame.initial_floor + 1)) continue;                          // 如果樓層變化超過1，則視為誤差值

						cout << "The elevator is at " << ret << " floor." << endl;

						if (now_num != ret){
							printf("!!!!!!!!!!!!!!!!!! change floor at %d (%d)\n", frame.gar, frame.frame_num);
							if (change_floor == 1) change_floor = 0;  // label set, 如果連續兩個frame(gar)都有change floor，代表是誤差，floor_change_cou不用歸零
							else{
								change_floor = 1;             // label
								next_floor = frame.gar + 1;   // 如果下一個frame，數字沒有跳回來，floor_change_cou歸零
							}
							arr.push_back(frame);
							floors.push_back(ret);
							humans.push_back(human);
						}

						if (change_floor == 1 && next_floor == frame.gar) {
							floor_change_cou = 0;   // 進入這個if，代表，上一個frame有change floor，但是這個frame沒有change，所以歸零
							change_floor = 0;
						}

						now_num = ret;
						floor_change_cou++;
						frame.gar++;


						if (floor_change_cou == 10 && ret != frame.initial_floor) {
							elavator_stay = 1;
							for (int k = 0; k < 10; k++)
								newtrack[k] = 0;
						}

						if (floor_change_cou >= 10 && change_floor == 0) frame.initial_floor = ret;          // 當連續出現10個數字，都沒變過，就代表樓層數字已經穩定

						if (frame.gar == 6){
							min_digit_len = min_temp / 5;                                           // 更新min_digit_len的值
							range_bound_x /= 5;
							range_bound_y /= 5;
							if (range_bound_x - 60 <= 1){
								range_x_l = 1;
								range_x_r = range_bound_x + 60;
							}
							else if (range_bound_x + 60 >= 349){
								range_x_l = range_bound_x - 60;
								range_x_r = 349;
							}
							else {
								range_x_l = range_bound_x - 60;
								range_x_r = range_bound_x + 60;
							}
							if (range_bound_y - 70 <= 1){
								range_y_up = 1;
								range_y_down = range_bound_y + 70;
							}
							else if (range_bound_y + 70 >= 549){
								range_y_up = range_bound_y - 70;
								range_y_down = 549;
							}
							else{
								range_y_up = range_bound_y - 70;
								range_y_down = range_bound_y + 70;
							}
						}
					}
				}
			}
		}
		if (lednum > 1)
			elavator_stay++;

		/*****************************************************************背景去除********************************************************/
		Mat frame_gray, catchgray;
		int upper_body = 0;
		Rect *location;
		Mat downloadmat;
		Mat grayt, foreground, diff;
		Rect select[10];
		int man = 0;

		if (elavator_stay > fps * 1.3){
			cvtColor(track, grayt, CV_BGR2GRAY);
			//IplImage smooth = IplImage(grayt);
			//cvSmooth(&smooth, &smooth, CV_GAUSSIAN, 5, 0, 0);
			//grayt = cvarrToMat(&smooth);
			//absdiff(background_8U, grayt, foreground);
			//threshold(foreground, foreground, 20, 255.0, CV_THRESH_BINARY);
			//accumulateWeighted(grayt, background_32F, 0.01, foreground);
			//erode(foreground, foreground, Mat(), Point(-1, -1), 3);
			imshow("origin", grayt);
			imshow("background", background_8U);
			uchar* p,*q;
			for (int i = 0; i < grayt.rows; i++){
				p = background_8U.ptr<uchar>(i);
				q = grayt.ptr<uchar>(i);
				for (int j = 1; j < grayt.cols; j++){
					if (abs(p[j] - q[j]) < 20)
						q[j] = 255;
				}
			}

			//track.copyTo(diff, foreground);
			imshow("foreground", grayt);
			//grayt.convertTo(background_32F, CV_32F);
			cvtColor(detect, frame_gray, CV_BGR2GRAY);


			/*******************************************************抓人*******************************************************************/
			man = 0;
			//cvtColor(track, frame_gray, CV_BGR2GRAY);
			equalizeHist(frame_gray, catchgray);
			//-- Detect faces
			cv::gpu::GpuMat img_gpu(catchgray);
			cv::gpu::GpuMat result;

			WaitForSingleObject(mutex, INFINITE);
			upper_body = face_cascade.detectMultiScale(img_gpu, result, Size(500, 500), Size(300, 300), 1.1, 6);
			ReleaseMutex(mutex);

			result.colRange(0, upper_body).download(downloadmat);
			location = downloadmat.ptr<Rect>();

			for (int i = 0; i < upper_body; i++)
			{
				//Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);	
				if (location[i].area() > 100000 && location[i].tl().y < img.rows / 2){
					rectangle(detect, location[i], Scalar(255, 0, 255));
					select[man] = Rect(location[i].tl(), location[i].br());
					man++;
					//imshow("fff", Mat(track, select[man - 1]));
				}
				rectangle(detect, location[i], Scalar(0, 0, 0));

				//ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 2, 8, 0);
				//-- In each face, detect eye
			}
			//open--;
		}


		/****************************************************追蹤******************************************************************/
		gpu::PyrLKOpticalFlow of;
		gpu::GoodFeaturesToTrackDetector_GPU gftt(maxCount, qLevel, minDist);

		if (man > 0 || human > 0){
			cvtColor(track, frame_gray, CV_BGR2GRAY);
			nowgray.upload(frame_gray);

			for (int m = 0; m < man; m++){
				int repeat = 0;
				//if (select[m].height > )

				select[m].x = select[m].x + select[m].width / 4;
				select[m].y = select[m].y + select[m].height / 8;
				select[m].width /= 2;
				select[m].height /= 2;

				/*if (select[m].y < ledtop)
				continue;*/

				for (int n = 0; n < human; n++){
					int c = 0;
					if (select[m].x >= trackWindow[n].x - 100 && select[m].x + select[m].width <= trackWindow[n].x + trackWindow[n].width + 100 && select[m].y >= trackWindow[n].y - 100 && select[m].y + select[m].height <= trackWindow[n].y + trackWindow[n].height + 100){
						repeat = 1;
						break;
					}
					if (select[m].x - 100 <= trackWindow[n].x  && select[m].x + select[m].width + 100 >= trackWindow[n].x + trackWindow[n].width  && select[m].y - 100 <= trackWindow[n].y  && select[m].y + select[m].height + 50 >= trackWindow[n].y + trackWindow[n].height){
						repeat = 1;
						break;
					}
					if ((select[m].x - 100 <= trackWindow[n].x  && select[m].x + select[m].width + 100 >= trackWindow[n].x + trackWindow[n].width) || (select[m].x >= trackWindow[n].x - 100 && select[m].x + select[m].width <= trackWindow[n].x + trackWindow[n].width + 100)){
						repeat = 1;
						break;
					}
				}
				if (repeat == 0 && select[m].x > 0 && select[m].y > 0){
					target = Mat(frame_gray, select[m]);
					origin_x = select[m].x;
					origin_y = select[m].y;
					//imshow("target", target);
					gpu::GpuMat wanttrack(target);
					features[human].clear();
					WaitForSingleObject(mutex, INFINITE);
					gftt(wanttrack, prevpoint[human]);
					ReleaseMutex(mutex);
					download(prevpoint[human], points1[human]);
					newtrack[human] = 1;
					initw[human] = select[m].width;
					inith[human] = select[m].height;
					for (int i = 0; i < prevpoint[human].cols; i++){
						points1[human][i].x += origin_x;
						points1[human][i].y += origin_y;
					}
					Mat temppoint = Mat(points1[human]);
					temppoint = temppoint.t();
					prevpoint[human].upload(temppoint);
					//prevpoint[human].reshape(prevpoint[human].channels(), 1);
					human++;
				}
			}
			// 添加特征点


			if (prevgray.empty())
				prevgray.upload(frame_gray);
			/*Mat ff(prevgray);
			Mat dd(nowgray);
			imshow("prev", ff);
			imshow("now", dd);*/
			// l-k光流法运动估计
			for (int n = 0; n < human && n >= 0; n++){
				//calcOpticalFlowPyrLK(prevgray, frame_gray, points1[n], points2[n], status[n]);
				WaitForSingleObject(mutex, INFINITE);
				of.sparse(prevgray, nowgray, prevpoint[n], nowpoint[n], status[n]);
				ReleaseMutex(mutex);
				vector<uchar> stat;
				stat.resize(status[n].cols);
				Mat mat(1, status[n].cols, CV_8UC1, (void*)&stat[0]);
				status[n].download(mat);
				download(nowpoint[n], points2[n]);
				//download(prevpoint[n], points1[n]);
				// 去掉一些不好的特征点
				int k = 0, sum_x = 0, sum_y = 0, j = 0;
				int max_x = 0, min_x = 0, max_y = 0, min_y = 0;
				//cout << points2[n].size() << " " << stat.size() << endl;
				for (size_t i = 0; i < points2[n].size(); i++)
				{
					if (stat[i] == 1 && (abs(points1[n][i].x - points2[n][i].x) + abs(points1[n][i].y - points2[n][i].y) < 25))
					{
						points2[n][k++] = points2[n][i];
						if (points2[n][i].x > max_x)
							max_x = points2[n][i].x;
						else if (points2[n][i].x < min_x)
							min_x = points2[n][i].x;
						if (points2[n][i].y > max_y)
							max_y = points2[n][i].y;
						else if (points2[n][i].y < min_y)
							min_x = points2[n][i].y;
						sum_x += points2[n][i].x;
						sum_y += points2[n][i].y;
					}
				}

				if (k <= 2)
					j = 0;
				else{
					int avg_x = (sum_x - min_x - max_x) / k;
					int avg_y = (sum_y - min_y - max_y) / k;
					int tlx = avg_x - 100, tly = avg_y - 100, brx = avg_x + 100, bry = avg_y + 100;
					if (tlx < 0)
						tlx = 0;
					if (brx > img.cols)
						brx = img.cols;
					if (tly < 0)
						tly = 0;
					if (bry > img.rows)
						bry = img.rows;
					for (int i = 0; i < k; i++){
						if (points2[n][i].x > tlx && points2[n][i].x < brx && points2[n][i].y > tly && points2[n][i].y < bry){
							//initial[n][j] = initial[n][i];
							points2[n][j++] = points2[n][i];
						}
					}

					Rect testWindow = boundingRect(Mat(points2[n]));
					if (testWindow.width < initw[n] / 3 && newtrack[n]  == 0)
						j = 0;

					shiftx[n][frame.frame_num % 10] = abs(testWindow.x - trackWindow[n].x) - abs(testWindow.x + testWindow.width - (trackWindow[n].x + trackWindow[n].width));
					shifty[n][frame.frame_num % 10] = abs(testWindow.y - trackWindow[n].y) - abs(testWindow.y + testWindow.height - (trackWindow[n].y + trackWindow[n].height));
					if (testWindow.width < initw[n] / 2 && newtrack[n] == 1){
						//system("pause");
						int diffx = shiftx[n][frame.frame_num % 10];
						if (diffx > 0){
							if (testWindow.x - (initw[n] - testWindow.width) > 0){
								//cout << testWindow.x << " " << testWindow.width << endl;
								testWindow.x = testWindow.x - (initw[n] - testWindow.width);
								testWindow.width = initw[n];
							}
							else{
								testWindow.width += testWindow.x;
								testWindow.x = 0;
							}
						}
						else{
							if (testWindow.x + initw[n] < track.cols)
								testWindow.width = initw[n];
							else
								testWindow.width = track.cols - testWindow.x - 1;
						}
						gpu::GpuMat newfeature, addfeature_gpu;
						Mat addfeature(frame_gray, testWindow);
						addfeature_gpu.upload(addfeature);
						vector<Point2f> newp;
						WaitForSingleObject(mutex, INFINITE);
						gftt(addfeature_gpu, newfeature);
						ReleaseMutex(mutex);
						download(newfeature, newp);
						for (int c = 0; c < newp.size(); c++){
							newp[c].x += testWindow.x;
							newp[c].y += testWindow.y;
						}
						points2[n].insert(points2[n].end(), newp.begin(), newp.end());
						//initial[n].insert(initial[n].end(), newp.begin(), newp.end());
						j += newp.size();
					}
					if (testWindow.height < inith[n] / 2 && newtrack[n] == 1){
						int diffy = shifty[n][frame.frame_num % 10];
						if (diffy > 0){
							if (testWindow.y - (inith[n] - testWindow.height) > 0){
								testWindow.y = testWindow.y - (inith[n] - testWindow.height);
								testWindow.height = inith[n];
							}
							else{
								testWindow.height += testWindow.y;
								testWindow.y = 0;
							}
						}
						else{
							if (testWindow.y + inith[n] < track.rows)
								testWindow.height = inith[n];
							else
								testWindow.height = track.rows - testWindow.y - 1;
						}
						gpu::GpuMat newfeature, addfeature_gpu;
						Mat addfeature(frame_gray, testWindow);
						addfeature_gpu.upload(addfeature);
						vector<Point2f> newp;
						WaitForSingleObject(mutex, INFINITE);
						gftt(addfeature_gpu, newfeature);
						ReleaseMutex(mutex);
						download(newfeature, newp);

						for (int c = 0; c < newp.size(); c++){
							newp[c].x += testWindow.x;
							newp[c].y += testWindow.y;
						}
						points2[n].insert(points2[n].end(), newp.begin(), newp.end());
						//initial[n].insert(initial[n].end(), newp.begin(), newp.end());
						j += newp.size();
					}
					trackWindow[n] = testWindow;
					points1[n].resize(j);
					points2[n].resize(j);
				}
				for (int d = 0; d < n; d++){
					if (trackWindow[d].x < trackWindow[n].x && trackWindow[d].x + trackWindow[d].width > trackWindow[n].x + trackWindow[n].width){
						j = 0;
						break;
					}
				}

				if (j < 10){
					//cout << j << endl;
					points1[n].clear();
					points1[n].resize(points1[human - 1].size());
					swap(points1[n], points1[human - 1]);
					points1[human - 1].clear();
					points2[n].clear();
					points2[n].resize(points2[human - 1].size());
					swap(points2[n], points2[human - 1]);
					points2[human - 1].clear();
					swap(newtrack[n], newtrack[human - 1]);
					initw[n] = initw[human - 1];
					inith[n] = inith[human - 1];
					swap(trackWindow[n], trackWindow[human - 1]);
					memset(&shiftx[n], 0, 10 * sizeof(int));
					memset(&shiftx[n], 0, 10 * sizeof(int));
					swap(shiftx[n], shiftx[human - 1]);
					swap(shifty[n], shifty[human - 1]);
					swap(nowpoint[n], nowpoint[human - 1]);
					swap(prevpoint[n], prevpoint[human - 1]);
					human--;
					n--;
					cout << "OUT" << endl;
					//cout << n << " " << human;
				}
				else{
					// 显示特征点和运动轨迹
					//if (newtrack[n] == 0){
						char no[5];
						sprintf(no, "%d", n);
						Rect drawrect;
						if (trackWindow[n].x > 50)
							drawrect.x = trackWindow[n].x - 50;
						else
							drawrect.x = 0;
						if (trackWindow[n].y > 50)
							drawrect.y = trackWindow[n].y - 50;
						else
							drawrect.y = 0;
						if (trackWindow[n].x + trackWindow[n].width + 100 < track.cols)
							drawrect.width = trackWindow[n].width + 100;
						else
							drawrect.width = track.cols - trackWindow[n].x;
						if (trackWindow[n].y + trackWindow[n].height + 100 < track.rows)
							drawrect.height = trackWindow[n].height + 100;
						else
							drawrect.height = track.cols - trackWindow[n].y;

						rectangle(track, drawrect, Scalar(255, 255, 255), 3);
						//putText(track, no, drawrect.tl(), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255));
						for (size_t i = 0; i < points2[n].size(); i++)
						{
							//line(track, initial[n][i], points[n][1][i], Scalar(0, 0, 255));
							//circle(track, points2[n][i], 3, Scalar(255, 0, 0), -1);
						}
					//}
					// 把当前跟踪结果作为下一此参考
					Mat temppoint = Mat(points2[n]);
					temppoint = temppoint.t();
					prevpoint[n].upload(temppoint);
					swap(points2[n], points1[n]);
				}
			}
			swap(prevgray, nowgray);
		}

		//elavator_stay++;
		//imshow("number", number);
		//cout << "Frame is " << fram_num << endl;
		//cout << "Now tracking : " << human << endl;
		cv::resize(track, track, cv::Size(720, 1280));
		out_capture.write(track);
		if (change[tik] == 0){
			matnow[tik] = track;
			change[tik] = 1;
			sprintf(events[tik], "樓層: %d  人數: %d", frame.initial_floor, human);
		}
		//cout << elavator_stay << endl;
		//imshow(video_name, detect);
		//imshow("track", track);
		waitKey(1);
	}

	out_capture.release();

	int prev = -1;
	for (int i = 0; i < arr.size(); i++)
	{
		if ((i + 1) != arr.size() && arr[i + 1].gar - arr[i].gar <= 3){
			i++;
			continue;
		}
		if (prev >= 0){
			char tmp[100];
			cout << arr[prev].frame_num / fps << " 秒時位於 " << floors[prev] << " 樓層，原本有 " << humans[prev] << " 人，最後人數為 " << humans[i] << " 人。" << endl;
			sprintf(tmp, "%d 秒時位於 %d 樓層，原本有 %d 人，最後人數為 %d 人。\r\n", arr[prev].frame_num / fps, floors[prev], humans[prev], humans[i]);
			strcat(result[tik], tmp);
		}
		prev = i;
	}
	char tmp[1000];
	cout << arr[prev].frame_num / fps << " 秒時位於 " << floors[prev] << " 樓層，原本有 " << humans[prev] << " 人，最後人數為 " << human << " 人。" << endl;
	sprintf(tmp, "%d 秒時位於 %d 樓層，原本有 %d 人，最後人數為 %d 人。\r\n", arr[prev].frame_num / fps, floors[prev], humans[prev], human);
	strcat(result[tik], tmp);
	countx++;
	//system("pause");
}

[STAThread]
int main(array<System::String ^> ^args)
{
	mutex = CreateMutex(NULL, FALSE, NULL);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Elevator_Scan::MyForm form;
	Application::Run(%form);
	Console::WriteLine(L"Hello World");
}
