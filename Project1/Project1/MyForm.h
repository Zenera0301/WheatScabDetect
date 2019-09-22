#pragma once
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "ArrayTypes.h"
#include "Wrapper.h"
#include "windows.h"
#include "svm.h"
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <msclr\marshal_cppstd.h>  
#include<cstdio> 
using namespace msclr::interop;
using namespace System::IO;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

//界面
char ifIn = 0;//判断用户是否登录成功，成功该值设为1
//光谱仪
int intSampleAverage = 5;//平均次数是5
int intBoxcar = 1;//平滑度3，故宽度为1
int integrationTime = 350000;//积分时间350ms
int	numberOfPixels=512;	// number of CCD elements/pixels provided by the spectrometer
int numberOfSpectrometersAttached;// actually attached and talking to us
DoubleArray spectrumArray;// pixel values from the CCD elements
DoubleArray wavelengthArray;// wavelengths (in nanometers) corresponding to each CCD element
Wrapper wrapper;// this is the object through which we will access all of Omnidriver's capabilities
//模型
int feature_number;
int feature_number_spa = 8;//8个特征波段
int touying_spa[] = { 74, 138, 377, 9, 344, 242, 188, 294 };
int feature_number_mgs = 15;//15个特征波段
int touying_mgs[] = { 466, 471, 470, 465, 455, 469, 377, 433, 346, 405, 244, 248, 246, 468, 396 };
double r_spa[8];//8个特征波段
double r_mgs[15];//15个特征波段
int bandNumber = 500;//从原始数据中选取了3-502共500个波段
svm_parameter param;
svm_problem prob;
svm_model *svmModel;
vector<double> predictvalue;//预测值，即预测出的f(x)
vector<double> realvalue;//真实值，即参考值Y
ofstream outfile;
double wavelengths[512];
double white[512];
double black[512];
double specdata[512];
double r[512];
double copyrr[512];
double copyr[512];
char judgeStateWhite, judgeStateBlack, judgeAcquireIsOK, judgePredictIsOK;
int analyzeNumberOffline, analyzeNumberOnline;
double sum_x = 0.0;
double dr[500];//挑选3-502共500个波段，900nm-1700nm
double sum_drdr = 0.0;
double copyAccuracy;
int trainNum;
double sum_xsum_x[100];
double drdr[100][500];
double sum_drdrsum_drdr[100];

