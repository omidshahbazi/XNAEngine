#pragma once


namespace MapEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			tsbNew_Click(nullptr, nullptr);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^  tsTools;
	private: System::Windows::Forms::Panel^  pGameArea;
	protected: 

	protected: 

	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel2;
	private: System::Windows::Forms::ToolStripTextBox^  tstbWidth;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripTextBox^  tstbHeight;
	private: System::Windows::Forms::ToolStripButton^  tsbNew;

	private: System::Windows::Forms::ToolStripButton^  tsbSave;


	private: System::Windows::Forms::ContextMenuStrip^  cmsTileType;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiBlankSpace;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiExitPoint;



	private: System::Windows::Forms::ToolStripMenuItem^  tsmiGem;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiFloatingPlatform;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiVariousEnemiesD;


	private: System::Windows::Forms::ToolStripMenuItem^  tsmiVariousEnemiesC;


	private: System::Windows::Forms::ToolStripMenuItem^  tsmiVariousEnemiesB;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiVariousEnemiesA;





	private: System::Windows::Forms::ToolStripMenuItem^  tsmiPlatformBlock;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiPassableBlock;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiStartPoint;


	private: System::Windows::Forms::ToolStripMenuItem^  tsmiImpassableBlock;
	private: System::Windows::Forms::ToolStripButton^  tsbLoad;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;






	private: System::ComponentModel::IContainer^  components;



























	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->tsTools = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->tstbWidth = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->tstbHeight = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->tsbNew = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tsbLoad = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsbSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->pGameArea = (gcnew System::Windows::Forms::Panel());
			this->cmsTileType = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiBlankSpace = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiImpassableBlock = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiStartPoint = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiPassableBlock = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiPlatformBlock = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiVariousEnemiesA = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiVariousEnemiesB = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiVariousEnemiesC = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiVariousEnemiesD = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiFloatingPlatform = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiGem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiExitPoint = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsTools->SuspendLayout();
			this->cmsTileType->SuspendLayout();
			this->SuspendLayout();
			// 
			// tsTools
			// 
			this->tsTools->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->toolStripLabel2, this->tstbWidth, 
				this->toolStripLabel1, this->tstbHeight, this->tsbNew, this->toolStripSeparator2, this->tsbLoad, this->tsbSave});
			this->tsTools->Location = System::Drawing::Point(0, 0);
			this->tsTools->Name = L"tsTools";
			this->tsTools->Size = System::Drawing::Size(640, 25);
			this->tsTools->TabIndex = 0;
			this->tsTools->Text = L"toolStrip1";
			// 
			// toolStripLabel2
			// 
			this->toolStripLabel2->Name = L"toolStripLabel2";
			this->toolStripLabel2->Size = System::Drawing::Size(45, 22);
			this->toolStripLabel2->Text = L"Width :";
			// 
			// tstbWidth
			// 
			this->tstbWidth->Name = L"tstbWidth";
			this->tstbWidth->Size = System::Drawing::Size(30, 25);
			this->tstbWidth->Text = L"10";
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(49, 22);
			this->toolStripLabel1->Text = L"Height :";
			// 
			// tstbHeight
			// 
			this->tstbHeight->Name = L"tstbHeight";
			this->tstbHeight->Size = System::Drawing::Size(30, 25);
			this->tstbHeight->Text = L"10";
			// 
			// tsbNew
			// 
			this->tsbNew->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbNew->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbNew.Image")));
			this->tsbNew->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbNew->Name = L"tsbNew";
			this->tsbNew->Size = System::Drawing::Size(35, 22);
			this->tsbNew->Text = L"New";
			this->tsbNew->Click += gcnew System::EventHandler(this, &Form1::tsbNew_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// tsbLoad
			// 
			this->tsbLoad->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbLoad->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbLoad.Image")));
			this->tsbLoad->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbLoad->Name = L"tsbLoad";
			this->tsbLoad->Size = System::Drawing::Size(37, 22);
			this->tsbLoad->Text = L"Load";
			this->tsbLoad->Click += gcnew System::EventHandler(this, &Form1::tsbLoad_Click);
			// 
			// tsbSave
			// 
			this->tsbSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbSave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsbSave.Image")));
			this->tsbSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbSave->Name = L"tsbSave";
			this->tsbSave->Size = System::Drawing::Size(35, 22);
			this->tsbSave->Text = L"Save";
			this->tsbSave->Click += gcnew System::EventHandler(this, &Form1::tsbSave_Click);
			// 
			// pGameArea
			// 
			this->pGameArea->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pGameArea->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pGameArea->Location = System::Drawing::Point(0, 25);
			this->pGameArea->Name = L"pGameArea";
			this->pGameArea->Size = System::Drawing::Size(640, 455);
			this->pGameArea->TabIndex = 1;
			// 
			// cmsTileType
			// 
			this->cmsTileType->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->tsmiBlankSpace, 
				this->tsmiImpassableBlock, this->tsmiStartPoint, this->tsmiPassableBlock, this->tsmiPlatformBlock, this->tsmiVariousEnemiesA, 
				this->tsmiVariousEnemiesB, this->tsmiVariousEnemiesC, this->tsmiVariousEnemiesD, this->tsmiFloatingPlatform, this->tsmiGem, this->tsmiExitPoint});
			this->cmsTileType->Name = L"cmsTileType";
			this->cmsTileType->Size = System::Drawing::Size(172, 268);
			// 
			// tsmiBlankSpace
			// 
			this->tsmiBlankSpace->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiBlankSpace->Name = L"tsmiBlankSpace";
			this->tsmiBlankSpace->Size = System::Drawing::Size(171, 22);
			this->tsmiBlankSpace->Tag = L".";
			this->tsmiBlankSpace->Text = L"Blank space";
			this->tsmiBlankSpace->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiImpassableBlock
			// 
			this->tsmiImpassableBlock->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiImpassableBlock.Image")));
			this->tsmiImpassableBlock->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiImpassableBlock->Name = L"tsmiImpassableBlock";
			this->tsmiImpassableBlock->Size = System::Drawing::Size(171, 22);
			this->tsmiImpassableBlock->Tag = L"#";
			this->tsmiImpassableBlock->Text = L"Impassable block";
			this->tsmiImpassableBlock->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiStartPoint
			// 
			this->tsmiStartPoint->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiStartPoint.Image")));
			this->tsmiStartPoint->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiStartPoint->Name = L"tsmiStartPoint";
			this->tsmiStartPoint->Size = System::Drawing::Size(171, 22);
			this->tsmiStartPoint->Tag = L"1";
			this->tsmiStartPoint->Text = L"Start point";
			this->tsmiStartPoint->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiPassableBlock
			// 
			this->tsmiPassableBlock->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiPassableBlock.Image")));
			this->tsmiPassableBlock->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiPassableBlock->Name = L"tsmiPassableBlock";
			this->tsmiPassableBlock->Size = System::Drawing::Size(171, 22);
			this->tsmiPassableBlock->Tag = L":";
			this->tsmiPassableBlock->Text = L"Passable block";
			this->tsmiPassableBlock->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiPlatformBlock
			// 
			this->tsmiPlatformBlock->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiPlatformBlock.Image")));
			this->tsmiPlatformBlock->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiPlatformBlock->Name = L"tsmiPlatformBlock";
			this->tsmiPlatformBlock->Size = System::Drawing::Size(171, 22);
			this->tsmiPlatformBlock->Tag = L"~";
			this->tsmiPlatformBlock->Text = L"Platform block";
			this->tsmiPlatformBlock->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiVariousEnemiesA
			// 
			this->tsmiVariousEnemiesA->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiVariousEnemiesA.Image")));
			this->tsmiVariousEnemiesA->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiVariousEnemiesA->Name = L"tsmiVariousEnemiesA";
			this->tsmiVariousEnemiesA->Size = System::Drawing::Size(171, 22);
			this->tsmiVariousEnemiesA->Tag = L"A";
			this->tsmiVariousEnemiesA->Text = L"Various enemies A";
			this->tsmiVariousEnemiesA->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiVariousEnemiesB
			// 
			this->tsmiVariousEnemiesB->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiVariousEnemiesB.Image")));
			this->tsmiVariousEnemiesB->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiVariousEnemiesB->Name = L"tsmiVariousEnemiesB";
			this->tsmiVariousEnemiesB->Size = System::Drawing::Size(171, 22);
			this->tsmiVariousEnemiesB->Tag = L"B";
			this->tsmiVariousEnemiesB->Text = L"Various enemies B";
			this->tsmiVariousEnemiesB->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiVariousEnemiesC
			// 
			this->tsmiVariousEnemiesC->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiVariousEnemiesC.Image")));
			this->tsmiVariousEnemiesC->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiVariousEnemiesC->Name = L"tsmiVariousEnemiesC";
			this->tsmiVariousEnemiesC->Size = System::Drawing::Size(171, 22);
			this->tsmiVariousEnemiesC->Tag = L"C";
			this->tsmiVariousEnemiesC->Text = L"Various enemies C";
			this->tsmiVariousEnemiesC->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiVariousEnemiesD
			// 
			this->tsmiVariousEnemiesD->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiVariousEnemiesD.Image")));
			this->tsmiVariousEnemiesD->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiVariousEnemiesD->Name = L"tsmiVariousEnemiesD";
			this->tsmiVariousEnemiesD->Size = System::Drawing::Size(171, 22);
			this->tsmiVariousEnemiesD->Tag = L"D";
			this->tsmiVariousEnemiesD->Text = L"Various enemies D";
			this->tsmiVariousEnemiesD->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiFloatingPlatform
			// 
			this->tsmiFloatingPlatform->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiFloatingPlatform.Image")));
			this->tsmiFloatingPlatform->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiFloatingPlatform->Name = L"tsmiFloatingPlatform";
			this->tsmiFloatingPlatform->Size = System::Drawing::Size(171, 22);
			this->tsmiFloatingPlatform->Tag = L"-";
			this->tsmiFloatingPlatform->Text = L"Floating platform";
			this->tsmiFloatingPlatform->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiGem
			// 
			this->tsmiGem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiGem.Image")));
			this->tsmiGem->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiGem->Name = L"tsmiGem";
			this->tsmiGem->Size = System::Drawing::Size(171, 22);
			this->tsmiGem->Tag = L"G";
			this->tsmiGem->Text = L"Gem";
			this->tsmiGem->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// tsmiExitPoint
			// 
			this->tsmiExitPoint->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiExitPoint.Image")));
			this->tsmiExitPoint->ImageTransparentColor = System::Drawing::Color::Black;
			this->tsmiExitPoint->Name = L"tsmiExitPoint";
			this->tsmiExitPoint->Size = System::Drawing::Size(171, 22);
			this->tsmiExitPoint->Tag = L"X";
			this->tsmiExitPoint->Text = L"Exit point";
			this->tsmiExitPoint->Click += gcnew System::EventHandler(this, &Form1::tsmiTileType_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(640, 480);
			this->Controls->Add(this->pGameArea);
			this->Controls->Add(this->tsTools);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Tag = L"Aban - Map Editor {0}";
			this->Text = L"Aban - Map Editor {0}";
			this->tsTools->ResumeLayout(false);
			this->tsTools->PerformLayout();
			this->cmsTileType->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		static const int TILE_WIDTH = 64;
		static const int TILE_HEIGHT = 48;
		static int width = 10, height = 10;
		
		Button^ lastClickedButton;

private: Button^ AddTile(int X, int Y)
		 {
			 Button ^tile = gcnew Button();

			 tile->Width = TILE_WIDTH;
			 tile->Height = TILE_HEIGHT;

			 tile->Location = Point(X * TILE_WIDTH, Y * TILE_HEIGHT);

			 tile->BackgroundImageLayout = ImageLayout::Zoom;

			 tile->Tag = ".";

			 tile->Click += gcnew EventHandler(this, &Form1::tile_Click);
			 tile->MouseUp += gcnew MouseEventHandler(this, &Form1::tile_MouseUp);

			 pGameArea->Controls->Add(tile);

			 return tile;
		 }

private: System::Void tsbNew_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 pGameArea->Controls->Clear();

			 if (String::IsNullOrEmpty(tstbWidth->Text))
			 {
				 tstbWidth->Text = width.ToString();
			 }
			 else
			 {
				 try
				 {
					 width = Convert::ToInt32(tstbWidth->Text);
				 }
				 catch(...)
				 {
					tstbWidth->Text = width.ToString();
				 }
			 }

			 if (String::IsNullOrEmpty(tstbHeight->Text))
			 {
				 tstbHeight->Text = height.ToString();
			 }
			 else
			 {
				 try
				 {
					 height = Convert::ToInt32(tstbHeight->Text);
				 }
				 catch(...)
				 {
					tstbHeight->Text = height.ToString();
				 }
			 }

			 System::Drawing::Size size = System::Drawing::Size(TILE_WIDTH * width, TILE_HEIGHT * height);

			 Text = String::Format(Tag->ToString(), size);

			 Width = size.Width + 9;

			 Height = size.Height + 31 + tsTools->Height;

			 for (int y = 0; y < height; y++)
			 {
				 for (int x = 0; x < width; x++)
				 {
					 AddTile(x, y);
				 }
			 }
		 }

