#pragma once


namespace VC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		bool fActive;
		bool fPause;

        long dwReadTotal;
        long dwWriteTotal;

		Form1(void)
		{			
			InitializeComponent();
			fActive = false;
			fPause = false;

			dwReadTotal = 0;
			dwWriteTotal = 0;
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Splitter^  splitter1;
	protected: 
	private: System::Windows::Forms::RichTextBox^  redtData;
	private: System::Windows::Forms::RichTextBox^  ctlData;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblTip;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: AxCommMonitor6x::AxCommMonitor^  axCommMonitor1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  btnPause;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::Button^  btnClear;

 
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->redtData = (gcnew System::Windows::Forms::RichTextBox());
			this->ctlData = (gcnew System::Windows::Forms::RichTextBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->lblTip = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->axCommMonitor1 = (gcnew AxCommMonitor6x::AxCommMonitor());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->btnPause = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->statusStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axCommMonitor1))->BeginInit();
			this->SuspendLayout();
			// 
			// splitter1
			// 
			this->splitter1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->splitter1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->splitter1->Location = System::Drawing::Point(0, 375);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(843, 5);
			this->splitter1->TabIndex = 12;
			this->splitter1->TabStop = false;
			this->splitter1->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &Form1::splitter1_SplitterMoved);
			// 
			// redtData
			// 
			this->redtData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->redtData->Dock = System::Windows::Forms::DockStyle::Fill;
			this->redtData->Location = System::Drawing::Point(0, 48);
			this->redtData->Name = L"redtData";
			this->redtData->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->redtData->Size = System::Drawing::Size(843, 327);
			this->redtData->TabIndex = 10;
			this->redtData->Text = L"";
			// 
			// ctlData
			// 
			this->ctlData->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ctlData->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->ctlData->Location = System::Drawing::Point(0, 380);
			this->ctlData->Name = L"ctlData";
			this->ctlData->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->ctlData->Size = System::Drawing::Size(843, 210);
			this->ctlData->TabIndex = 11;
			this->ctlData->Text = L"";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->lblTip, this->toolStripStatusLabel4, 
				this->toolStripStatusLabel1});
			this->statusStrip1->Location = System::Drawing::Point(0, 590);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(843, 22);
			this->statusStrip1->TabIndex = 13;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// lblTip
			// 
			this->lblTip->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->lblTip->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->lblTip->Name = L"lblTip";
			this->lblTip->Size = System::Drawing::Size(414, 17);
			this->lblTip->Spring = true;
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->toolStripStatusLabel4->IsLink = true;
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			this->toolStripStatusLabel4->Size = System::Drawing::Size(414, 17);
			this->toolStripStatusLabel4->Spring = true;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::None;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// axCommMonitor1
			// 
			this->axCommMonitor1->Dock = System::Windows::Forms::DockStyle::Top;
			this->axCommMonitor1->Location = System::Drawing::Point(0, 0);
			this->axCommMonitor1->Name = L"axCommMonitor1";
			this->axCommMonitor1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axCommMonitor1.OcxState")));
			this->axCommMonitor1->Size = System::Drawing::Size(843, 48);
			this->axCommMonitor1->TabIndex = 14;
			this->axCommMonitor1->OnDblClick += gcnew System::EventHandler(this, &Form1::axCommMonitor1_OnDblClick);
			this->axCommMonitor1->OnAscii += gcnew AxCommMonitor6x::ICommMonitor6Events_OnAsciiEventHandler(this, &Form1::axCommMonitor1_OnAscii);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6"});
			this->comboBox1->Location = System::Drawing::Point(281, 15);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(45, 20);
			this->comboBox1->TabIndex = 20;
			this->comboBox1->Text = L"COM1";
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(667, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 19;
			this->button1->Text = L"ABout";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button4->Location = System::Drawing::Point(748, 12);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 18;
			this->button4->Text = L"Close";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// btnPause
			// 
			this->btnPause->Location = System::Drawing::Point(442, 12);
			this->btnPause->Name = L"btnPause";
			this->btnPause->Size = System::Drawing::Size(93, 23);
			this->btnPause->TabIndex = 17;
			this->btnPause->Text = L"Pause";
			this->btnPause->UseVisualStyleBackColor = true;
			this->btnPause->Click += gcnew System::EventHandler(this, &Form1::btnPause_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->ForeColor = System::Drawing::Color::Black;
			this->btnOpen->Location = System::Drawing::Point(332, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(104, 23);
			this->btnOpen->TabIndex = 16;
			this->btnOpen->Text = L"Start Monitor";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(571, 12);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 23);
			this->btnClear->TabIndex = 15;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &Form1::btnClear_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(843, 612);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->btnPause);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->redtData);
			this->Controls->Add(this->axCommMonitor1);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->ctlData);
			this->Controls->Add(this->statusStrip1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axCommMonitor1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void splitter1_SplitterMoved(System::Object^  sender, System::Windows::Forms::SplitterEventArgs^  e) {
			 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->axCommMonitor1->AboutBox();
		 }
private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->redtData->Clear();
			 this->ctlData->Clear();
		 }

		
