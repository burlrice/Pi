#pragma once

namespace Demo
{
	using namespace System::Collections::Generic;

	public ref class FreeType
	{
	public:
		static property Dictionary<System::String^, List<System::String^>^>^ Fonts { Dictionary<System::String^, List<System::String^>^>^ get(); };

		static System::String^ RenderChar(System::String^ family, System::String^ style, int height, System::String^ c);

	private:
		static void Init();

		static Dictionary<System::String^, List<System::String^>^>^ fonts;
		static Dictionary<System::Tuple<System::String^, System::String^>^, System::String^>^ files;
	};
}

