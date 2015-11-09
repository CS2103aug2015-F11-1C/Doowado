#pragma once

namespace DoowadoGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HelpGUI
	/// </summary>
	public ref class HelpGUI : public MetroFramework::Forms::MetroForm
	{
	public:
		HelpGUI(void)
		{
			InitializeComponent();

			this->richTextBox1->LoadFile("HelpText.rtf", RichTextBoxStreamType::RichText);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HelpGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(12, 63);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(607, 281);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"Help Text Here";
			this->richTextBox1->WordWrap = false;
			this->richTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &HelpGUI::richTextBox1_KeyDown);
			// 
			// HelpGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(633, 357);
			this->Controls->Add(this->richTextBox1);
			this->MaximizeBox = false;
			this->Name = L"HelpGUI";
			this->Padding = System::Windows::Forms::Padding(0, 60, 0, 0);
			this->Resizable = false;
			this->Text = L"Doowado Help";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void richTextBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyData == Keys::Down | e->KeyData == Keys::Up | e->KeyData == Keys::Left | e->KeyData == Keys::Right) {

		}
		else{
			this->Close();
		}
	}
	};
}
