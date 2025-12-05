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
	private:
		// Single-use flags (set by UI, consumed by caller)
		bool m_resetLightPosPressed = false;
		bool m_resetTransformPressed = false;


	public:
		bool GetMoveLightValue() { return MoveLightRadio->Checked; }
		bool GetTransformValue() { return TransformRadio->Checked; }
		bool GetWaterSceneValue() { return WaterSceneRadio->Checked; }
		bool GetSpaceSceneValue() { return SpaceSceneRadio->Checked; }
		bool GetResetLightPosPressed() { bool v = m_resetLightPosPressed; m_resetLightPosPressed = false; return v; }
		bool GetResetTransformPressed() { bool v = m_resetTransformPressed; m_resetTransformPressed = false; return v; }

		int GetSpecularStrength() { return SpecularStrength->Value; }
		double GetSpecularColorR() { return (double)SpecularColorR->Value / 100.0; }
		double GetSpecularColorG() { return (double)SpecularColorG->Value / 100.0; }
		double GetSpecularColorB() { return (double)SpecularColorB->Value / 100.0; }
		double GetFrequency() { return (double)Frequency->Value / 100.0; }
		double GetAmplitude() { return (double)Amplitude->Value / 100.0; }

		bool GetTranslateEnabled() { return TranslateCheckbox->Checked; }
		bool GetRotateEnabled() { return RotateCheckbox->Checked; }
		bool GetScaleEnabled() { return ScaleCheckbox->Checked; }
		bool GetWireframeEnabled() { return WireframeRenderCheckbox->Checked; }
		bool GetTintBlueEnabled() { return TintBlueCheckbox->Checked; }

	

		static bool RenderRedChannel;
		static bool RenderGreenChannel;
	private: System::Windows::Forms::RadioButton^ MoveLightRadio;
	private: System::Windows::Forms::RadioButton^ TransformRadio;
	private: System::Windows::Forms::RadioButton^ WaterSceneRadio;
	private: System::Windows::Forms::RadioButton^ SpaceSceneRadio;
	private: System::Windows::Forms::Button^ ResetLightPosButton;
	private: System::Windows::Forms::Label^ SpecularStrengthLabel;
	private: System::Windows::Forms::TrackBar^ SpecularStrength;
	private: System::Windows::Forms::TrackBar^ SpecularColorR;
	private: System::Windows::Forms::TrackBar^ SpecularColorG;
	private: System::Windows::Forms::TrackBar^ SpecularColorB;

	

		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::Button^ ResetTransformButton;
		private: System::Windows::Forms::CheckBox^ TranslateCheckbox;
		private: System::Windows::Forms::CheckBox^ RotateCheckbox;
		private: System::Windows::Forms::CheckBox^ ScaleCheckbox;

		private: System::Windows::Forms::TrackBar^ Frequency;
		private: System::Windows::Forms::TrackBar^ Amplitude;
		private: System::Windows::Forms::CheckBox^ WireframeRenderCheckbox;
		private: System::Windows::Forms::CheckBox^ TintBlueCheckbox;
		private: System::Windows::Forms::Label^ SpecularStrengthVal;
		private: System::Windows::Forms::Label^ ColorRVal;
		private: System::Windows::Forms::Label^ ColorGVal;
		private: System::Windows::Forms::Label^ ColorBVal;
		private: System::Windows::Forms::Label^ FrequencyVal;
		private: System::Windows::Forms::Label^ AmplitudeVal;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Label^ label6;

		


		

	public:

	public:


		   static bool RenderBlueChannel;

		ToolWindow(void)
		{
			InitializeComponent();
			// set initial label values (colors, frequency, amplitude are divided by 100)
			this->SpecularStrengthVal->Text = System::Convert::ToString(this->SpecularStrength->Value);
			this->ColorRVal->Text = System::String::Format("{0:F2}", (double)this->SpecularColorR->Value / 100.0);
			this->ColorGVal->Text = System::String::Format("{0:F2}", (double)this->SpecularColorG->Value / 100.0);
			this->ColorBVal->Text = System::String::Format("{0:F2}", (double)this->SpecularColorB->Value / 100.0);
			this->FrequencyVal->Text = System::String::Format("{0:F2}", (double)this->Frequency->Value / 100.0);
			this->AmplitudeVal->Text = System::String::Format("{0:F2}", (double)this->Amplitude->Value / 100.0);
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
		/// 
		///
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->MoveLightRadio = (gcnew System::Windows::Forms::RadioButton());
			this->TransformRadio = (gcnew System::Windows::Forms::RadioButton());
			this->WaterSceneRadio = (gcnew System::Windows::Forms::RadioButton());
			this->SpaceSceneRadio = (gcnew System::Windows::Forms::RadioButton());
			this->ResetLightPosButton = (gcnew System::Windows::Forms::Button());
			this->SpecularStrengthLabel = (gcnew System::Windows::Forms::Label());
			this->SpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorR = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorG = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorB = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ResetTransformButton = (gcnew System::Windows::Forms::Button());
			this->TranslateCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->RotateCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->ScaleCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->Frequency = (gcnew System::Windows::Forms::TrackBar());
			this->Amplitude = (gcnew System::Windows::Forms::TrackBar());
			this->WireframeRenderCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->TintBlueCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->SpecularStrengthVal = (gcnew System::Windows::Forms::Label());
			this->ColorRVal = (gcnew System::Windows::Forms::Label());
			this->ColorGVal = (gcnew System::Windows::Forms::Label());
			this->ColorBVal = (gcnew System::Windows::Forms::Label());
			this->FrequencyVal = (gcnew System::Windows::Forms::Label());
			this->AmplitudeVal = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Frequency))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Amplitude))->BeginInit();
			this->SuspendLayout();
			// 
			// MoveLightRadio
			// 
			this->MoveLightRadio->AutoSize = true;
			this->MoveLightRadio->Location = System::Drawing::Point(32, 13);
			this->MoveLightRadio->Name = L"MoveLightRadio";
			this->MoveLightRadio->Size = System::Drawing::Size(111, 24);
			this->MoveLightRadio->TabIndex = 0;
			this->MoveLightRadio->TabStop = true;
			this->MoveLightRadio->Text = L"Move Light";
			this->MoveLightRadio->UseVisualStyleBackColor = true;
			this->MoveLightRadio->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::MoveLightRadio_CheckedChanged);
			// 
			// TransformRadio
			// 
			this->TransformRadio->AutoSize = true;
			this->TransformRadio->Location = System::Drawing::Point(37, 358);
			this->TransformRadio->Name = L"TransformRadio";
			this->TransformRadio->Size = System::Drawing::Size(106, 24);
			this->TransformRadio->TabIndex = 1;
			this->TransformRadio->TabStop = true;
			this->TransformRadio->Text = L"Transform";
			this->TransformRadio->UseVisualStyleBackColor = true;
			this->TransformRadio->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TransformRadio_CheckedChanged);
			// 
			// WaterSceneRadio
			// 
			this->WaterSceneRadio->AutoSize = true;
			this->WaterSceneRadio->Location = System::Drawing::Point(37, 519);
	 this->WaterSceneRadio->Name = L"WaterSceneRadio";
	 this->WaterSceneRadio->Size = System::Drawing::Size(127, 24);
	 this->WaterSceneRadio->TabIndex = 2;
	 this->WaterSceneRadio->TabStop = true;
	 this->WaterSceneRadio->Text = L"Water Scene";
	 this->WaterSceneRadio->UseVisualStyleBackColor = true;
	 this->WaterSceneRadio->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WaterSceneRadio_CheckedChanged);
		// 
		// SpaceSceneRadio
		// 
		this->SpaceSceneRadio->AutoSize = true;
		this->SpaceSceneRadio->Location = System::Drawing::Point(32, 748);
		this->SpaceSceneRadio->Name = L"SpaceSceneRadio";
		this->SpaceSceneRadio->Size = System::Drawing::Size(130, 24);
		this->SpaceSceneRadio->TabIndex = 3;
		this->SpaceSceneRadio->TabStop = true;
		this->SpaceSceneRadio->Text = L"Space Scene";
		this->SpaceSceneRadio->UseVisualStyleBackColor = true;
		this->SpaceSceneRadio->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::SpaceSceneRadio_CheckedChanged);
		// 
		// ResetLightPosButton
		// 
		this->ResetLightPosButton->Location = System::Drawing::Point(54, 43);
		this->ResetLightPosButton->Name = L"ResetLightPosButton";
		this->ResetLightPosButton->Size = System::Drawing::Size(218, 35);
		this->ResetLightPosButton->TabIndex = 4;
		this->ResetLightPosButton->Text = L"Reset Light Position";
		this->ResetLightPosButton->UseVisualStyleBackColor = true;
		this->ResetLightPosButton->Click += gcnew System::EventHandler(this, &ToolWindow::ResetLightPosButton_Click);
		// 
		// SpecularStrengthLabel
		// 
		this->SpecularStrengthLabel->AutoSize = true;
		this->SpecularStrengthLabel->Location = System::Drawing::Point(28, 110);
		this->SpecularStrengthLabel->Name = L"SpecularStrengthLabel";
		this->SpecularStrengthLabel->Size = System::Drawing::Size(138, 20);
		this->SpecularStrengthLabel->TabIndex = 5;
		this->SpecularStrengthLabel->Text = L"Specular Strength";
		// 
		// SpecularStrength
		// 
		this->SpecularStrength->Location = System::Drawing::Point(185, 84);
		this->SpecularStrength->Maximum = 128;
		this->SpecularStrength->Minimum = 1;
		this->SpecularStrength->Name = L"SpecularStrength";
		this->SpecularStrength->Size = System::Drawing::Size(240, 69);
		this->SpecularStrength->TabIndex = 6;
		this->SpecularStrength->Value = 4;
		this->SpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularStrength_Scroll);
		// 
		// SpecularColorR
		// 
		this->SpecularColorR->Location = System::Drawing::Point(175, 158);
		this->SpecularColorR->Maximum = 300;
		this->SpecularColorR->Name = L"SpecularColorR";
		this->SpecularColorR->Size = System::Drawing::Size(250, 69);
		this->SpecularColorR->TabIndex = 7;
		this->SpecularColorR->Value = 100;
		this->SpecularColorR->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularColorR_Scroll);
		// 
		// SpecularColorG
		// 
		this->SpecularColorG->Location = System::Drawing::Point(175, 235);
	 this->SpecularColorG->Maximum = 300;
	 this->SpecularColorG->Name = L"SpecularColorG";
	 this->SpecularColorG->Size = System::Drawing::Size(250, 69);
	 this->SpecularColorG->TabIndex = 8;
	 this->SpecularColorG->Value = 100;
	 this->SpecularColorG->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularColorG_Scroll);
		// 
		// SpecularColorB
		// 
		this->SpecularColorB->Location = System::Drawing::Point(174, 310);
		this->SpecularColorB->Maximum = 300;
		this->SpecularColorB->Name = L"SpecularColorB";
		this->SpecularColorB->Size = System::Drawing::Size(250, 69);
		this->SpecularColorB->TabIndex = 9;
		this->SpecularColorB->Value = 100;
		this->SpecularColorB->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularColorB_Scroll);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(28, 170);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(113, 20);
		this->label1->TabIndex = 10;
		this->label1->Text = L"Specular Color";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(148, 180);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(21, 20);
		this->label2->TabIndex = 11;
		this->label2->Text = L"R";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(148, 247);
	 this->label3->Name = L"label3";
	 this->label3->Size = System::Drawing::Size(22, 20);
	 this->label3->TabIndex = 12;
	 this->label3->Text = L"G";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(148, 322);
	 this->label4->Name = L"label4";
	 this->label4->Size = System::Drawing::Size(20, 20);
	 this->label4->TabIndex = 13;
	 this->label4->Text = L"B";
		// 
		// ResetTransformButton
		// 
		this->ResetTransformButton->Location = System::Drawing::Point(54, 388);
	 this->ResetTransformButton->Name = L"ResetTransformButton";
	 this->ResetTransformButton->Size = System::Drawing::Size(218, 36);
	 this->ResetTransformButton->TabIndex = 14;
	 this->ResetTransformButton->Text = L"Reset Transform";
	 this->ResetTransformButton->UseVisualStyleBackColor = true;
	 this->ResetTransformButton->Click += gcnew System::EventHandler(this, &ToolWindow::ResetTransformButton_Click);
		// 
		// TranslateCheckbox
		// 
		this->TranslateCheckbox->AutoSize = true;
	 this->TranslateCheckbox->Location = System::Drawing::Point(99, 430);
	 this->TranslateCheckbox->Name = L"TranslateCheckbox";
	 this->TranslateCheckbox->Size = System::Drawing::Size(101, 24);
	 this->TranslateCheckbox->TabIndex = 15;
	 this->TranslateCheckbox->Text = L"Translate";
	 this->TranslateCheckbox->UseVisualStyleBackColor = true;
	 this->TranslateCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TranslateCheckbox_CheckedChanged);
		// 
		// RotateCheckbox
		// 
		this->RotateCheckbox->AutoSize = true;
	 this->RotateCheckbox->Location = System::Drawing::Point(99, 460);
	 this->RotateCheckbox->Name = L"RotateCheckbox";
	 this->RotateCheckbox->Size = System::Drawing::Size(84, 24);
	 this->RotateCheckbox->TabIndex = 16;
	 this->RotateCheckbox->Text = L"Rotate";
	 this->RotateCheckbox->UseVisualStyleBackColor = true;
	 this->RotateCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::RotateCheckbox_CheckedChanged);
		// 
		// ScaleCheckbox
		// 
		this->ScaleCheckbox->AutoSize = true;
	 this->ScaleCheckbox->Location = System::Drawing::Point(99, 490);
	 this->ScaleCheckbox->Name = L"ScaleCheckbox";
	 this->ScaleCheckbox->Size = System::Drawing::Size(75, 24);
	 this->ScaleCheckbox->TabIndex = 17;
	 this->ScaleCheckbox->Text = L"Scale";
	 this->ScaleCheckbox->UseVisualStyleBackColor = true;
	 this->ScaleCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::ScaleCheckbox_CheckedChanged);
		// 
		// Frequency
		// 
		this->Frequency->Location = System::Drawing::Point(151, 549);
	 this->Frequency->Maximum = 400;
	 this->Frequency->Minimum = 1;
	 this->Frequency->Name = L"Frequency";
	 this->Frequency->Size = System::Drawing::Size(273, 69);
	 this->Frequency->TabIndex = 19;
	 this->Frequency->Value = 400;
	 this->Frequency->Scroll += gcnew System::EventHandler(this, &ToolWindow::Frequency_Scroll);
		// 
		// Amplitude
		// 
		this->Amplitude->Location = System::Drawing::Point(151, 610);
	 this->Amplitude->Maximum = 100;
	 this->Amplitude->Name = L"Amplitude";
	 this->Amplitude->Size = System::Drawing::Size(273, 69);
	 this->Amplitude->TabIndex = 20;
	 this->Amplitude->Value = 1;
	 this->Amplitude->Scroll += gcnew System::EventHandler(this, &ToolWindow::Amplitude_Scroll);
		// 
		// WireframeRenderCheckbox
		// 
		this->WireframeRenderCheckbox->AutoSize = true;
	 this->WireframeRenderCheckbox->Location = System::Drawing::Point(99, 669);
	 this->WireframeRenderCheckbox->Name = L"WireframeRenderCheckbox";
	 this->WireframeRenderCheckbox->Size = System::Drawing::Size(165, 24);
	 this->WireframeRenderCheckbox->TabIndex = 21;
	 this->WireframeRenderCheckbox->Text = L"Wireframe Render";
	 this->WireframeRenderCheckbox->UseVisualStyleBackColor = true;
	 this->WireframeRenderCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WireframeRenderCheckbox_CheckedChanged);
		// 
		// TintBlueCheckbox
		// 
		this->TintBlueCheckbox->AutoSize = true;
	 this->TintBlueCheckbox->Location = System::Drawing::Point(99, 700);
	 this->TintBlueCheckbox->Name = L"TintBlueCheckbox";
	 this->TintBlueCheckbox->Size = System::Drawing::Size(97, 24);
	 this->TintBlueCheckbox->TabIndex = 22;
	 this->TintBlueCheckbox->Text = L"Tint Blue";
	 this->TintBlueCheckbox->UseVisualStyleBackColor = true;
	 this->TintBlueCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TintBlueCheckbox_CheckedChanged);
		// 
		// SpecularStrengthVal
		// 
		this->SpecularStrengthVal->AutoSize = true;
	 this->SpecularStrengthVal->Location = System::Drawing::Point(431, 84);
	 this->SpecularStrengthVal->Name = L"SpecularStrengthVal";
	 this->SpecularStrengthVal->Size = System::Drawing::Size(18, 20);
	 this->SpecularStrengthVal->TabIndex = 23;
	 this->SpecularStrengthVal->Text = L"4";
		// 
		// ColorRVal
		// 
		this->ColorRVal->AutoSize = true;
	 this->ColorRVal->Location = System::Drawing::Point(418, 158);
	 this->ColorRVal->Name = L"ColorRVal";
	 this->ColorRVal->Size = System::Drawing::Size(40, 20);
	 this->ColorRVal->TabIndex = 24;
	 this->ColorRVal->Text = L"1.00";
		// 
		// ColorGVal
		// 
		this->ColorGVal->AutoSize = true;
	 this->ColorGVal->Location = System::Drawing::Point(418, 235);
	 this->ColorGVal->Name = L"ColorGVal";
	 this->ColorGVal->Size = System::Drawing::Size(40, 20);
	 this->ColorGVal->TabIndex = 25;
	 this->ColorGVal->Text = L"1.00";
		// 
		// ColorBVal
		// 
		this->ColorBVal->AutoSize = true;
	 this->ColorBVal->Location = System::Drawing::Point(418, 310);
	 this->ColorBVal->Name = L"ColorBVal";
	 this->ColorBVal->Size = System::Drawing::Size(40, 20);
	 this->ColorBVal->TabIndex = 26;
	 this->ColorBVal->Text = L"1.00";
		// 
		// FrequencyVal
		// 
		this->FrequencyVal->AutoSize = true;
	 this->FrequencyVal->Location = System::Drawing::Point(430, 549);
	 this->FrequencyVal->Name = L"FrequencyVal";
	 this->FrequencyVal->Size = System::Drawing::Size(40, 20);
	 this->FrequencyVal->TabIndex = 27;
	 this->FrequencyVal->Text = L"4.00";
		// 
		// AmplitudeVal
		// 
		this->AmplitudeVal->AutoSize = true;
	 this->AmplitudeVal->Location = System::Drawing::Point(430, 610);
	 this->AmplitudeVal->Name = L"AmplitudeVal";
	 this->AmplitudeVal->Size = System::Drawing::Size(40, 20);
	 this->AmplitudeVal->TabIndex = 28;
	 this->AmplitudeVal->Text = L"0.01";
		// 
		// label5
		// 
		this->label5->AutoSize = true;
	 this->label5->Location = System::Drawing::Point(67, 562);
	 this->label5->Name = L"label5";
	 this->label5->Size = System::Drawing::Size(84, 20);
	 this->label5->TabIndex = 29;
	 this->label5->Text = L"Frequency";
	 // 
		// label6
		// 
		this->label6->AutoSize = true;
	 this->label6->Location = System::Drawing::Point(71, 609);
	 this->label6->Name = L"label6";
	 this->label6->Size = System::Drawing::Size(80, 20);
	 this->label6->TabIndex = 30;
	 this->label6->Text = L"Amplitude";
	 // 
		// ToolWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(888, 787);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->AmplitudeVal);
		this->Controls->Add(this->FrequencyVal);
		this->Controls->Add(this->ColorBVal);
		this->Controls->Add(this->ColorGVal);
		this->Controls->Add(this->ColorRVal);
		this->Controls->Add(this->SpecularStrengthVal);
		this->Controls->Add(this->TintBlueCheckbox);
		this->Controls->Add(this->WireframeRenderCheckbox);
		this->Controls->Add(this->Amplitude);
		this->Controls->Add(this->Frequency);
		this->Controls->Add(this->ScaleCheckbox);
		this->Controls->Add(this->RotateCheckbox);
		this->Controls->Add(this->TranslateCheckbox);
		this->Controls->Add(this->ResetTransformButton);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->SpecularColorB);
		this->Controls->Add(this->SpecularColorG);
		this->Controls->Add(this->SpecularColorR);
		this->Controls->Add(this->SpecularStrength);
		this->Controls->Add(this->SpecularStrengthLabel);
		this->Controls->Add(this->ResetLightPosButton);
		this->Controls->Add(this->SpaceSceneRadio);
		this->Controls->Add(this->WaterSceneRadio);
		this->Controls->Add(this->TransformRadio);
		this->Controls->Add(this->MoveLightRadio);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
		this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
		this->Name = L"ToolWindow";
		this->Text = L"ToolWindow";
		this->TopMost = true;
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrength))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorR))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorG))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorB))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Frequency))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Amplitude))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

		}
