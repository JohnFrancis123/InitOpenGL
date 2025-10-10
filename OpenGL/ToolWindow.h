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

		static int InvertColorsChannel;

	private: System::Windows::Forms::TrackBar^ UTrackBar;
	private: System::Windows::Forms::TrackBar^ VTrackBar;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckBox^ Invert;
	private: System::Windows::Forms::TrackBar^ YTrackBar;
	
	public:
		ToolWindow(void)
		{
			InitializeComponent();

			InvertColorsChannel = Invert->Checked;

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
			this->YTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->UTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->VTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Invert = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// YTrackBar
			// 
			this->YTrackBar->AccessibleName = L"";
			this->YTrackBar->Location = System::Drawing::Point(12, 12);
			this->YTrackBar->Maximum = 200;
			this->YTrackBar->Name = L"YTrackBar";
			this->YTrackBar->Size = System::Drawing::Size(798, 56);
			this->YTrackBar->TabIndex = 3;
			this->YTrackBar->Value = 100;
			this->YTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::yTrackBar_Scroll);
			// 
			// UTrackBar
			// 
			this->UTrackBar->Location = System::Drawing::Point(12, 74);
			this->UTrackBar->Maximum = 200;
			this->UTrackBar->Name = L"UTrackBar";
			this->UTrackBar->Size = System::Drawing::Size(798, 56);
			this->UTrackBar->TabIndex = 4;
			this->UTrackBar->Value = 100;
			this->UTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::uTrackBar_Scroll);
			// 
			// VTrackBar
			// 
			this->VTrackBar->Location = System::Drawing::Point(12, 137);
			this->VTrackBar->Maximum = 200;
			this->VTrackBar->Name = L"VTrackBar";
			this->VTrackBar->Size = System::Drawing::Size(798, 56);
			this->VTrackBar->TabIndex = 5;
			this->VTrackBar->Value = 100;
			this->VTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::vTrackBar_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 16);
			this->label1->TabIndex = 6;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &ToolWindow::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 115);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 16);
			this->label2->TabIndex = 7;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 176);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 16);
			this->label3->TabIndex = 8;
			this->label3->Text = L"label3";
			// 
			// Invert
			// 
			this->Invert->AutoSize = true;
			this->Invert->Location = System::Drawing::Point(12, 196);
			this->Invert->Name = L"Invert";
			this->Invert->Size = System::Drawing::Size(103, 20);
			this->Invert->TabIndex = 9;
			this->Invert->Text = L"Invert Colors";
			this->Invert->UseVisualStyleBackColor = true;
			this->Invert->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::Invert_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(836, 372);
			this->Controls->Add(this->Invert);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->VTrackBar);
			this->Controls->Add(this->UTrackBar);
			this->Controls->Add(this->YTrackBar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"Tool Box";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

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

private: System::Void Invert_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	InvertColorsChannel = Invert->Checked;
}
};
}
