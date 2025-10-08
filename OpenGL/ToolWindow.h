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

	private: System::Windows::Forms::TrackBar^ YTrackBar;
	private: System::Windows::Forms::TrackBar^ UTrackBar;
	private: System::Windows::Forms::Label^ YLabel;
	private: System::Windows::Forms::Label^ ULabel;
	private: System::Windows::Forms::Label^ VLabel;



	private: System::Windows::Forms::TrackBar^ VTrackBar;

	public:

		   

		ToolWindow(void)
		{
			InitializeComponent();
			RenderRedChannel = checkBoxRedChannel->Checked;
			RenderGreenChannel = checkBoxGreenChannel->Checked;
			RenderBlueChannel = checkBoxBlueChannel->Checked;

			YTrackBar->Value = 100;
			UTrackBar->Value = 100;
			VTrackBar->Value = 100;

			YLabel->Text = "Y: " + YTrackBar->Value.ToString() + "%";
			ULabel->Text = "U: " + UTrackBar->Value.ToString() + "%";
			VLabel->Text = "V: " + VTrackBar->Value.ToString() + "%";
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
			this->YLabel = (gcnew System::Windows::Forms::Label());
			this->ULabel = (gcnew System::Windows::Forms::Label());
			this->VLabel = (gcnew System::Windows::Forms::Label());
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
			this->YTrackBar->Location = System::Drawing::Point(13, 94);
			this->YTrackBar->Maximum = 200;
			this->YTrackBar->Name = L"YTrackBar";
			this->YTrackBar->Size = System::Drawing::Size(257, 56);
			this->YTrackBar->TabIndex = 3;
			this->YTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::YTrackBar_Scroll);
			// 
			// UTrackBar
			// 
			this->UTrackBar->Location = System::Drawing::Point(13, 157);
			this->UTrackBar->Maximum = 200;
			this->UTrackBar->Name = L"UTrackBar";
			this->UTrackBar->Size = System::Drawing::Size(257, 56);
			this->UTrackBar->TabIndex = 4;
			this->UTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::UTrackBar_Scroll);
			// 
			// VTrackBar
			// 
			this->VTrackBar->Location = System::Drawing::Point(13, 219);
			this->VTrackBar->Maximum = 200;
			this->VTrackBar->Name = L"VTrackBar";
			this->VTrackBar->Size = System::Drawing::Size(257, 56);
			this->VTrackBar->TabIndex = 5;
			this->VTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::VTrackBar_Scroll);
			// 
			// YLabel
			// 
			this->YLabel->AutoSize = true;
			this->YLabel->Location = System::Drawing::Point(13, 133);
			this->YLabel->Name = L"YLabel";
			this->YLabel->Size = System::Drawing::Size(44, 16);
			this->YLabel->TabIndex = 6;
			this->YLabel->Text = L"label1";
			// 
			// ULabel
			// 
			this->ULabel->AutoSize = true;
			this->ULabel->Location = System::Drawing::Point(16, 197);
			this->ULabel->Name = L"ULabel";
			this->ULabel->Size = System::Drawing::Size(44, 16);
			this->ULabel->TabIndex = 7;
			this->ULabel->Text = L"label2";
			// 
			// VLabel
			// 
			this->VLabel->AutoSize = true;
			this->VLabel->Location = System::Drawing::Point(19, 258);
			this->VLabel->Name = L"VLabel";
			this->VLabel->Size = System::Drawing::Size(44, 16);
			this->VLabel->TabIndex = 8;
			this->VLabel->Text = L"label3";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 315);
			this->Controls->Add(this->VLabel);
			this->Controls->Add(this->ULabel);
			this->Controls->Add(this->YLabel);
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

	private: System::Void YTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderYChannel = YTrackBar->Value;
		YLabel->Text = "Y: " + YTrackBar->Value.ToString() + "%";
	}
	private: System::Void UTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderUChannel = UTrackBar->Value;
		ULabel->Text = "U: " + UTrackBar->Value.ToString() + "%";
	}
	private: System::Void VTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		RenderVChannel = VTrackBar->Value;
		VLabel->Text = "V: " + VTrackBar->Value.ToString() + "%";
	}
};
}
