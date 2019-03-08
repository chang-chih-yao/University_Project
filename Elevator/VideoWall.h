#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv/cv.h"
#include <msclr\marshal_cppstd.h>
#include <string>

using namespace std;
using namespace cv;
using namespace System;

static Mat matnow[100];
static int change[100];
static int countx;
static char events[100][50];
extern string videos[100];

namespace Elevator_Scan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// VideoWall 的摘要
	/// </summary>
	public ref class VideoWall : public System::Windows::Forms::Form
	{
	public:
		VideoWall(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~VideoWall()
		{
			if (components)
			{
				delete components;
			}
		}
	public: array<PictureBox^>^ pic = gcnew array<PictureBox^>(100);
	public: array<Label^>^ lab = gcnew array<Label^>(100);
	public: array<Label^>^ nam = gcnew array<Label^>(100);


	public:
	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// VideoWall
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1274, 613);
			this->Name = L"VideoWall";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"即時總覽";
			this->Load += gcnew System::EventHandler(this, &VideoWall::VideoWall_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: void func(int a){
				array<Graphics^>^ graphics = gcnew array<Graphics^>(100);
				for (int i = 0; i < a; i++){
					graphics[i] = pic[i]->CreateGraphics();
					Controls->Add(pic[i]);
					Controls->Add(lab[i]);
					Controls->Add(nam[i]);
				}
				System::Drawing::RectangleF rect(0, 0, 216, 384);
				while (countx != a){
					for (int i = 0; i < a; i++){
						if (change[i] == 1){
							System::IntPtr ptr(matnow[i].ptr());
							Bitmap^ b = gcnew System::Drawing::Bitmap(matnow[i].cols, matnow[i].rows, matnow[i].step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
							graphics[i]->DrawImage(b, rect);
							System::String^ str = gcnew System::String(events[i]);
							lab[i]->Text = str;
							lab[i]->Refresh();
							nam[i]->Refresh();
							change[i] = 0;
						}
					}
				}
				this->Close();
	}
	public:void setlocation(int a){
			   int line = sqrt(a);
			   if (line > 2) line = 2;
			   for (int i = 0; i < a; i++){
				   pic[i]->Location = System::Drawing::Point(246 * (i / line) + 30, 444 * (i % line) + 30);
				   lab[i]->Location = System::Drawing::Point(246 * (i / line) + 30, 444 * (i % line) + 419);
				   nam[i]->Location = System::Drawing::Point(246 * (i / line) + 30, 444 * (i % line) + 15);
				   System::String^ str = i.ToString();
				  
				   nam[i]->Text = str;
			   }
			   int row = a / line;
			   if (a%line != 0) row++;

			   ClientSize = System::Drawing::Size(246*row+30, 444*line+45);
	}
	private: System::Void VideoWall_Load(System::Object^  sender, System::EventArgs^  e) {
				 for (int i = 0; i < 100; i++){
					pic[i] = gcnew PictureBox();
					pic[i]->Size = System::Drawing::Size(216, 384);
					pic[i]->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
					lab[i] = gcnew Label();
					lab[i]->AutoSize = true;
					lab[i]->Size = System::Drawing::Size(69, 12);
					lab[i]->TabIndex = 0;
					nam[i] = gcnew Label();
					nam[i]->AutoSize = true;
					nam[i]->Size = System::Drawing::Size(69, 12);
					nam[i]->TabIndex = 0;
				 }
	}
	};
}