double Y1_predict = 0.0;//预测出的值
int Y1_predictlabel = 5;//根据值判断的等级
int accuracy = 5;
double b_spa[9], b_mgs[16], Y1_spa[9], Y1_mgs[16];

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::OleDb;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	/// <summary>
	/// MyForm 摘要
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}
		String^ jg(String^ filename)
		{
			FileStream^  fs = File::Open(filename, FileMode::Open, FileAccess::Read);
			StreamReader^ sr = gcnew StreamReader(fs);
			String^ str;
			for (int i = 0; i < 517; i++)
			{
				str = sr->ReadLine();
			}
			sr->Close();
			return  str;
		}
		String^ TxtTime(String^ filename)
		{
			FileStream^  fs = File::Open(filename, FileMode::Open, FileAccess::Read);
			StreamReader^ sr = gcnew StreamReader(fs);
			String^ str = sr->ReadLine();
			str = sr->ReadLine();
			sr->Close();
			return  str;
		}
		DataSet^ TxtToDataSet(String^ filename)
		{
			DataSet^ ds = gcnew DataSet();
			DataTable^ dt = gcnew  DataTable();
			FileStream^  fs = File::Open(filename, FileMode::Open, FileAccess::Read);
			StreamReader^ sr = gcnew StreamReader(fs);
			dt->Columns->Add("数据");
			String^ str = sr->ReadLine();
			str = sr->ReadLine();
			str = sr->ReadLine();
			for (int i = 0; i<511; i++)
			{
				DataRow^ dr = dt->NewRow();
				dr[0] = sr->ReadLine();;
				dt->Rows->Add(dr);
			}
			ds->Tables->Add(dt);
			sr->Close();
			return  ds;
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox7;





	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::TextBox^  textBox2;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox6;

	private: System::Windows::Forms::TextBox^  textBox5;

	private: System::Windows::Forms::TextBox^  textBox4;

	private: System::Windows::Forms::TextBox^  textBox3;

	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Label^  label8;



	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::Button^  button7;
private: System::Windows::Forms::TextBox^  textBox16;
private: System::Windows::Forms::TextBox^  textBox15;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::ComboBox^  comboBox1;
private: System::Windows::Forms::TextBox^  textBox17;
private: System::Windows::Forms::DataGridView^  dataGridView1;
private: System::Data::DataSet^  dataSet1;
private: System::Data::DataTable^  dataTable1;
private: System::Data::DataColumn^  dataColumn1;
private: System::Data::DataColumn^  dataColumn2;

private: System::Windows::Forms::DataGridView^  dataGridView2;
private: System::Data::DataColumn^  dataColumn3;
private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
private: System::Data::DataSet^  dataSet2;
private: System::Windows::Forms::Button^  button11;
private: System::Data::DataSet^  dataSet3;
private: System::Data::DataTable^  dataTable2;
private: System::Data::DataColumn^  dataColumn4;
private: System::Data::DataColumn^  dataColumn5;
private: System::Data::DataColumn^  dataColumn6;
private: System::Data::DataColumn^  dataColumn7;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::Button^  button10;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::TextBox^  textBox18;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::Button^  button12;







	private: System::ComponentModel::IContainer^  components;


	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->dataTable1 = (gcnew System::Data::DataTable());
			this->dataColumn1 = (gcnew System::Data::DataColumn());
			this->dataColumn2 = (gcnew System::Data::DataColumn());
			this->dataColumn3 = (gcnew System::Data::DataColumn());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->dataSet2 = (gcnew System::Data::DataSet());
			this->dataSet3 = (gcnew System::Data::DataSet());
			this->dataTable2 = (gcnew System::Data::DataTable());
			this->dataColumn4 = (gcnew System::Data::DataColumn());
			this->dataColumn5 = (gcnew System::Data::DataColumn());
			this->dataColumn6 = (gcnew System::Data::DataColumn());
			this->dataColumn7 = (gcnew System::Data::DataColumn());
			this->button12 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(198, 30);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(82, 26);
			this->button1->TabIndex = 0;
			this->button1->Text = L"浏    览";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(14, 30);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(178, 23);
			this->textBox7->TabIndex = 1;
			// 
			// chart1
			// 
			this->chart1->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Lines;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->Title = L"波段/nm";
			chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisX2->MajorGrid->Enabled = false;
			chartArea1->AxisX2->MajorGrid->LineColor = System::Drawing::Color::Transparent;
			chartArea1->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Lines;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY->Title = L"反射率/%";
			chartArea1->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisY2->MajorGrid->Enabled = false;
			chartArea1->AxisY2->MajorGrid->LineColor = System::Drawing::Color::Transparent;
			chartArea1->BackColor = System::Drawing::Color::White;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->DockedToChartArea = L"ChartArea1";
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(360, 103);
			this->chart1->Name = L"chart1";
			this->chart1->Size = System::Drawing::Size(326, 253);
			this->chart1->TabIndex = 5;
			this->chart1->Text = L"chart1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(198, 76);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(82, 26);
			this->button2->TabIndex = 6;
			this->button2->Text = L"预    测";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->ItemSize = System::Drawing::Size(180, 25);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->ShowToolTips = true;
			this->tabControl1->Size = System::Drawing::Size(734, 429);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 7;
			this->tabControl1->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &MyForm::tabControl1_Selected);
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->tabPage1->Controls->Add(this->button7);
			this->tabPage1->Controls->Add(this->textBox16);
			this->tabPage1->Controls->Add(this->textBox15);
			this->tabPage1->Controls->Add(this->label23);
			this->tabPage1->Controls->Add(this->label22);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 29);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tabPage1->Size = System::Drawing::Size(726, 396);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"登   录";
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(574, 357);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(74, 31);
			this->button7->TabIndex = 5;
			this->button7->Text = L"登 录";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(539, 319);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(109, 23);
			this->textBox16->TabIndex = 4;
			this->textBox16->UseSystemPasswordChar = true;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(539, 282);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(109, 23);
			this->textBox15->TabIndex = 3;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->BackColor = System::Drawing::SystemColors::Control;
			this->label23->Location = System::Drawing::Point(489, 325);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(32, 17);
			this->label23->TabIndex = 2;
			this->label23->Text = L"密码";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->BackColor = System::Drawing::SystemColors::Control;
			this->label22->Location = System::Drawing::Point(489, 285);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(44, 17);
			this->label22->TabIndex = 1;
			this->label22->Text = L"用户名";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(-57, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(796, 397);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->AutoScroll = true;
			this->tabPage2->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->tabPage2->Controls->Add(this->button12);
			this->tabPage2->Controls->Add(this->label19);
			this->tabPage2->Controls->Add(this->label18);
			this->tabPage2->Controls->Add(this->pictureBox2);
			this->tabPage2->Controls->Add(this->button6);
			this->tabPage2->Controls->Add(this->button5);
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->chart2);
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Controls->Add(this->groupBox1);
			this->tabPage2->Location = System::Drawing::Point(4, 29);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(726, 396);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"采  集";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(500, 21);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(0, 21);
			this->label19->TabIndex = 9;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(322, 64);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(80, 17);
			this->label18->TabIndex = 8;
			this->label18->Text = L"当前采集光谱";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(3, 3);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(251, 59);
			this->pictureBox2->TabIndex = 7;
			this->pictureBox2->TabStop = false;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(609, 339);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 30);
			this->button6->TabIndex = 6;
			this->button6->Text = L"保 存";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(512, 339);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(73, 30);
			this->button5->TabIndex = 5;
			this->button5->Text = L"采 集";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(416, 339);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(77, 30);
			this->button4->TabIndex = 4;
			this->button4->Text = L"白 帧";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(322, 338);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(73, 31);
			this->button3->TabIndex = 3;
			this->button3->Text = L"黑 帧";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// chart2
			// 
			chartArea2->AxisX->MajorGrid->Enabled = false;
			chartArea2->AxisX->Title = L"波段/nm";
			chartArea2->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea2->AxisY->MajorGrid->Enabled = false;
			chartArea2->AxisY->Title = L"反射率";
			chartArea2->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->DockedToChartArea = L"ChartArea1";
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(320, 88);
			this->chart2->Name = L"chart2";
			this->chart2->Size = System::Drawing::Size(362, 197);
			this->chart2->TabIndex = 2;
			this->chart2->Text = L"chart2";
			title1->DockedToChartArea = L"ChartArea1";
			title1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title1->Name = L"Title1";
			title1->Text = L"当前采集光谱图";
			this->chart2->Titles->Add(title1);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox6);
			this->groupBox2->Controls->Add(this->textBox5);
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->groupBox2->Location = System::Drawing::Point(4, 204);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(250, 168);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"预设参数";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(127, 132);
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(100, 21);
			this->textBox6->TabIndex = 7;
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(127, 99);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(100, 21);
			this->textBox5->TabIndex = 6;
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(127, 66);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(100, 21);
			this->textBox4->TabIndex = 5;
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(127, 33);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(100, 21);
			this->textBox3->TabIndex = 4;
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label6->Location = System::Drawing::Point(17, 135);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 12);
			this->label6->TabIndex = 3;
			this->label6->Text = L"非线性校正：";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label5->Location = System::Drawing::Point(17, 102);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 12);
			this->label5->TabIndex = 2;
			this->label5->Text = L"平滑度：";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(17, 69);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 12);
			this->label4->TabIndex = 1;
			this->label4->Text = L"平均次数：";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(17, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 12);
			this->label3->TabIndex = 0;
			this->label3->Text = L"积分时间：";
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->groupBox1->Location = System::Drawing::Point(4, 80);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(250, 106);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"光谱仪";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(127, 67);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(100, 21);
			this->textBox2->TabIndex = 3;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(17, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 12);
			this->label2->TabIndex = 2;
			this->label2->Text = L"序列号：";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(17, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"连接状态：";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(127, 31);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 21);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tabPage3
			// 
			this->tabPage3->AutoScroll = true;
			this->tabPage3->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->tabPage3->Controls->Add(this->label24);
			this->tabPage3->Controls->Add(this->label7);
			this->tabPage3->Controls->Add(this->groupBox5);
			this->tabPage3->Controls->Add(this->dataGridView1);
			this->tabPage3->Controls->Add(this->label20);
			this->tabPage3->Controls->Add(this->pictureBox3);
			this->tabPage3->Controls->Add(this->chart1);
			this->tabPage3->Location = System::Drawing::Point(4, 29);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(726, 396);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"预   测";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(357, 83);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(92, 17);
			this->label24->TabIndex = 21;
			this->label24->Text = L"当前预测光谱图";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(29, 276);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(44, 17);
			this->label7->TabIndex = 20;
			this->label7->Text = L"信息表";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->textBox17);
			this->groupBox5->Controls->Add(this->comboBox1);
			this->groupBox5->Controls->Add(this->button8);
			this->groupBox5->Controls->Add(this->label8);
			this->groupBox5->Controls->Add(this->textBox7);
			this->groupBox5->Controls->Add(this->button1);
			this->groupBox5->Controls->Add(this->button2);
			this->groupBox5->Location = System::Drawing::Point(32, 83);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(291, 186);
			this->groupBox5->TabIndex = 19;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"预测";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(73, 132);
			this->textBox17->Name = L"textBox17";
			this->textBox17->ReadOnly = true;
			this->textBox17->Size = System::Drawing::Size(119, 23);
			this->textBox17->TabIndex = 17;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"SPA-SVM", L"MGS-SVM" });
			this->comboBox1->Location = System::Drawing::Point(14, 76);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(178, 25);
			this->comboBox1->TabIndex = 16;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(198, 130);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(82, 26);
			this->button8->TabIndex = 11;
			this->button8->Text = L"保     存";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(11, 135);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(56, 17);
			this->label8->TabIndex = 10;
			this->label8->Text = L"预测结果";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(32, 296);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowTemplate->Height = 23;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(291, 60);
			this->dataGridView1->TabIndex = 18;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(500, 21);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(0, 21);
			this->label20->TabIndex = 13;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(3, 3);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(251, 59);
			this->pictureBox3->TabIndex = 12;
			this->pictureBox3->TabStop = false;
			// 
			// tabPage4
			// 
			this->tabPage4->AutoScroll = true;
			this->tabPage4->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->tabPage4->Controls->Add(this->label25);
			this->tabPage4->Controls->Add(this->button10);
			this->tabPage4->Controls->Add(this->button11);
			this->tabPage4->Controls->Add(this->dataGridView2);
			this->tabPage4->Controls->Add(this->label21);
			this->tabPage4->Controls->Add(this->pictureBox4);
			this->tabPage4->Controls->Add(this->label17);
			this->tabPage4->Controls->Add(this->dateTimePicker2);
			this->tabPage4->Controls->Add(this->dateTimePicker1);
			this->tabPage4->Controls->Add(this->label16);
			this->tabPage4->Controls->Add(this->groupBox4);
			this->tabPage4->Controls->Add(this->groupBox3);
			this->tabPage4->Controls->Add(this->label15);
			this->tabPage4->Controls->Add(this->textBox8);
			this->tabPage4->Controls->Add(this->button9);
			this->tabPage4->Location = System::Drawing::Point(4, 29);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(726, 396);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"查   询";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(327, 73);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(44, 17);
			this->label25->TabIndex = 28;
			this->label25->Text = L"信息表";
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::White;
			this->button10->Location = System::Drawing::Point(330, 93);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(40, 24);
			this->button10->TabIndex = 27;
			this->button10->Text = L"清空";
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click_1);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(606, 287);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(92, 27);
			this->button11->TabIndex = 26;
			this->button11->Text = L"选择文件夹";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click_1);
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView2->BackgroundColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->dataGridView2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Location = System::Drawing::Point(330, 93);
			this->dataGridView2->MultiSelect = false;
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->ReadOnly = true;
			this->dataGridView2->RowTemplate->Height = 23;
			this->dataGridView2->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView2->Size = System::Drawing::Size(368, 146);
			this->dataGridView2->TabIndex = 24;
			this->dataGridView2->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView2_CellClick);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(500, 21);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(0, 21);
			this->label21->TabIndex = 23;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(3, 3);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(251, 59);
			this->pictureBox4->TabIndex = 22;
			this->pictureBox4->TabStop = false;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label17->Location = System::Drawing::Point(455, 294);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(17, 12);
			this->label17->TabIndex = 21;
			this->label17->Text = L"至";
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Location = System::Drawing::Point(477, 287);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->Size = System::Drawing::Size(123, 23);
			this->dateTimePicker2->TabIndex = 20;
			this->dateTimePicker2->Value = System::DateTime(2018, 3, 18, 0, 0, 0, 0);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(330, 287);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(119, 23);
			this->dateTimePicker1->TabIndex = 19;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label16->Location = System::Drawing::Point(328, 272);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(101, 12);
			this->label16->TabIndex = 18;
			this->label16->Text = L"按采集时间查询：";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox18);
			this->groupBox4->Controls->Add(this->label27);
			this->groupBox4->Controls->Add(this->textBox14);
			this->groupBox4->Controls->Add(this->label14);
			this->groupBox4->Controls->Add(this->textBox9);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->groupBox4->Location = System::Drawing::Point(8, 270);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(298, 109);
			this->groupBox4->TabIndex = 17;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"记录";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(86, 49);
			this->textBox18->Name = L"textBox18";
			this->textBox18->ReadOnly = true;
			this->textBox18->Size = System::Drawing::Size(196, 21);
			this->textBox18->TabIndex = 17;
			this->textBox18->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label27->Location = System::Drawing::Point(16, 52);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(65, 12);
			this->label27->TabIndex = 16;
			this->label27->Text = L"所用算法：";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(86, 77);
			this->textBox14->Name = L"textBox14";
			this->textBox14->ReadOnly = true;
			this->textBox14->Size = System::Drawing::Size(196, 21);
			this->textBox14->TabIndex = 15;
			this->textBox14->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label14->Location = System::Drawing::Point(16, 80);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(65, 12);
			this->label14->TabIndex = 6;
			this->label14->Text = L"预测结果：";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(86, 19);
			this->textBox9->Name = L"textBox9";
			this->textBox9->ReadOnly = true;
			this->textBox9->Size = System::Drawing::Size(196, 21);
			this->textBox9->TabIndex = 10;
			this->textBox9->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label9->Location = System::Drawing::Point(16, 24);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(65, 12);
			this->label9->TabIndex = 1;
			this->label9->Text = L"采样时间：";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label26);
			this->groupBox3->Controls->Add(this->textBox13);
			this->groupBox3->Controls->Add(this->textBox12);
			this->groupBox3->Controls->Add(this->textBox11);
			this->groupBox3->Controls->Add(this->textBox10);
			this->groupBox3->Controls->Add(this->label13);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->label11);
			this->groupBox3->Controls->Add(this->label10);
			this->groupBox3->Controls->Add(this->chart3);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->groupBox3->Location = System::Drawing::Point(9, 85);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(297, 154);
			this->groupBox3->TabIndex = 16;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"参数及光谱曲线";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->label26->Location = System::Drawing::Point(157, 12);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(89, 12);
			this->label26->TabIndex = 15;
			this->label26->Text = L"当前查询光谱图";
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(86, 119);
			this->textBox13->Name = L"textBox13";
			this->textBox13->ReadOnly = true;
			this->textBox13->Size = System::Drawing::Size(62, 21);
			this->textBox13->TabIndex = 14;
			this->textBox13->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(86, 88);
			this->textBox12->Name = L"textBox12";
			this->textBox12->ReadOnly = true;
			this->textBox12->Size = System::Drawing::Size(62, 21);
			this->textBox12->TabIndex = 13;
			this->textBox12->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(86, 59);
			this->textBox11->Name = L"textBox11";
			this->textBox11->ReadOnly = true;
			this->textBox11->Size = System::Drawing::Size(62, 21);
			this->textBox11->TabIndex = 12;
			this->textBox11->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(86, 31);
			this->textBox10->Name = L"textBox10";
			this->textBox10->ReadOnly = true;
			this->textBox10->Size = System::Drawing::Size(62, 21);
			this->textBox10->TabIndex = 11;
			this->textBox10->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label13->Location = System::Drawing::Point(3, 122);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(77, 12);
			this->label13->TabIndex = 5;
			this->label13->Text = L"非线性校正：";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label12->Location = System::Drawing::Point(27, 91);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(53, 12);
			this->label12->TabIndex = 4;
			this->label12->Text = L"平滑度：";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label11->Location = System::Drawing::Point(15, 62);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(65, 12);
			this->label11->TabIndex = 3;
			this->label11->Text = L"平均次数：";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label10->Location = System::Drawing::Point(15, 34);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(65, 12);
			this->label10->TabIndex = 2;
			this->label10->Text = L"积分时间：";
			// 
			// chart3
			// 
			this->chart3->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea3->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Lines;
			chartArea3->AxisX->MajorGrid->Enabled = false;
			chartArea3->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Lines;
			chartArea3->AxisY->MajorGrid->Enabled = false;
			chartArea3->BackColor = System::Drawing::Color::White;
			chartArea3->Name = L"ChartArea1";
			this->chart3->ChartAreas->Add(chartArea3);
			this->chart3->Location = System::Drawing::Point(159, 31);
			this->chart3->Name = L"chart3";
			this->chart3->Size = System::Drawing::Size(122, 112);
			this->chart3->TabIndex = 0;
			this->chart3->Text = L"chart3";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->label15->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label15->Location = System::Drawing::Point(328, 324);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(101, 12);
			this->label15->TabIndex = 9;
			this->label15->Text = L"按样本名称查询：";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(330, 344);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(270, 23);
			this->textBox8->TabIndex = 8;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(606, 342);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(92, 27);
			this->button9->TabIndex = 7;
			this->button9->Text = L"查  询";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"NewDataSet";
			this->dataSet1->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) { this->dataTable1 });
			// 
			// dataTable1
			// 
			this->dataTable1->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(3) {
				this->dataColumn1, this->dataColumn2,
					this->dataColumn3
			});
			this->dataTable1->TableName = L"Table1";
			// 
			// dataColumn1
			// 
			this->dataColumn1->ColumnName = L"文件名称";
			// 
			// dataColumn2
			// 
			this->dataColumn2->ColumnName = L"采集时间";
			// 
			// dataColumn3
			// 
			this->dataColumn3->ColumnName = L"文件路径";
			// 
			// dataSet2
			// 
			this->dataSet2->DataSetName = L"NewDataSet";
			// 
			// dataSet3
			// 
			this->dataSet3->DataSetName = L"NewDataSet";
			this->dataSet3->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) { this->dataTable2 });
			// 
			// dataTable2
			// 
			this->dataTable2->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(4) {
				this->dataColumn4, this->dataColumn5,
					this->dataColumn6, this->dataColumn7
			});
			this->dataTable2->TableName = L"Table1";
			// 
			// dataColumn4
			// 
			this->dataColumn4->ColumnName = L"文件名称";
			// 
			// dataColumn5
			// 
			this->dataColumn5->ColumnName = L"采集时间";
			// 
			// dataColumn6
			// 
			this->dataColumn6->ColumnName = L"文件路径";
			// 
			// dataColumn7
			// 
			this->dataColumn7->ColumnName = L"预测结果";
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(512, 300);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(73, 33);
			this->button12->TabIndex = 10;
			this->button12->Text = L"快速检测";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(734, 429);
			this->Controls->Add(this->tabControl1);
			this->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"小麦感染赤霉病等级检测系统";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Start();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //动态显示系统当前时间
			 string   time = getTime();
			 const char * p = time.data();
			 String ^ MyStr = Marshal::PtrToStringAnsi((IntPtr)(char *)p);
			 label19->Text = MyStr;
			 label20->Text = MyStr;
			 label21->Text = MyStr;
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 //登录界面
			 String^isUserName = "ssl";//设置用户名
			 String^isPassWord = "123";//设置密码
			 String^ userName = textBox15->Text;
			 if (userName == isUserName)
			 {
				 String^ passWord = textBox16->Text;
				 if (passWord == isPassWord)
				 {
					 ifIn = 1;
					 textBox16->Text = "";//清空密码
					 tabControl1->SelectedIndex = 1;//自动跳到第二个选板“采集”上
				 }
				 else if (passWord == "")
				 {
					 ::MessageBox(NULL, TEXT("您未输入密码，请输入密码！"), TEXT("提示"), MB_OK);
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("您输入的密码有误，请重新输入！"), TEXT("提示"), MB_OK);
				 }
			 }
			 else if (userName == "")
			 {
				 ::MessageBox(NULL, TEXT("您未输入用户名，请输入用户名！"), TEXT("提示"), MB_OK);
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您输入的用户名有误，请重新输入！"), TEXT("提示"), MB_OK);
			 }
}
public: System::Void tabControl1_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e) {
				//选中面板时，判断光谱仪连接状态
				numberOfSpectrometersAttached = wrapper.openAllSpectrometers();	// Gets an array of spectrometer objects
				if (numberOfSpectrometersAttached <= 0)
				{
					textBox1->Text = "未连接";
					textBox2->Text = "NULL";
					textBox3->Text = "NULL";
					textBox4->Text = "NULL";
					textBox5->Text = "NULL";
					textBox6->Text = "NULL";
				}
				if (numberOfSpectrometersAttached == 1){
					textBox1->Text = "已连接";
					textBox2->Text = string_to_textbox(wrapper.getSerialNumber(0).getASCII()); //采集显示序列号
					wrapper.setIntegrationTime(0, integrationTime);		// Sets the integration time of the first spectrometer to 350ms
					textBox3->Text = "350ms";
					textBox4->Text = "5";
					textBox5->Text = "3";
					textBox6->Text = "进行";
				}
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (ifIn == 1)
			 {
				//采集黑帧
				 if (numberOfSpectrometersAttached >0){
					 getSpectrumInit();
					 spectrumArray = wrapper.getSpectrum(0);
					 if (!(wrapper.getWrapperExtensions().isSpectrumValid(0)) == false)
					 {
						 wavelengthArray = wrapper.getWavelengths(0);			    
						 numberOfPixels = spectrumArray.getLength();				
						 double *wavelengths = wavelengthArray.getDoubleValues();	
						 double *spectrum = spectrumArray.getDoubleValues();	
						 for (int i = 0; i < numberOfPixels; i++){
							 black[i] = spectrum[i];
						 }
						 judgeStateBlack = 1;
						 ::MessageBox(NULL, TEXT("黑帧采集成功！"), TEXT("提示"), MB_OK);
					 }
					 else{
						 judgeStateBlack = 0;
						 ::MessageBox(NULL, TEXT("黑帧采集失败，请重新采集黑帧！"), TEXT("提示"), MB_OK);
					 }
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("请先连接光谱仪！"), TEXT("未连接光谱仪"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
			 
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (ifIn == 1)
			 {
				 //采集白帧
				 if (numberOfSpectrometersAttached >0){
					 getSpectrumInit();
					 spectrumArray = wrapper.getSpectrum(0);
					 spectrumArray = wrapper.getSpectrum(0);//采集两次
					 if (!(wrapper.getWrapperExtensions().isSpectrumValid(0)) == false)
					 {
						 wavelengthArray = wrapper.getWavelengths(0);			   
						 numberOfPixels = spectrumArray.getLength();				
						 double *wavelengths = wavelengthArray.getDoubleValues();
						 double *spectrum = spectrumArray.getDoubleValues();	
						 for (int i = 0; i < numberOfPixels; i++){
							 white[i] = spectrum[i];
						 }
						 judgeStateWhite = 1;
						 ::MessageBox(NULL, TEXT("白帧采集成功！"), TEXT("提示"), MB_OK);
					 }
					 else{
						 judgeStateWhite = 0;
						 ::MessageBox(NULL, TEXT("白帧采集失败，请重新采集白帧！"), TEXT("提示"), MB_OK);
					 }
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("请先连接光谱仪！"), TEXT("未连接光谱仪"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 //采集样本光谱   
			 if (ifIn == 1)
			 {
				 if (numberOfSpectrometersAttached>0)//判断是否已连接光谱仪
				 {
					 if (judgeStateWhite == 1 && judgeStateBlack == 1)//判断是否已经采集黑白帧
					 {
						 getSpectrumInit();
						 spectrumArray = wrapper.getSpectrum(0);
						 if (!(wrapper.getWrapperExtensions().isSpectrumValid(0)) == false)
						 {
							 wavelengthArray = wrapper.getWavelengths(0);			    
							 numberOfPixels = spectrumArray.getLength();				
							 double *wavelengths = wavelengthArray.getDoubleValues();	
							 double *spectrum = spectrumArray.getDoubleValues();			 
							 for (int i = 0; i < numberOfPixels; i++){
								 r[i] = spectrum[i];
							 }
							 ::MessageBox(NULL, TEXT("样本光谱采集成功！"), TEXT("提示"), MB_OK);
							 
							 outfile.open("afterBlackWhiteREF.txt");
							 for (int i = 0; i < numberOfPixels; i++){
								 r[i] = 100.0 * (r[i] - black[i]) / (white[i] - black[i]);
								 outfile << r[i] << endl;
								 copyr[i] = r[i];
							 }
							 outfile.close();

							 chart2->Series->Clear();
							 DataTable^ DT = gcnew  DataTable();
							 DT->Columns->Add("数据");
							 for (int i = 0; i < 512; i++)
							 {
								 DataRow^ dr = DT->NewRow();
								 dr[0] = r[i];
								 DT->Rows->Add(dr);
							 }
							 this->chart2->DataSource = DT;
							 Series^ dataSeries = gcnew Series("反射率");
							 dataSeries->YValueMembers = DT->Columns[0]->ColumnName;
							 dataSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
							 chart2->Series->Add(dataSeries);

							 judgeAcquireIsOK = 1;
							 }
							 else{
								 ::MessageBox(NULL, TEXT("样本光谱采集失败！"), TEXT("提示"), MB_OK);
							 }
					 }
					 else
					 {
						 ::MessageBox(NULL, TEXT("请先采集黑白帧！"), TEXT("未采集黑白帧"), MB_OK);
					 }
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("请先连接光谱仪！"), TEXT("未连接光谱仪"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (ifIn == 1)
			 {
				//采集界面的保存
				 if (judgeAcquireIsOK == 1)//判断是否已采集完成
				 {
					 this->saveFileDialog1->Filter = "txt文件(*.txt)|*.txt;";
					 this->saveFileDialog1->RestoreDirectory = true;
					 if (this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 {
						String^ savefilelocation = saveFileDialog1->FileName;						
						std::string savefilelocation_string = marshal_as<std::string>(savefilelocation->ToString());
						outfile.open(savefilelocation_string);
						outfile << "采集时间："<< endl;
						string  time = getTime();
						outfile << time << endl;
						outfile << "采集数据：" << endl;
						 for (int i = 0; i < numberOfPixels; i++){
							 outfile << copyr[i] << endl;
						 }
						 outfile.close();
						 for (int i = 0; i < numberOfPixels; i++){
							 copyr[i] = 0;
						 }
					 }
					 judgeAcquireIsOK = 0;
					 ::MessageBox(NULL, TEXT("保存成功！"), TEXT("提示"), MB_OK);
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("请先进行采集！"), TEXT("未采集"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
}
private: System::Void button1_Click(System::Object^sender, System::EventArgs^e)
	{
			 if (ifIn == 1)
			 {
				 //浏览
				 this->openFileDialog1->Filter = "txt文件(*.txt)|*.txt;";
				 this->openFileDialog1->RestoreDirectory = true;
				 if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 dataSet1->Tables[0]->Clear();
					 this->textBox7->Text = this->openFileDialog1->FileName;
					 String^ FN = System::IO::Path::GetFileNameWithoutExtension(this->openFileDialog1->FileName);
					 DataRow^ nrow = dataSet1->Tables[0]->NewRow();
					 nrow["文件名称"] = FN;
					 nrow["采集时间"] = TxtTime(this->openFileDialog1->FileName);
					 nrow["文件路径"] = this->openFileDialog1->FileName;
					 dataSet1->Tables[0]->Rows->Add(nrow);
					 this->dataGridView1->DataSource = dataSet1->Tables[0];
					 this->dataGridView1->Columns["文件路径"]->Visible = false; 
					 
				 //图表作图
				 if (dataGridView1->SelectedRows[0] != nullptr)
				 {
					 chart1->Series->Clear();
					 String^ filename = dataGridView1->SelectedRows[0]->Cells[2]->Value->ToString();
					 dataSet2 = TxtToDataSet(filename);
					 DataTable^ dt = dataSet2->Tables[0];
					 this->chart1->DataSource = dt;
					 Series^ dataSeries = gcnew Series("反射率");
					 dataSeries->YValueMembers = dt->Columns[0]->ColumnName;
					 dataSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
					 chart1->Series->Add(dataSeries);
				 }
				 }
						
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 } 
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{		//预测		 
			if (ifIn == 1)
			{
				ofstream outfile;
				outfile.open("aftergetOneSample.txt");
				for (int i = 0; i < 512; i++){
					r[i] = TxtToArray(textBox7->Text, i + 4);
					outfile << r[i] << endl;
				}
				outfile.close();
				CutBandprogram();
				//根据用户选择调用不同的模型进行预测
				if (comboBox1->Text == "SPA-SVM")
				{
					feature_number=feature_number_spa;
					SPAprogram();//进行SPA波段提取并存入afterSelectprogram.txt
					getB("b_spa.txt");
					getY1("afterSelectprogram.txt");
					Y1withB();
					accuracy = Y1_predictlabel;
					//预测结果的输出
					if (accuracy == 0)
					{
						textBox17->Text = "低";
					}
					else if (accuracy == 1)
					{
						textBox17->Text = "高";
					}
					else
					{
						textBox17->Text = double_to_textbox(accuracy);
					}
					for (int i = 0; i < numberOfPixels; i++){
						r[i] = 0;
					}
					judgePredictIsOK = 1;
					::MessageBox(NULL, TEXT("预测成功！"), TEXT("提示"), MB_OK);
				}
				else if (comboBox1->Text == "MGS-SVM")
				{
					feature_number = feature_number_mgs;
					MGSprogram();//进行MGS波段提取并存入afterSelectprogram.txt
					getB("b_mgs.txt");
					getY1("afterSelectprogram.txt");
					Y1withB();
					accuracy = Y1_predictlabel;
					//预测结果的输出
					if (accuracy == 0)
					{
						textBox17->Text = "低";
					}
					else if (accuracy == 1)
					{
						textBox17->Text = "高";
					}
					else
					{
						textBox17->Text = double_to_textbox(accuracy);
					}
					for (int i = 0; i < numberOfPixels; i++){
						r[i] = 0;
					}
					judgePredictIsOK = 1;
					::MessageBox(NULL, TEXT("预测成功！"), TEXT("提示"), MB_OK);
				}
				else
				{
					::MessageBox(NULL, TEXT("请选择数据处理方式！"), TEXT("提示"), MB_OK);
				}				
			}
			else
			{
				::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			}	 
	}


private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {

			 //实现采集与控制一体化
			 //采集样本光谱   
			 if (ifIn == 1)
			 {
				 if (numberOfSpectrometersAttached>0)//判断是否已连接光谱仪
				 {
					 if (judgeStateWhite == 1 && judgeStateBlack == 1)//判断是否已经采集黑白帧
					 {
						 getSpectrumInit();
						 spectrumArray = wrapper.getSpectrum(0);
						 if (!(wrapper.getWrapperExtensions().isSpectrumValid(0)) == false)
						 {
							 wavelengthArray = wrapper.getWavelengths(0);
							 numberOfPixels = spectrumArray.getLength();
							 double *wavelengths = wavelengthArray.getDoubleValues();
							 double *spectrum = spectrumArray.getDoubleValues();
							 for (int i = 0; i < numberOfPixels; i++){
								 r[i] = spectrum[i];
							 }
							 // ::MessageBox(NULL, TEXT("样本光谱采集成功！"), TEXT("提示"), MB_OK);

							 outfile.open("afterBlackWhiteREF.txt");
							 for (int i = 0; i < numberOfPixels; i++){
								 r[i] = 100.0 * (r[i] - black[i]) / (white[i] - black[i]);
								 outfile << r[i] << endl;
								 copyr[i] = r[i];
							 }
							 outfile.close();

							 chart2->Series->Clear();
							 DataTable^ DT = gcnew  DataTable();
							 DT->Columns->Add("数据");
							 for (int i = 0; i < 512; i++)
							 {
								 DataRow^ dr = DT->NewRow();
								 dr[0] = r[i];
								 DT->Rows->Add(dr);
							 }
							 this->chart2->DataSource = DT;
							 Series^ dataSeries = gcnew Series("反射率");
							 dataSeries->YValueMembers = DT->Columns[0]->ColumnName;
							 dataSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
							 chart2->Series->Add(dataSeries);

							 judgeAcquireIsOK = 1;

							 //采集成功后进行预测
							 //预测		 

							/* ofstream outfile;
							 outfile.open("aftergetOneSample.txt");
							 for (int i = 0; i < 512; i++){
								 r[i] = TxtToArray(textBox7->Text, i + 4);
								 outfile << r[i] << endl;
							 }
							 outfile.close();*/

							 CutBandprogram();

							 //根据内置参数，选择SPA-SVM的方法进行检测
							 feature_number = feature_number_spa;
							 SPAprogram();//进行SPA波段提取并存入afterSelectprogram.txt
							 getB("b_spa.txt");
							 getY1("afterSelectprogram.txt");
							 Y1withB();
							 accuracy = Y1_predictlabel;
							 //预测结果的输出
							 if (accuracy == 0)
							 {
								 ::MessageBox(NULL, TEXT("当前检测结果为：低毒！"), TEXT("提示"), MB_OK);
							 }
							 else if (accuracy == 1)
							 {
								 ::MessageBox(NULL, TEXT("当前检测结果为：高毒！"), TEXT("提示"), MB_OK);
							 }

							 for (int i = 0; i < numberOfPixels; i++){
								 r[i] = 0;
							 }
							 judgePredictIsOK = 1;


						 }
						 else{
							 ::MessageBox(NULL, TEXT("样本光谱采集失败！"), TEXT("提示"), MB_OK);
						 }
					 }
					 else
					 {
						 ::MessageBox(NULL, TEXT("请先采集黑白帧！"), TEXT("未采集黑白帧"), MB_OK);
					 }
				 }
				 else
				 {
					 ::MessageBox(NULL, TEXT("请先连接光谱仪！"), TEXT("未连接光谱仪"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }

}




private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			 //保存预测结果
			 if (ifIn == 1)
			 {   
				 if (judgePredictIsOK == 1)//判断是否已预测完成
				 {
					 this->saveFileDialog1->Filter = "txt文件(*.txt)|*.txt;";
					 this->saveFileDialog1->RestoreDirectory = true;
					 if (this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 {
						 String^ savefilelocation = saveFileDialog1->FileName;
						 std::string savefilelocation_string = marshal_as<std::string>(savefilelocation->ToString());
						 FileStream^  fs = File::Open(textBox7->Text, FileMode::Open, FileAccess::Read);
						 StreamReader^ sr = gcnew StreamReader(fs);
						 String^ str;
						 str = sr->ReadLine();
						 str = sr->ReadLine();
						 std::string str_string = marshal_as<std::string>(str->ToString());
						 sr->Close();
						 outfile.open(savefilelocation_string);
						 outfile << "采集时间：" << endl;						
						 outfile << str_string << endl;
						 outfile << "采集数据：" << endl;
						 for (int i = 0; i <512; i++)
						 {
							 outfile << TxtToArray(textBox7->Text, i + 4) << endl;
						 }
						 outfile << "预测结果：" << endl;
						 std::string predictResult = marshal_as<std::string>(textBox17->Text->ToString());
						 if (predictResult == "低")
						 {
							 outfile << 0 << endl;
						 }
						 else if (predictResult == "高")
						 {
							 outfile << 1 << endl;
						 }
						 else
						 {
							 outfile << "NULL" << endl;
						 }
						 outfile << "使用算法：" << endl;
						 std::string 使用算法 = marshal_as<std::string>(comboBox1->Text->ToString());
						 outfile << 使用算法 << endl;
						 outfile.close();
					 }
					 judgePredictIsOK = 0;
					 ::MessageBox(NULL, TEXT("保存成功！"), TEXT("提示"), MB_OK);
				 }
				 else{
					 ::MessageBox(NULL, TEXT("请先进行预测！"), TEXT("未预测"), MB_OK);
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
}
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			 // 按样本名称查询
			 if (ifIn == 1)
			 {
				 this->openFileDialog1->Filter = "txt文件(*.txt)|*.txt;";
				 this->openFileDialog1->RestoreDirectory = true;
				 if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->textBox8->Text = this->openFileDialog1->FileName;
					 String^ FN = System::IO::Path::GetFileNameWithoutExtension(this->openFileDialog1->FileName);
					 DataRow^ nrow = dataSet3->Tables[0]->NewRow();
					 nrow["文件名称"] = FN;
					 nrow["采集时间"] = TxtTime(this->openFileDialog1->FileName);
					 nrow["文件路径"] = this->openFileDialog1->FileName;
					 nrow["预测结果"] = jg(this->openFileDialog1->FileName);
					 dataSet3->Tables[0]->Rows->Add(nrow);
					 this->dataGridView2->DataSource = dataSet3->Tables[0];
					 this->dataGridView2->Columns["文件路径"]->Visible = false;
					 //图表作图
					 if (dataGridView2->SelectedRows[0] != nullptr)
					 {
						 chart3->Series->Clear();
						 String^ filename = dataGridView2->SelectedRows[0]->Cells[2]->Value->ToString();
						 dataSet2 = TxtToDataSet(filename);
						 DataTable^ dt = dataSet2->Tables[0];
						 this->chart3->DataSource = dt;
						 Series^ dataSeries = gcnew Series("反射率");
						 dataSeries->YValueMembers = dt->Columns[0]->ColumnName;
						 dataSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
						 chart3->Series->Add(dataSeries);
					 }
					 textBox10->Text = "350ms";
					 textBox11->Text = "5";
					 textBox12->Text = "3";
					 textBox13->Text = "进行";
					 //输出采样时间
					 FileStream^  fs = File::Open(textBox8->Text, FileMode::Open, FileAccess::Read);
					 StreamReader^ sr = gcnew StreamReader(fs);
					 String^ str;
					 str = sr->ReadLine();
					 str = sr->ReadLine();
					 textBox9->Text = str;
					 for (int i = 0; i < 517; i++)
					 {
						 str = sr->ReadLine();
					 }
					 textBox18->Text = str;
					 sr->Close();
					 //输出采集结果
					 double x = TxtToArray(textBox8->Text, 517);
					 if (x == 0)
					 {
						 textBox14->Text = "低";
					 }
					 else if (x == 1)
					 {
						 textBox14->Text = "高";
					 }
					 else
					 {
						 textBox14->Text = "NULL";
					 }
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }
		 }

private: System::Void button11_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 if (ifIn == 1)
			 {
				 FolderBrowserDialog^ dialog = gcnew FolderBrowserDialog();
				 dialog->Description = "请选择预测结果所在文件夹";
				 if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 if (String::IsNullOrEmpty(dialog->SelectedPath))
					 {
						 MessageBox::Show("文件夹路径不能为空");
						 return;
					 }
					 else
					 {
						 dataSet3->Tables[0]->Clear();
						 array<String^>^ files = Directory::GetFiles(dialog->SelectedPath, "*.txt", SearchOption::AllDirectories);
						 for (int i = 0; i < files->Length; i++)
						 {
							 DateTime DT = DateTime::ParseExact(TxtTime(files[i]), "yyyy-MM-dd HH:mm:ss", nullptr);
							 DateTime DTmin = dateTimePicker1->Value;
							 DateTime DTmax = dateTimePicker2->Value;
							 if ((DateTime::Compare(DT, DTmin)>0) && (DateTime::Compare(DT, DTmax) < 0))
							 {
								 String^ FN = System::IO::Path::GetFileNameWithoutExtension(files[i]);
								 DataRow^ nrow = dataSet3->Tables[0]->NewRow();
								 nrow["文件名称"] = FN;
								 nrow["采集时间"] = TxtTime(files[i]);
								 nrow["文件路径"] = files[i];
								 nrow["预测结果"] = jg(files[i]);
								 dataSet3->Tables[0]->Rows->Add(nrow);
								 this->dataGridView2->DataSource = dataSet3->Tables[0];
								 this->dataGridView2->Columns["文件路径"]->Visible = false;
							 }
						 }
					 }
				 }
			 }
			 else
			 {
				 ::MessageBox(NULL, TEXT("您还未登录，请登录后使用！"), TEXT("提示"), MB_OK);
			 }			 
}
private: System::Void dataGridView2_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			//单击某行弹出该行样本信息
			 if (dataGridView2->SelectedRows[0] != nullptr)
			 {
				 chart3->Series->Clear();
				 String^ filename = dataGridView2->SelectedRows[0]->Cells[2]->Value->ToString();
				 dataSet2 = TxtToDataSet(filename);
				 DataTable^ dt = dataSet2->Tables[0];
				 this->chart3->DataSource = dt;
				 Series^ dataSeries = gcnew Series("反射率");
				 dataSeries->YValueMembers = dt->Columns[0]->ColumnName;
				 dataSeries->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
				 chart3->Series->Add(dataSeries);
				 textBox10->Text = "350ms";
				 textBox11->Text = "5";
				 textBox12->Text = "3";
				 textBox13->Text = "进行";
				 //输出采样时间
				 FileStream^  fs = File::Open(filename, FileMode::Open, FileAccess::Read);
				 StreamReader^ sr = gcnew StreamReader(fs);
				 String^ str;
				 str = sr->ReadLine();
				 str = sr->ReadLine();
				 textBox9->Text = str;
				 for (int i = 0; i < 517; i++)
				 {
					 str = sr->ReadLine();
				 }
				 textBox18->Text = str;
				 sr->Close();
				 //输出采集结果
				 double x = TxtToArray(filename, 517);
				 if (x == 0)
				 {
					 textBox14->Text = "低";
				 }
				 else if (x == 1)
				 {
					 textBox14->Text = "高";
				 }
				 else
				 {
					 textBox14->Text = "NULL";
				 } 
			 }
}
private: System::Void button10_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 //清空
			 dataSet2->Clear();
			 dataSet3->Clear();
			 chart3->Series->Clear();
			 textBox9->Text = "";
			 textBox10->Text = "";
			 textBox11->Text = ""; 
			 textBox12->Text = "";
			 textBox13->Text = "";
			 textBox14->Text = "";
			 textBox18->Text = "";
			 textBox8->Text = "";
}

public: String ^int_to_textbox(int num)
{
			string s = "";
			s += to_string(num);
			const char * p = s.data();
			String ^ MyStr = Marshal::PtrToStringAnsi((IntPtr)(char *)p);
			return MyStr;
}
public: String ^double_to_textbox(double num)
{
			num = num*100.0;
			string s = "";
			s += to_string(num);
			s += "%";
			const char * p = s.data();
			String ^ MyStr = Marshal::PtrToStringAnsi((IntPtr)(char *)p);
			return MyStr;
}
public: String ^string_to_textbox(string s)
{
			const char * p = s.data();
			String ^ MyStr = Marshal::PtrToStringAnsi((IntPtr)(char *)p);
			return MyStr;
}
Double TxtToArray(String^ filename, int n)//Double^
{
	FileStream^  fs = File::Open(filename, FileMode::Open, FileAccess::Read);
	StreamReader^ sr = gcnew StreamReader(fs);
	String^ str;
	for (int i = 1; i<n; i++)
	{
		str = sr->ReadLine();
	}
	str = sr->ReadLine();
	Double db = Convert::ToDouble(str);//Double^
	sr->Close();
	return  db;
}

public: void predict(char *filePath)
{
			//根据用户选择调用不同的模型进行预测
			if (comboBox1->Text == "SPA-SVM")
			{
				svm_model *svmModel = svm_load_model("model_snv_spa_svm.txt");
				FILE *fp;
				int line = 0;
				int temp;

				if ((fp = fopen(filePath, "rt")) == NULL)
					return;
				while (1)
				{
					svm_node* input = new svm_node[feature_number + 1];//每个样本由feature_number个特征变量组成
					for (int k = 0; k<feature_number; k++)
					{
						fscanf(fp, "%f", &temp);
						input[k].index = k + 1;
						input[k].value = temp;//input[k].value = temp / (MAX*1.0);
					}
					input[feature_number].index = -1;

					double predictValue = svm_predict(svmModel, input);
					predictvalue.push_back(predictValue);
					if (feof(fp))
						break;
				}
			}
			else if (comboBox1->Text == "MGS-SVM")
			{
				svm_model *svmModel = svm_load_model("model_snv_mgs_svm.txt");
				FILE *fp;
				int line = 0;
				int temp;

				if ((fp = fopen(filePath, "rt")) == NULL)
					return;
				while (1)
				{
					svm_node* input = new svm_node[feature_number + 1];//每个样本由feature_number个特征变量组成
					for (int k = 0; k<feature_number; k++)
					{
						fscanf(fp, "%f", &temp);
						input[k].index = k + 1;
						input[k].value = temp;//input[k].value = temp / (MAX*1.0);
					}
					input[feature_number].index = -1;

					double predictValue = svm_predict(svmModel, input);
					predictvalue.push_back(predictValue);
					if (feof(fp))
						break;
				}
			}
			else
			{
				::MessageBox(NULL, TEXT("请选择数据处理方式！"), TEXT("提示"), MB_OK);
			}
}

public:	void getSpectrumInit()
{
			wrapper.setIntegrationTime(0, integrationTime);  //设置积分时间350ms
			wrapper.setCorrectForDetectorNonlinearity(0, 1); //允许非线性校正
			wrapper.setScansToAverage(0, intSampleAverage);  //设置平均次数5
			wrapper.setBoxcarWidth(0, intBoxcar);            //设置平滑点数3
}
public:	void CutBandprogram()//截取无噪声波段3-502共500个波段
{
			double row[500];
			for (int i = 1, k = 0; i < 501; i++, k++){//1-512波段中挑选3-502波段，下标从0开始即2-501
				row[k] = r[i];
			}
			for (int i = 0, k = 0; i < 500; i++, k++){
				r[i] = row[i];
			}
}
public:	void SNVprogram()//使用SNV算法对原始数据做预处理
{
			for (int i = 0; i < bandNumber; i++){
				sum_x += r[i];
			}
			for (int i = 0; i < bandNumber; i++){
				dr[i] = r[i] - sum_x / bandNumber;//求x减x拔
				sum_drdr += dr[i] * dr[i];
			}
			for (int i = 0; i < bandNumber; i++){
				r[i] = dr[i] / sqrt(sum_drdr / (bandNumber - 1));
			}
			sum_x = 0;
			sum_drdr = 0;
			sum_drdr = 0;
			sum_drdr = 0;
			for (int i = 0; i < bandNumber; i++){
				dr[i] = 0;
			}
}
public:	void SPAprogram()//进行SPA波段提取
{
			outfile.open("afterSelectprogram.txt");
			for (int i = 0; i < feature_number; i++){
				r_spa[i] = r[touying_spa[i] - 1];
				outfile << r_spa[i] << endl;
			}
			outfile.close();
}
public:	void MGSprogram()//进行MGS波段提取
{
			outfile.open("afterSelectprogram.txt");
			for (int i = 0; i < feature_number; i++){
				r_mgs[i] = r[touying_mgs[i] - 1];
				outfile << r_mgs[i] << endl;
			}
			outfile.close();
}

void getB(const char *filePath)
{
	if (comboBox1->Text == "SPA-SVM")//说明是8个特征波段
	{
		double array[9][1] = { 0.0 };
		ifstream infile;
		infile.open(filePath);
		double* ptr = &array[0][0];
		while (!infile.eof())
		{
			infile >> *ptr;
			ptr++;
		}
		infile.close();//到此为止，得到b.txt中的数值，并存入array[8][1]中了
		outfile.open("aftergetB.txt");
		for (int i = 0; i < 9; i++){
			b_spa[i] = array[i][0];
			outfile << b_spa[i] << endl;
		}
		outfile.close();//到此为止，将array[8][1]中的内容输出到aftergetB.txt文件中了
	}
	else if (comboBox1->Text == "MGS-SVM")//说明是15个特征波段
	{
		double array[16][1] = { 0.0 };
		ifstream infile;
		infile.open(filePath);
		double* ptr = &array[0][0];
		while (!infile.eof())
		{
			infile >> *ptr;
			ptr++;
		}
		infile.close();//到此为止，得到b.txt中的数值，并存入array[x][1]中了
		outfile.open("aftergetB.txt");
		for (int i = 0; i < 16; i++){
			b_mgs[i] = array[i][0];
			outfile << b_mgs[i] << endl;
		}
		outfile.close();//到此为止，将array[x][1]中的内容输出到aftergetB.txt文件中了
	}

}

void getY1(const char *filePath)
{
	if (comboBox1->Text == "SPA-SVM")//说明是8个特征波段
	{
		double array[8][1] = { 0.0 };
		ifstream infile;
		infile.open(filePath);
		double* ptr = &array[0][0];
		while (!infile.eof())
		{
			infile >> *ptr;
			ptr++;
		}
		infile.close();
		double arr2[9][1] = { 0.0 };
		arr2[0][0] = 1.0;
		for (int i = 1; i < 9; i++){
			arr2[i][0] = array[i - 1][0];
		}

		//到此为止，得到afterSPAprogram.txt中的数值，并存入array[1:8][0]中了;array[0][0]中是1；
		outfile.open("aftergetY1.txt");
		for (int i = 0; i < 9; i++){
			Y1_spa[i] = arr2[i][0];
			outfile << Y1_spa[i] << endl;
		}
		outfile.close();//到此为止，将array[x][1]中的内容输出到aftergetY1.txt文件中了
	}
	else if (comboBox1->Text == "MGS-SVM")//说明是15个特征波段
	{
		double array[15][1] = { 0.0 };
		ifstream infile;
		infile.open(filePath);
		double* ptr = &array[0][0];
		while (!infile.eof())
		{
			infile >> *ptr;
			ptr++;
		}
		infile.close();
		double arr2[16][1] = { 0.0 };
		arr2[0][0] = 1.0;
		for (int i = 1; i < 16; i++){
			arr2[i][0] = array[i - 1][0];
		}

		//到此为止，得到afterSPAprogram.txt中的数值
		outfile.open("aftergetY1.txt");
		for (int i = 0; i < 16; i++){
			Y1_mgs[i] = arr2[i][0];
			outfile << Y1_mgs[i] << endl;
		}
		outfile.close();//到此为止，将array[x][1]中的内容输出到aftergetY1.txt文件中了
	}
}



void Y1withB()
{
	
	if (comboBox1->Text == "SPA-SVM")//说明是8个特征波段
	{
		Y1_predict = 0;
		Y1_predictlabel = 5;
		double array[9][3] = { 0.0 };
		for (int i = 0; i < 9; i++)
		{
			array[i][0] = b_spa[i];
			array[i][1] = Y1_spa[i];

		}//到此为止，得到b.txt中的数存在array第1列,得到afterSPAprogram.txt中的数存在array第2列

		outfile.open("Y1_predictlabel.txt");
		outfile << "array[i][2]:" << endl;
		//进行向量的点乘运算
		for (int i = 0; i < 9; i++)
		{
			array[i][2] = array[i][0] * array[i][1];
			outfile << array[i][2] << endl;
		}
		outfile << "Y1_predictlabel:" << endl;
		for (int i = 0; i < 9; i++){
			Y1_predict = Y1_predict + array[i][2];
			outfile << Y1_predict << endl;
		}
		//向量的点乘运算结束
	}
	else if (comboBox1->Text == "MGS-SVM")//说明是15个特征波段
	{
		Y1_predict = 0;
		Y1_predictlabel = 5;
		double array[16][3] = { 0.0 };
		for (int i = 0; i < 16; i++)
		{
			array[i][0] = b_mgs[i];
			array[i][1] = Y1_mgs[i];

		}//到此为止，得到b.txt中的数存在array第1列,得到afterSPAprogram.txt中的数存在array第2列

		outfile.open("Y1_predictlabel.txt");
		outfile << "array[i][2]:" << endl;
		//进行向量的点乘运算
		for (int i = 0; i < 16; i++)
		{
			array[i][2] = array[i][0] * array[i][1];
			outfile << array[i][2] << endl;
		}
		outfile << "Y1_predictlabel:" << endl;
		for (int i = 0; i < 16; i++){
			Y1_predict = Y1_predict + array[i][2];
			outfile << Y1_predict << endl;
		}
		//向量的点乘运算结束
	}
	//根据值判断等级 model中是两个等级分别为1和2，所以取1和2中间的1.5作为阈值区分两个等级
	if (Y1_predict<1.5)
	{
		Y1_predictlabel = 0;//健康
	}
	else if (Y1_predict >= 1.5)
	{
		Y1_predictlabel = 1;//感染
	}

	//将结果输出到文件中
	outfile << "grade:" << Y1_predictlabel << "grade=0 表示健康；grade=1 表示感染" << endl;
	outfile << "value:" << Y1_predict << endl;
	outfile.close();//到此为止，将array[x][1]中的内容输出到aftergetY1.txt文件中了
}




public:bool getRealValue()
{
		   FILE *fp;
		   int temp;
		   if ((fp = fopen("test_label.txt", "rt")) == NULL)
			   return false;
		   while (1)
		   {
			   fscanf(fp, "%f", &temp);
			   realvalue.push_back(temp);
			   if (feof(fp))
				   break;
		   }
		   return true;
}
public:double getAccuracy()
{
		   if (!getRealValue())
			   return 0.0;
		   int counter = 0;
		   int counter1 = 0;
		   for (int i = 0; i<realvalue.size(); i++)
		   {
			   if (realvalue.at(i) == predictvalue.at(i))
			   {
				   counter++;//测试正确的个数  
			   }
			   if (predictvalue.at(i) != 0)
				   counter1++;
		   }
		   return counter*1.0 / realvalue.size();
}
public: void getOneSample(const char *filePath)
{
			double array[512][1] = { 0.0 };

			ifstream infile;

			infile.open(filePath);

			double* ptr = &array[0][0];

			while (1)
			{
				infile >> *ptr;
				ptr++;
				if (infile.eof())
					break;
			}
			infile.close();
			outfile.open("aftergetOneSample.txt");
			for (int i = 0; i < 512; i++){
				r[i] = array[i][0];
				outfile << r[i] << endl;
			}
			outfile.close();
}

public:string getTime()
{
		   time_t timep;
		   time(&timep);
		   char tmp[64];
		   strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
		   return tmp;
}

};
}