#pragma endregion
	//private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	//	RenderRedChannel = checkBoxRedChannel->Checked;
	//}
	//private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	//	RenderGreenChannel = checkBoxGreenChannel->Checked;
	//}
	//private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	//	RenderBlueChannel = checkBoxBlueChannel->Checked;
	//}
private: System::Void SpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
	this->SpecularStrengthVal->Text = System::Convert::ToString(this->SpecularStrength->Value);
}
private: System::Void SpecularColorR_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double val = (double)this->SpecularColorR->Value / 100.0;
	this->ColorRVal->Text = System::String::Format("{0:F2}", val);
}
private: System::Void SpecularColorG_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double val = (double)this->SpecularColorG->Value / 100.0;
	this->ColorGVal->Text = System::String::Format("{0:F2}", val);
}
private: System::Void SpecularColorB_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double val = (double)this->SpecularColorB->Value / 100.0;
	this->ColorBVal->Text = System::String::Format("{0:F2}", val);
}
private: System::Void ResetLightPosButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->m_resetLightPosPressed = true;
}
private: System::Void MoveLightRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void TransformRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void ResetTransformButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->m_resetTransformPressed = true;
}
private: System::Void TranslateCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void RotateCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void ScaleCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Frequency_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double val = (double)this->Frequency->Value / 100.0;
	this->FrequencyVal->Text = System::String::Format("{0:F2}", val);
}
private: System::Void WaterSceneRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Amplitude_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double val = (double)this->Amplitude->Value / 100.0;
	this->AmplitudeVal->Text = System::String::Format("{0:F2}", val);
}
private: System::Void WireframeRenderCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void TintBlueCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void SpaceSceneRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
