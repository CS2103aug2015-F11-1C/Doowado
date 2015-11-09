#pragma once


#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "msclr\marshal_cppstd.h"
#include "DisplayController.h"
#include "HelpGUI.h"

namespace DoowadoGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	DisplayController* Controller;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public MetroFramework::Forms::MetroForm {
	public:
		GUI(void)
		{
			InitializeComponent();

			//initializing program
			Controller = new DisplayController;
			Controller->initialiseProgram();
			updateGUI();

			this->FocusMe();
		}
		 
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ListView^  EventListDisplay;
	private: System::Windows::Forms::ColumnHeader^  EventID;
	private: System::Windows::Forms::ColumnHeader^  EventDesc;

	private: System::Windows::Forms::ListView^  TaskListDisplay;
	private: System::Windows::Forms::ColumnHeader^  TaskID;
	private: System::Windows::Forms::ColumnHeader^  TaskDescription;

	private: MetroFramework::Controls::MetroLabel^  EventListLabel;
	private: MetroFramework::Controls::MetroLabel^  TaskListLabel;

	private: MetroFramework::Controls::MetroTextBox^  inputBox;
	private: MetroFramework::Controls::MetroLabel^  feedbackLabel;
	private: MetroFramework::Controls::MetroTextBox^  FeedbackDisplay;

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  dateLabel;
	private: System::Windows::Forms::Label^  clockLabel;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->EventListDisplay = (gcnew System::Windows::Forms::ListView());
			this->EventID = (gcnew System::Windows::Forms::ColumnHeader());
			this->EventDesc = (gcnew System::Windows::Forms::ColumnHeader());
			this->TaskListDisplay = (gcnew System::Windows::Forms::ListView());
			this->TaskID = (gcnew System::Windows::Forms::ColumnHeader());
			this->TaskDescription = (gcnew System::Windows::Forms::ColumnHeader());
			this->EventListLabel = (gcnew MetroFramework::Controls::MetroLabel());
			this->TaskListLabel = (gcnew MetroFramework::Controls::MetroLabel());
			this->inputBox = (gcnew MetroFramework::Controls::MetroTextBox());
			this->feedbackLabel = (gcnew MetroFramework::Controls::MetroLabel());
			this->FeedbackDisplay = (gcnew MetroFramework::Controls::MetroTextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->dateLabel = (gcnew System::Windows::Forms::Label());
			this->clockLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// EventListDisplay
			// 
			this->EventListDisplay->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EventListDisplay->BackColor = System::Drawing::Color::White;
			this->EventListDisplay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->EventListDisplay->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->EventID, this->EventDesc });
			this->EventListDisplay->ForeColor = System::Drawing::Color::Black;
			this->EventListDisplay->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->EventListDisplay->Location = System::Drawing::Point(8, 80);
			this->EventListDisplay->Name = L"EventListDisplay";
			this->EventListDisplay->ShowItemToolTips = true;
			this->EventListDisplay->Size = System::Drawing::Size(317, 287);
			this->EventListDisplay->TabIndex = 0;
			this->EventListDisplay->UseCompatibleStateImageBehavior = false;
			this->EventListDisplay->View = System::Windows::Forms::View::Details;
			this->EventListDisplay->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::generalForm_KeyDown);
			this->EventListDisplay->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::generalForm_KeyPress);
			// 
			// EventID
			// 
			this->EventID->Text = L"ID.";
			this->EventID->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->EventID->Width = 35;
			// 
			// EventDesc
			// 
			this->EventDesc->Text = L"Event Description";
			this->EventDesc->Width = 265;
			// 
			// TaskListDisplay
			// 
			this->TaskListDisplay->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TaskListDisplay->BackColor = System::Drawing::Color::White;
			this->TaskListDisplay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->TaskListDisplay->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->TaskID, this->TaskDescription });
			this->TaskListDisplay->ForeColor = System::Drawing::Color::Black;
			this->TaskListDisplay->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->TaskListDisplay->Location = System::Drawing::Point(331, 80);
			this->TaskListDisplay->Name = L"TaskListDisplay";
			this->TaskListDisplay->ShowItemToolTips = true;
			this->TaskListDisplay->Size = System::Drawing::Size(317, 287);
			this->TaskListDisplay->TabIndex = 0;
			this->TaskListDisplay->UseCompatibleStateImageBehavior = false;
			this->TaskListDisplay->View = System::Windows::Forms::View::Details;
			this->TaskListDisplay->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::generalForm_KeyDown);
			this->TaskListDisplay->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::generalForm_KeyPress);
			// 
			// TaskID
			// 
			this->TaskID->Text = L"ID.";
			this->TaskID->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TaskID->Width = 35;
			// 
			// TaskDescription
			// 
			this->TaskDescription->Text = L"Task Description";
			this->TaskDescription->Width = 265;
			// 
			// EventListLabel
			// 
			this->EventListLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EventListLabel->AutoSize = true;
			this->EventListLabel->FontSize = MetroFramework::MetroLabelSize::Small;
			this->EventListLabel->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->EventListLabel->ForeColor = System::Drawing::Color::DarkTurquoise;
			this->EventListLabel->Location = System::Drawing::Point(8, 60);
			this->EventListLabel->Name = L"EventListLabel";
			this->EventListLabel->Size = System::Drawing::Size(124, 15);
			this->EventListLabel->Style = MetroFramework::MetroColorStyle::Silver;
			this->EventListLabel->TabIndex = 0;
			this->EventListLabel->Text = L"Your Events for Today:";
			this->EventListLabel->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->EventListLabel->UseCustomBackColor = true;
			this->EventListLabel->UseCustomForeColor = true;
			this->EventListLabel->UseStyleColors = true;
			// 
			// TaskListLabel
			// 
			this->TaskListLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TaskListLabel->AutoSize = true;
			this->TaskListLabel->FontSize = MetroFramework::MetroLabelSize::Small;
			this->TaskListLabel->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->TaskListLabel->ForeColor = System::Drawing::Color::DarkTurquoise;
			this->TaskListLabel->Location = System::Drawing::Point(330, 60);
			this->TaskListLabel->Name = L"TaskListLabel";
			this->TaskListLabel->Size = System::Drawing::Size(112, 15);
			this->TaskListLabel->Style = MetroFramework::MetroColorStyle::White;
			this->TaskListLabel->TabIndex = 0;
			this->TaskListLabel->Text = L"Your Pending Tasks:";
			this->TaskListLabel->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->TaskListLabel->UseCustomBackColor = true;
			this->TaskListLabel->UseCustomForeColor = true;
			this->TaskListLabel->UseStyleColors = true;
			// 
			// inputBox
			// 
			this->inputBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			// 
			// 
			// 
			this->inputBox->CustomButton->Image = nullptr;
			this->inputBox->CustomButton->Location = System::Drawing::Point(618, 1);
			this->inputBox->CustomButton->Name = L"";
			this->inputBox->CustomButton->Size = System::Drawing::Size(21, 21);
			this->inputBox->CustomButton->Style = MetroFramework::MetroColorStyle::Blue;
			this->inputBox->CustomButton->TabIndex = 1;
			this->inputBox->CustomButton->Theme = MetroFramework::MetroThemeStyle::Light;
			this->inputBox->CustomButton->UseSelectable = true;
			this->inputBox->CustomButton->Visible = false;
			this->inputBox->Lines = gcnew cli::array< System::String^  >(1) { L"Enter Command Here" };
			this->inputBox->Location = System::Drawing::Point(8, 418);
			this->inputBox->MaxLength = 32767;
			this->inputBox->Name = L"inputBox";
			this->inputBox->PasswordChar = '\0';
			this->inputBox->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->inputBox->SelectedText = L"";
			this->inputBox->SelectionLength = 0;
			this->inputBox->SelectionStart = 0;
			this->inputBox->Size = System::Drawing::Size(640, 23);
			this->inputBox->Style = MetroFramework::MetroColorStyle::Orange;
			this->inputBox->TabIndex = 1;
			this->inputBox->Text = L"Enter Command Here";
			this->inputBox->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->inputBox->UseSelectable = true;
			this->inputBox->UseStyleColors = true;
			this->inputBox->WaterMarkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(109)), static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(109)));
			this->inputBox->WaterMarkFont = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Pixel));
			this->inputBox->TextChanged += gcnew System::EventHandler(this, &GUI::inputBox_TextChanged);
			this->inputBox->DoubleClick += gcnew System::EventHandler(this, &GUI::inputBox_DoubleClick);
			this->inputBox->Enter += gcnew System::EventHandler(this, &GUI::inputBox_Enter);
			this->inputBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::inputBox_KeyDown);
			this->inputBox->Leave += gcnew System::EventHandler(this, &GUI::inputBox_Leave);
			// 
			// feedbackLabel
			// 
			this->feedbackLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->feedbackLabel->AutoSize = true;
			this->feedbackLabel->FontSize = MetroFramework::MetroLabelSize::Small;
			this->feedbackLabel->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->feedbackLabel->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->feedbackLabel->Location = System::Drawing::Point(8, 400);
			this->feedbackLabel->Name = L"feedbackLabel";
			this->feedbackLabel->Size = System::Drawing::Size(258, 15);
			this->feedbackLabel->Style = MetroFramework::MetroColorStyle::Orange;
			this->feedbackLabel->TabIndex = 19;
			this->feedbackLabel->Text = L"add / edit / show / search / delete / undo / save";
			this->feedbackLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->feedbackLabel->Theme = MetroFramework::MetroThemeStyle::Light;
			this->feedbackLabel->UseCustomBackColor = true;
			this->feedbackLabel->UseCustomForeColor = true;
			this->feedbackLabel->UseStyleColors = true;
			// 
			// FeedbackDisplay
			// 
			this->FeedbackDisplay->Anchor = System::Windows::Forms::AnchorStyles::None;
			// 
			// 
			// 
			this->FeedbackDisplay->CustomButton->Image = nullptr;
			this->FeedbackDisplay->CustomButton->Location = System::Drawing::Point(618, 2);
			this->FeedbackDisplay->CustomButton->Name = L"";
			this->FeedbackDisplay->CustomButton->Size = System::Drawing::Size(19, 19);
			this->FeedbackDisplay->CustomButton->Style = MetroFramework::MetroColorStyle::Blue;
			this->FeedbackDisplay->CustomButton->TabIndex = 1;
			this->FeedbackDisplay->CustomButton->Theme = MetroFramework::MetroThemeStyle::Light;
			this->FeedbackDisplay->CustomButton->UseSelectable = true;
			this->FeedbackDisplay->CustomButton->Visible = false;
			this->FeedbackDisplay->Lines = gcnew cli::array< System::String^  >(0);
			this->FeedbackDisplay->Location = System::Drawing::Point(8, 373);
			this->FeedbackDisplay->MaxLength = 32767;
			this->FeedbackDisplay->Multiline = true;
			this->FeedbackDisplay->Name = L"FeedbackDisplay";
			this->FeedbackDisplay->PasswordChar = '\0';
			this->FeedbackDisplay->ReadOnly = true;
			this->FeedbackDisplay->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->FeedbackDisplay->SelectedText = L"";
			this->FeedbackDisplay->SelectionLength = 0;
			this->FeedbackDisplay->SelectionStart = 0;
			this->FeedbackDisplay->Size = System::Drawing::Size(640, 24);
			this->FeedbackDisplay->Style = MetroFramework::MetroColorStyle::Orange;
			this->FeedbackDisplay->TabIndex = 2;
			this->FeedbackDisplay->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->FeedbackDisplay->UseCustomForeColor = true;
			this->FeedbackDisplay->UseSelectable = true;
			this->FeedbackDisplay->UseStyleColors = true;
			this->FeedbackDisplay->WaterMarkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(109)), static_cast<System::Int32>(static_cast<System::Byte>(109)));
			this->FeedbackDisplay->WaterMarkFont = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Pixel));
			this->FeedbackDisplay->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::generalForm_KeyDown);
			this->FeedbackDisplay->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::generalForm_KeyPress);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &GUI::timer1_Tick);
			// 
			// dateLabel
			// 
			this->dateLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->dateLabel->AutoSize = true;
			this->dateLabel->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateLabel->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->dateLabel->Location = System::Drawing::Point(328, 18);
			this->dateLabel->Name = L"dateLabel";
			this->dateLabel->Size = System::Drawing::Size(111, 19);
			this->dateLabel->TabIndex = 0;
			this->dateLabel->Text = L"Current Date";
			this->dateLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// clockLabel
			// 
			this->clockLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->clockLabel->AutoSize = true;
			this->clockLabel->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->clockLabel->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->clockLabel->Location = System::Drawing::Point(515, 17);
			this->clockLabel->Name = L"clockLabel";
			this->clockLabel->Size = System::Drawing::Size(113, 19);
			this->clockLabel->TabIndex = 0;
			this->clockLabel->Text = L"Current Time";
			this->clockLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BorderStyle = MetroFramework::Forms::MetroFormBorderStyle::FixedSingle;
			this->CausesValidation = false;
			this->ClientSize = System::Drawing::Size(657, 451);
			this->Controls->Add(this->clockLabel);
			this->Controls->Add(this->dateLabel);
			this->Controls->Add(this->FeedbackDisplay);
			this->Controls->Add(this->feedbackLabel);
			this->Controls->Add(this->inputBox);
			this->Controls->Add(this->TaskListLabel);
			this->Controls->Add(this->EventListLabel);
			this->Controls->Add(this->TaskListDisplay);
			this->Controls->Add(this->EventListDisplay);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->Name = L"GUI";
			this->Resizable = false;
			this->Style = MetroFramework::MetroColorStyle::Orange;
			this->Text = L"Doowado";
			this->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::generalForm_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::generalForm_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void inputBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyCode == Keys::Enter) {
					String^ inputText = inputBox->Text;

					if (inputText == "exit") {
						MetroFramework::MetroMessageBox::Show(this, "Good Bye!", "Exiting the Application:", MessageBoxButtons::OK, MessageBoxIcon::Information);
						Application::Exit();
					} else if (inputText == "help") {
						getHelpText();
					} else if (inputText == "save") {
						OpenFileDialog^ filebrowser = gcnew OpenFileDialog;
						filebrowser->InitialDirectory = "c:\\";
						filebrowser->Filter = "txt files (*.txt)|*.txt";
						filebrowser->FilterIndex = 1;
						filebrowser->Multiselect = false;

						if (filebrowser->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
							String^ filepath = filebrowser->FileName;

							Controller->processInput(inputText + " " + filepath);

							updateGUI();
						}
					} else {
						try {
							Controller->processInput(inputText);

							updateGUI();
						}
						catch (System::String^ errorMessage) {
							MetroFramework::MetroMessageBox::Show(this, errorMessage, "User Input Error:", MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
					}

					inputBox->Clear();

					this->ActiveControl = FeedbackDisplay;

					e->Handled = true;
			}
			
			// Minimize via Ctrl + W
			else if (e->KeyData == (Keys::Control | Keys::W)) {
				if (WindowState == FormWindowState::Normal) {
					WindowState = FormWindowState::Minimized;
				}
				else {
					WindowState = FormWindowState::Normal;
				}
			}
			
			// Exit via Ctrl + Q
			else if (e->KeyData == (Keys::Control | Keys::Q)) {
				MetroFramework::MetroMessageBox::Show(this, "Good Bye!", "Exiting the Application:", MessageBoxButtons::OK, MessageBoxIcon::Information);
				Application::Exit();
			}

			// Undo via Ctrl + Z
			else if (e->KeyData == (Keys::Control | Keys::Z)) {
				Controller->processInput("undo");
			}

			// Move Cursor left or right on arrow keys
			else if (e->KeyData == Keys::Right) {
				inputBox->SelectionStart += 1;
			}
			else if (e->KeyData == Keys::Left) {
				if (inputBox->SelectionStart != 0) {
					inputBox->SelectionStart -= 1;
				}
			}

			e->Handled = true;
		}

	private:
		
		System::Void generalForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			// Minimize via Ctrl + W
			if (e->KeyData == (Keys::Control | Keys::W)) {
				WindowState = FormWindowState::Minimized;
			}

			// Exit via Ctrl + Q
			else if (e->KeyData == (Keys::Control | Keys::Q)) {
				MetroFramework::MetroMessageBox::Show(this, "Good Bye!", "Exiting the Application:", MessageBoxButtons::OK, MessageBoxIcon::Information);
				Application::Exit();
			}
			// Undo via Ctrl + Z
			else if (e->KeyData == (Keys::Control | Keys::Z)) {
				Controller->processInput("undo");
			}
			else if (e->KeyData == Keys::Down | e->KeyData == Keys::Up) {

			}
			else {
				inputBox->Text = gcnew System::String(to_string(e->KeyValue).c_str());
				this->ActiveControl = inputBox;
			}
		}

		System::Void generalForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			if (e->KeyChar == (char)13 || e->KeyChar == (char)8) {
				this->ActiveControl = inputBox;
			}
			else {
				inputBox->Text = e->KeyChar.ToString();
				this->ActiveControl = inputBox;
				inputBox->SelectionStart = inputBox->Text->Length;
			}
		}

		System::Void updateGUI() {
			EventListDisplay->Items->Clear();
			getListofEvents();

			TaskListDisplay->Items->Clear();
			getListofTasks();

			getFeedbackList();
		}

		System::Void getListofEvents() {
			for (int i = 0; i < Controller->getEventListSize(); i++) {
				System::Windows::Forms::ListViewItem^ NewListViewItem;

				NewListViewItem = Controller->retrieveEventNameFromList(i);
				EventListDisplay->Items->Add(NewListViewItem);

				NewListViewItem = Controller->retrieveEventStartFromList(i);
				EventListDisplay->Items->Add(NewListViewItem);

				NewListViewItem = Controller->retrieveEventEndFromList(i);
				EventListDisplay->Items->Add(NewListViewItem);
			}
		}

		System::Void getListofTasks() {
			for (int i = 0; i < Controller->getTaskListSize(); i++) {
				System::Windows::Forms::ListViewItem^ NewListViewItem;

				NewListViewItem = Controller->retrieveTaskNameFromList(i);
				TaskListDisplay->Items->Add(NewListViewItem);

				NewListViewItem = Controller->retrieveTaskDueFromList(i);
				if (NewListViewItem->SubItems->Count > 1) {
					TaskListDisplay->Items->Add(NewListViewItem);
				}
			}
		}

		System::Void getFeedbackList() {
			FeedbackDisplay->AppendText("\r\n" + Controller->retrieveLastFeedback());

			EventListLabel->Text = Controller->retrieveEventListFeedback();
			TaskListLabel->Text = Controller->retrieveTaskListFeedback();
		}

		System::Void getHelpText() {
			HelpGUI^ HelpText = gcnew HelpGUI;
			HelpText->Show(this);
		}

	private:
		System::Void inputBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
			if (inputBox->Text == "add") {
				feedbackLabel->Text = "add <Entry name> from <start date/day> <start time> to <start date/day> <end time>";
			}
			else if (inputBox->Text == "edit") {
				feedbackLabel->Text = "edit <index> <new description> OR edit <index> start/end <new time>";
			}
			else if (inputBox->Text == "show") {
				feedbackLabel->Text = "show <date / day> OR show from <date> to <date>";
			}
			else if (inputBox->Text == "delete") {
				feedbackLabel->Text = "delete <index>";
			}
			else if (inputBox->Text == "undo") {
				feedbackLabel->Text = "undo";
			}
			else if (inputBox->Text == "search") {
				feedbackLabel->Text = "search <keyword 1> | <keyword 2> | <and so on>";
			}
			else if (inputBox->Text == "help") {
				feedbackLabel->Text = "help";
			}
			else if (inputBox->Text == "save") {
				feedbackLabel->Text = "save <new save directory>";
			}
			else if (inputBox->Text == ""){
				feedbackLabel->Text = "add / edit / show / search / delete / undo / save / help";
			}
		}

	private: 
		System::Void inputBox_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			this->inputBox->Clear();
		}

	private: 
		System::Void inputBox_Enter(System::Object^  sender, System::EventArgs^  e) {
			this->inputBox->Clear();
		}
	
	private: 
		System::Void inputBox_Leave(System::Object^  sender, System::EventArgs^  e) {
			this->inputBox->Text = "Enter Command Here";
		}

	private: 
		System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			DateTime^ current = DateTime::Now;
			String^ date = current->Date.ToString("dddd, dd/MM/yyy");
			String^ time = current->ToString("hh : mm tt");

			this->dateLabel->Text = date;
			this->clockLabel->Text = time;
		}
};
}