private: System::Void btnPause_Click(System::Object^  sender, System::EventArgs^  e) {
		   if (axCommMonitor1->PauseMonitor(fPause))
                 fPause = !fPause;
                 
           if (fPause)
           {
                btnPause->Text = "Continue";
                btnPause->ForeColor = Color::Black;
           }
           else
           {
                btnPause->Text = "Pause";
				btnPause->ForeColor = Color::Blue;
           }
		 }
private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		  if (!fActive)			  
			  fActive = axCommMonitor1->StartMonitor(this->comboBox1->Text->ToString());
          else {         
            axCommMonitor1->StopMonitor();
            fActive = false;
          }

           if (fActive)  
           {
             btnOpen->Text = "Stop Monitor";
			 btnOpen->ForeColor = Color::Blue;
             
           }
           else{
               btnOpen->Text = "Start Monitor";
			   btnOpen->ForeColor = Color::Black;
           }
		 }
private: System::Void axCommMonitor1_OnAscii(System::Object^  sender, AxCommMonitor6x::ICommMonitor6Events_OnAsciiEvent^  e) {
		    const  int  IRP_MJ_CREATE                 =0x00;
            const  int  IRP_MJ_CLOSE                    =0x02;
            const  int  IRP_MJ_READ                     =0x03;
            const  int  IRP_MJ_WRITE                    =0x04;
            const  int  IRP_MJ_DEVICE_CONTROL           =0x0E;
            const  int  IRP_MJ_CLEANUP                  =0x12;
            const  int  IRP_MJ_MAXIMUM_FUNCTION         =0x1B;
            const  int  IRP_MJ_FLUSH_BUFFERS            =0x09;
        
            switch(e->dwCtrlCode)
			{  
               case IRP_MJ_CLOSE:
                    redtData->AppendText(String::Format("{0}: Close\r\n", e->sPortName));
                    break;
               case IRP_MJ_CREATE: 
                    redtData->AppendText(String::Format("{0}: Open\r\n", e->sPortName));
                    break;
               case  IRP_MJ_READ:   {
                    dwReadTotal += e->dwSize;
					redtData->SelectionColor = Color::Blue;
					this->redtData->AppendText(String::Format("{0}, Read({1:D}): {2}\r\n", e->sPortName, e->dwSize, e->sData));                
                    break;
                 }
               case  IRP_MJ_WRITE: {
                    dwWriteTotal += e->dwSize;
                    redtData->SelectionColor = Color::Green;
                    this->redtData->AppendText(String::Format("{0}, Write({1:D}): {2}\r\n", e->sPortName, e->dwSize, e->sData));
                    break;
                 }
              default:  {
                   if (e->dwCtrlCode > 0x400)
                       ctlData->AppendText(String::Format("{0}, CTLCode({1:D}): {2}\r\n", e->sPortName, e->dwCtrlCode, e->sData));
                 break;
               }
            }
                
            if ((e->dwCtrlCode == IRP_MJ_READ)  || (e->dwCtrlCode == IRP_MJ_WRITE))
            {
                lblTip->Text = String::Format("Write:  {0:D}(Bytes), Read: {1:D}(Bytes)", dwWriteTotal, dwReadTotal);
                
            }
		 }
private: System::Void axCommMonitor1_OnDblClick(System::Object^  sender, System::EventArgs^  e) {
			  
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			  this->Text = axCommMonitor1->Caption + " FOR VS2008 VC DEMO";
		 }
};
}

