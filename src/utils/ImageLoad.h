#pragma once
#include <FreeImage\FreeImage.h>
#include <string>

namespace ferrari {
	
	static BYTE* load_image(const char* filepath, GLsizei* width, GLsizei* height, unsigned int* bits)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		//pointer to the image, once loaded
		FIBITMAP *dib = nullptr;

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filepath, 0);

		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filepath);

		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return nullptr;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filepath);

		//if the image failed to load, return failure
		if (!dib)
			return nullptr;

		//retrieve the image data
		BYTE* pixels = FreeImage_GetBits(dib);
		//get the image width and height
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bits = FreeImage_GetBPP(dib);

		int size = *width * *height * (*bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);

		FreeImage_Unload(dib);

		//return success
		return result;
	}
}