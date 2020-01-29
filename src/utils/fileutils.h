#pragma once
#include <string>

namespace ferrari
{
	class FileUtils
	{
	public:
		static std::string read_file(const char *filepath)
		{
			FILE *file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
	};

	class WAVFileUtils
	{
	public:

		struct WAV_Info
		{
			char chunkID[4];
			unsigned long chunkSize;
			char format[4];
			char subchunk1ID[4];
			unsigned long subChunk1Size;
			unsigned short audioFormat, numChannels;
			unsigned long sampleRate, byteRate;
			unsigned short blockAlign, bitsPerSample;

			char subChunk2ID[4]; //"data" = 0x61746164
			unsigned long subChunk2Size;  //Chunk data bytes

			unsigned char* bufferData;
		};
		
		static WAV_Info read_WAV_file(const char* filepath)
		{			
			FILE *file = fopen(filepath, "rb");
			if (!file)
				std::cout << "Error: Cannot access file contents" << std::endl;

			WAV_Info header;
			fread(&header, 44, 1, file);

			if (!strcmp(header.chunkID, "RIFF"))
				std::cout << "Error" << std::endl;
			if (!strcmp(header.format, "WAVE"))
				std::cout << "Error: Invalid format" << std::endl;
			if (!strcmp(header.format, "data"))
				std::cout << "Error: Invalid data" << std::endl;

			std::cout << "File Type: " << header.chunkID[0] << header.chunkID[1] << header.chunkID[2] << header.chunkID[3] << std::endl;
			std::cout << "File Size: " << header.chunkSize << std::endl;
			std::cout << "WAV Marker: " << header.format[0] << header.format[1] << header.format[2] << header.format[3] << std::endl;
			std::cout << "Format Name: " << header.subchunk1ID[0] << header.subchunk1ID[1] << header.subchunk1ID[2] << header.subchunk1ID[3] << std::endl;
			std::cout << "Format Length: " << header.subChunk1Size << std::endl;
			std::cout << "Format Type: " << header.audioFormat << std::endl;
			std::cout << "Number of Channels: " << header.numChannels << std::endl;
			std::cout << "Sample Rate: " << header.sampleRate << std::endl;
			std::cout << "Rate * Bits/Sample * Channels / 8: " << header.byteRate << std::endl;
			std::cout << "Bits per Sample * Channels / 8.1: " << header.blockAlign << std::endl;
			std::cout << "Bits per Sample: " << header.bitsPerSample << std::endl;
			std::cout << header.subChunk2ID[0] << header.subChunk2ID[1] << header.subChunk2ID[2] << header.subChunk2ID[3] << "	" << header.subChunk2Size << std::endl;
			
			int size = header.subChunk2Size;
			unsigned char* data = new unsigned char[size];
			fread(data, sizeof(char), size, file);

			header.bufferData = data;
			delete[] data;

			return header;
		}
	};
}