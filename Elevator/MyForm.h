#pragma once
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <msclr\marshal_cppstd.h>
#include "Allview.h"
#include "information.h"
#include "VideoWall.h"
#include <queue>

#define MAX_SEM_COUNT 100
#define THREADCOUNT 12

#define file_path "hb.txt"

using namespace std;
using namespace cv;

DWORD WINAPI threadfunc(int tik);
extern void train();
static string video[100];
static string videos[100];
static int ledside[100];
static int ledcolor[100];
static string backpic[100];

namespace Elevator_Scan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label4;



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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(31, 70);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 42);
			this->button1->TabIndex = 0;
			this->button1->Text = L"新增";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button2->Location = System::Drawing::Point(364, 399);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(102, 54);
			this->button2->TabIndex = 1;
			this->button2->Text = L"執行";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(192, 70);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(449, 304);
			this->listBox1->TabIndex = 2;
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button3->Location = System::Drawing::Point(31, 152);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(94, 42);
			this->button3->TabIndex = 3;
			this->button3->Text = L"更改輸入設定";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(12, 227);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"當前設定:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(28, 265);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(122, 15);
			this->label2->TabIndex = 5;
			this->label2->Text = L"LED位置 : 右上方";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(28, 308);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(107, 15);
			this->label3->TabIndex = 6;
			this->label3->Text = L"LED顏色 : 紅色";
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button4->Location = System::Drawing::Point(690, 70);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(94, 42);
			this->button4->TabIndex = 7;
			this->button4->Text = L"分類器訓練";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(687, 141);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 15);
			this->label4->TabIndex = 8;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(813, 495);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"大量電梯監視器影像事件辨識平行處理系統";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	Allview^ check = gcnew Allview();;
	Elevator_Scan::VideoWall form1;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
					 listBox1->Items->Add(openFileDialog1->FileName);
					 ledside[listBox1->Items->Count - 1] = check->get_side();
					 ledcolor[listBox1->Items->Count - 1] = check->get_color();
					 backpic[listBox1->Items->Count - 1] = check->get_back();
				 }
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 clock_t start, end;
				 form1.Show();
				 Elevator_Scan::information form2;
				 HANDLE aThread[100];
				 DWORD ThreadID;
				 //viewall = gcnew Allview();
				 memset(change, 0, 100);
				 start = clock();
				 for (int i = 0; i < listBox1->Items->Count; i++){
					 std::string str = msclr::interop::marshal_as<std::string>(listBox1->Items[i]->ToString());
					 char *strrr = new char[str.length() + 1];
					 strcpy(strrr, str.c_str());
					 video[i] = strrr;
					 videos[i] = strrr;
					 aThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadfunc, (LPVOID)i, 0, &ThreadID);
					 form2.comboBox1->Items->Add(listBox1->Items[i]->ToString());
				 }

				 form1.setlocation(listBox1->Items->Count);
				 form1.func(listBox1->Items->Count);

				 WaitForMultipleObjects(listBox1->Items->Count, aThread, TRUE, INFINITE);
				 for (int i = 0; i < listBox1->Items->Count; i++){
					 CloseHandle(aThread[i]);
				 }
				 end = clock();
				 cout << (end - start)/CLOCKS_PER_SEC << endl;
				 form2.ShowDialog();

	}
	
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 check->ShowDialog();
			 if (check->get_side() == 1)
				 label2->Text = "LED位置 : 右上方";
			 else if (check->get_side() == 2)
				 label2->Text = "LED位置 : 左上方";
			 if (check->get_color() == 1)
				 label3->Text = "LED顏色 : 紅色";
			 else if (check->get_color() == 2)
				 label3->Text = "LED顏色 : 黃色";
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 train();
			 label4->Text = "已訓練完畢!";
}
};
}
