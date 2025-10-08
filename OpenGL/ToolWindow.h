#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static bool RenderBlueChannel;

		static int RenderYChannel;
		static int RenderUChannel;
		static int RenderVChannel;
	private: System::Windows::Forms::TrackBar^ UTrackBar;
	private: System::Windows::Forms::TrackBar^ VTrackBar;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ YTrackBar;
	
	public:
		ToolWindow(void)
		{
			InitializeComponent();
			RenderRedChannel = checkBoxRedChannel->Checked;
			RenderGreenChannel = checkBoxGreenChannel->Checked;
			RenderBlueChannel = checkBoxBlueChannel->Checked;

			RenderYChannel = YTrackBar->Value;
			RenderUChannel = UTrackBar->Value;
			RenderVChannel = VTrackBar->Value;

			label1->Text = "Y: " + YTrackBar->Value.ToString() + "%";
			label2->Text = "U: " + UTrackBar->Value.ToString() + "%";
			label3->Text = "V: " + VTrackBar->Value.ToString() + "%";
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkBoxRedChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxGreenChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxBlueChannel;

	protected:

	protected:

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->checkBoxRedChannel = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxGreenChannel = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxBlueChannel = (gcnew System::Windows::Forms::CheckBox());
			this->YTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->UTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->VTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBoxRedChannel
			// 
			this->checkBoxRedChannel->AutoSize = true;
			this->checkBoxRedChannel->Location = System::Drawing::Point(13, 13);
			this->checkBoxRedChannel->Name = L"checkBoxRedChannel";
			this->checkBoxRedChannel->Size = System::Drawing::Size(107, 20);
			this->checkBoxRedChannel->TabIndex = 0;
			this->checkBoxRedChannel->Text = L"Red Channel";
			this->checkBoxRedChannel->UseVisualStyleBackColor = true;
			this->checkBoxRedChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox1_CheckedChanged);
			// 
			// checkBoxGreenChannel
			// 
			this->checkBoxGreenChannel->AutoSize = true;
			this->checkBoxGreenChannel->Location = System::Drawing::Point(13, 40);
			this->checkBoxGreenChannel->Name = L"checkBoxGreenChannel";
			this->checkBoxGreenChannel->Size = System::Drawing::Size(118, 20);
			this->checkBoxGreenChannel->TabIndex = 1;
			this->checkBoxGreenChannel->Text = L"Green Channel";
			this->checkBoxGreenChannel->UseVisualStyleBackColor = true;
			this->checkBoxGreenChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxGreenChannel_CheckedChanged);
			// 
			// checkBoxBlueChannel
			// 
			this->checkBoxBlueChannel->AutoSize = true;
			this->checkBoxBlueChannel->Location = System::Drawing::Point(13, 67);
			this->checkBoxBlueChannel->Name = L"checkBoxBlueChannel";
			this->checkBoxBlueChannel->Size = System::Drawing::Size(108, 20);
			this->checkBoxBlueChannel->TabIndex = 2;
			this->checkBoxBlueChannel->Text = L"Blue Channel";
			this->checkBoxBlueChannel->UseVisualStyleBackColor = true;
			this->checkBoxBlueChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxBlueChannel_CheckedChanged);
			// 
			// YTrackBar
			// 
			this->YTrackBar->AccessibleName = L"";
			this->YTrackBar->Location = System::Drawing::Point(27, 93);
			this->YTrackBar->Maximum = 200;
			this->YTrackBar->Name = L"YTrackBar";
			this->YTrackBar->Size = System::Drawing::Size(263, 56);
			this->YTrackBar->TabIndex = 3;
			this->YTrackBar->Value = 100;
			this->YTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::yTrackBar_Scroll);
			// 
			// UTrackBar
			// 
			this->UTrackBar->Location = System::Drawing::Point(27, 155);
			this->UTrackBar->Maximum = 200;
			this->UTrackBar->Name = L"UTrackBar";
			this->UTrackBar->Size = System::Drawing::Size(263, 56);
			this->UTrackBar->TabIndex = 4;
			this->UTrackBar->Value = 100;
			this->UTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::uTrackBar_Scroll);
			// 
			// VTrackBar
			// 
			this->VTrackBar->Location = System::Drawing::Point(27, 218);
			this->VTrackBar->Maximum = 200;
			this->VTrackBar->Name = L"VTrackBar";
			this->VTrackBar->Size = System::Drawing::Size(263, 56);
			this->VTrackBar->TabIndex = 5;
			this->VTrackBar->Value = 100;
			this->VTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::vTrackBar_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 132);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 16);
			this->label1->TabIndex = 6;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &ToolWindow::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 196);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 16);
			this->label2->TabIndex = 7;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(33, 257);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 16);
			this->label3->TabIndex = 8;
			this->label3->Text = L"label3";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(306, 372);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->VTrackBar);
			this->Controls->Add(this->UTrackBar);
			this->Controls->Add(this->YTrackBar);
			this->Controls->Add(this->checkBoxBlueChannel);
			this->Controls->Add(this->checkBoxGreenChannel);
			this->Controls->Add(this->checkBoxRedChannel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderRedChannel = checkBoxRedChannel->Checked;
	}
	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderGreenChannel = checkBoxGreenChannel->Checked;
	}
	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderBlueChannel = checkBoxBlueChannel->Checked;
	}

	private: System::Void yTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderYChannel = YTrackBar->Value;
		label1->Text = "Y: " + YTrackBar->Value.ToString() + "%";
	}
	private: System::Void uTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderUChannel = UTrackBar->Value;
		label2->Text = "U: " + UTrackBar->Value.ToString() + "%";
	}
	private: System::Void vTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderVChannel = VTrackBar->Value;
		label3->Text = "V: " + VTrackBar->Value.ToString() + "%";
	}




private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {

}

};
}
