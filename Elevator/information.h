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
static char result[100][1000];

namespace Elevator_Scan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// information 的摘要
	/// </summary>
	public ref class information : public System::Windows::Forms::Form
	{
	public:
		information(void)
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
		~information()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	public:
	protected:

	protected:


	private:

	private:


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
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(95, 78);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(391, 20);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &information::comboBox1_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(95, 160);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(399, 308);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"\r\n";
			this->textBox1->WordWrap = false;
			// 
			// information
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(596, 513);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"information";
			this->Text = L"information";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 int x = comboBox1->SelectedIndex;
				 System::String^ str = gcnew System::String(result[x]);
				 textBox1->Text = str;
	}
	};
}
