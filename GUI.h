#pragma once
#include "HackingFunctions.cpp"
#include "Defines.h"

namespace address
{

}

namespace pattern
{

}

namespace pointer
{

}

namespace settings
{

}

namespace assemblycode
{

}

void HackThread()
{
	return;
}

namespace BlackHat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->SuspendLayout();
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->ClientSize = System::Drawing::Size(354, 294);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"GUI";
			this->Text = L"Black Hat";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &GUI::GUI_UnLoad);
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void GUI_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void GUI_UnLoad(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	}
	};
}