private: System::Void tile_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			lastClickedButton = (Button^)sender;

			cmsTileType->Show(MousePosition);
		}
private: System::Void tile_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Middle)
			{
				((Button^)sender)->BackgroundImage = lastClickedButton->BackgroundImage;
				((Button^)sender)->Tag = lastClickedButton->Tag;

				lastClickedButton = (Button^)sender;
			}
			else if (e->Button == System::Windows::Forms::MouseButtons::Right)
			{
				((Button^)sender)->BackgroundImage = nullptr;
				((Button^)sender)->Tag = ".";
			}
		}
private: System::Void tsmiTileType_Click(System::Object^  sender, System::EventArgs^  e) {
			 lastClickedButton->BackgroundImage = ((ToolStripMenuItem^)sender)->Image;
			 lastClickedButton->Tag = ((ToolStripMenuItem^)sender)->Tag;
		 }
private: System::Void tsbSave_Click(System::Object^  sender, System::EventArgs^  e) {

			 String ^st = "";

			 for (int y = 0; y < height; y++)
			 {
				 for (int x = 0; x < width; x++)
				 {
					 Control ^c = pGameArea->Controls[(y * width) + x];

					 st += c->Tag->ToString();
				 }

				 st += Environment::NewLine;
			 }

			 st = st->Substring(0, st->Length - 1);

			 SaveFileDialog^ sfd = gcnew SaveFileDialog();

			 sfd->Filter = "Map files|*.map";

			 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::Cancel)
				 File::WriteAllText(sfd->FileName, st);
		 }
private: System::Void tsbLoad_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 OpenFileDialog^ ofd = gcnew OpenFileDialog();

			 ofd->Filter = "Map files|*.map";

			 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::Cancel)
			 {
				 cli::array<String^>^ lines = File::ReadAllLines(ofd->FileName);

				 tstbWidth->Text = lines[0]->Length.ToString();
				 tstbHeight->Text = lines->Length.ToString();

				 tsbNew_Click(gcnew Object(), gcnew EventArgs());
				 
				 pGameArea->Controls->Clear();

				 for (int y = 0; y < height; y++)
				 {
					 for (int x = 0; x < width; x++)
					 {
						 AddTile(x, y);

						 int index = (y * width) + x;

						 pGameArea->Controls[index]->Tag = lines[y][x].ToString();
						 
						 for (int i = 0; i < cmsTileType->Items->Count; i++)
						 {
							 if (cmsTileType->Items[i]->Tag->ToString() == lines[y][x].ToString())
							 {
								 pGameArea->Controls[index]->BackgroundImage = cmsTileType->Items[i]->Image;

								 break;
							 }
						 }
					 }
				 }
			 }
		 }
};
}

