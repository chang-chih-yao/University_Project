#pragma once
#include <msclr\marshal_cppstd.h>
#include <string>

using namespace std;
static int side = 1;
static int color = 1;
static string backg;

namespace Elevator_Scan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Allview 的摘要
	/// </summary>
	public ref class Allview : public System::Windows::Forms::Form
	{
	public:
		Allview(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
		int get_side(){
			return side;
		}
		int get_color(){
			return color;
		}
		string get_back(){
			string back = backg;
			backg = "";
			return back;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Allview()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label4;
	protected:

	protected:

	protected:

	protected:

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
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton1->Location = System::Drawing::Point(148, 33);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(84, 23);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"右上方";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton2->Location = System::Drawing::Point(8, 33);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(84, 23);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"左上方";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Location = System::Drawing::Point(34, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(294, 19);
			this->label1->TabIndex = 2;
			this->label1->Text = L"1.請選擇影片樓層數字的位置:\r\n";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(121, 404);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(105, 45);
			this->button1->TabIndex = 3;
			this->button1->Text = L"確定";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Allview::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label2->Location = System::Drawing::Point(34, 149);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(294, 19);
			this->label2->TabIndex = 4;
			this->label2->Text = L"2.請選擇影片樓層數字的顏色:\r\n";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton3->Location = System::Drawing::Point(8, 35);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(65, 23);
			this->radioButton3->TabIndex = 5;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"紅色";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->radioButton4->Location = System::Drawing::Point(148, 35);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(65, 23);
			this->radioButton4->TabIndex = 6;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"黃色";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton4);
			this->groupBox1->Location = System::Drawing::Point(52, 171);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(242, 85);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->radioButton2);
			this->groupBox2->Controls->Add(this->radioButton1);
			this->groupBox2->Location = System::Drawing::Point(52, 61);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(242, 85);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label3->Location = System::Drawing::Point(34, 273);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(211, 19);
			this->label3->TabIndex = 9;
			this->label3->Text = L"3.輸入背景(選擇性):\r\n";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 335);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(87, 22);
			this->button2->TabIndex = 10;
			this->button2->Text = L"背景添加";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Allview::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(121, 337);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(216, 22);
			this->textBox1->TabIndex = 11;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Allview::textBox1_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label4->Location = System::Drawing::Point(56, 303);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(162, 16);
			this->label4->TabIndex = 12;
			this->label4->Text = L"(僅適用於下個輸入)\r\n";
			// 
			// Allview
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(349, 488);
			this->ControlBox = false;
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"Allview";
			this->Text = L"輸入設定";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 int finish = 1;

				 if (radioButton1->Checked == true) side = 1;
				 else if (radioButton2->Checked == true) side = 2;
				 else finish = 0;

				 if (radioButton3->Checked == true) color = 1;
				 else if (radioButton4->Checked == true) color = 2;
				 else finish = 0;

				 std::string str = msclr::interop::marshal_as<std::string>(textBox1->Text->ToString());
				 char *strrr = new char[str.length() + 1];
				 strcpy(strrr, str.c_str());
				 backg = strrr;

				 if (finish == 0) MessageBox::Show("有資料未填寫!!");
				 else {
					 textBox1->Text = "";
					 this->Close();
				 }

	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				 textBox1->Text = openFileDialog1->FileName;
			 }
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
