#include "FreeType.h"
#include "Pi.h"

#include <memory>
#include <functional>
#include <filesystem>
#include <bitset>
#include <numeric>
#include <msclr/marshal_cppstd.h>

#define generic GenericFromFreeTypeLibrary
#include <ft2build.h>
#include FT_FREETYPE_H
#undef generic

using namespace Demo;
using namespace msclr::interop;
using namespace System;

void FreeType::Init()
{
	std::unique_ptr<FT_Library, std::function<void(FT_Library*)>> library(new FT_Library(), [](auto* p) { FT_Done_FreeType(*p); });

	FT_Init_FreeType(library.get());
	fonts = gcnew Dictionary<String^, List<String^>^>();
	files = gcnew Dictionary<Tuple<String^, String^>^, String^>();

	for (const auto& file : std::filesystem::directory_iterator{"C:\\Windows\\Fonts"})
	{
		std::unique_ptr<FT_Face, std::function<void(FT_Face*)>> face(new FT_Face(), [](auto* p) { FT_Done_Face(*p); });

		if (FT_New_Face(*library.get(), file.path().string().c_str(), 0, face.get()) == FT_Err_Ok)
		{
			auto family = marshal_as<String^>((*face)->family_name);
			auto style = marshal_as<String^>((*face)->style_name);

			if (!fonts->ContainsKey(family))
			{
				fonts->Add(family, gcnew List<String^>());
			}

			if (!fonts[family]->Contains(style))
			{
				fonts[family]->Add(style);
				files->Add(gcnew Tuple<String^, String^>(family, style), marshal_as<String^>(file.path().string()));
			}
		}
	}
}

Dictionary<String^, List<String^>^>^ FreeType::Fonts::get()
{
	if (!fonts)
	{
		Init();
	}

	return fonts;
}


String^ FreeType::RenderChar(String^ family, String^ style, int height, String^ c)
{
	auto charcode = c[0];
	auto key = gcnew Tuple<String^, String^>(family, style);
	String^ value;

	if (files->TryGetValue(key, value))
	{
		auto file = marshal_as<std::string>(value);
		std::unique_ptr<FT_Library, std::function<void(FT_Library*)>> library(new FT_Library(), [](auto* p) { FT_Done_FreeType(*p); });
		std::unique_ptr<FT_Face, std::function<void(FT_Face*)>> face(new FT_Face(), [](auto* p) { FT_Done_Face(*p); });

		FT_Init_FreeType(library.get());

		if (FT_New_Face(*library.get(), file.c_str(), 0, face.get()) == FT_Err_Ok)
		{
			FT_Set_Pixel_Sizes(*face.get(), height, height);

			if (auto glyphIndex = FT_Get_Char_Index(*face.get(), charcode))
			{
				size_t bitsOn = 0;
				std::string result;

				FT_Load_Glyph(*face.get(), glyphIndex, FT_LOAD_DEFAULT);
				FT_GlyphSlot slot = (*face)->glyph;
				FT_Render_Glyph((*face)->glyph, FT_RENDER_MODE_MONO);

				for (unsigned int y = 0; y < slot->bitmap.rows; y++)
				{
					const auto* src = &slot->bitmap.buffer[y * slot->bitmap.pitch];

					for (int x = 0; x < slot->bitmap.pitch; x++)
					{
						std::bitset<8> bits (src[x]);
						bitsOn += bits.count();
					}
				}

				auto pi = marshal_as<std::string>(Pi::Generate((int)bitsOn));

				for (unsigned int y = 0; y < slot->bitmap.rows; y++)
				{
					const auto* src = &slot->bitmap.buffer[y * slot->bitmap.pitch];

					for (int x = 0; x < slot->bitmap.pitch; x++)
					{
						std::bitset<8> bits(src[x]);

						for (int i = 7; i >= 0; i--)
						{
							if (bits[i])
							{
								result += *pi.begin();
								pi.erase(0, 1);
							}
							else
							{
								result += ' ';
							}
						}
					}

					result += "\n";
				}

				return marshal_as<String^>(result);
			}
		}
	}

	return family + " does not contain character: " + (gcnew Int32(charcode))->ToString();
}
