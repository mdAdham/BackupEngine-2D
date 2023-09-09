#pragma once
#ifdef CORESTUFF_EXPORTS
#define CORESTUFF_API __declspec(dllexport)
#else
#define CORESTUFF_API __declspec(dllimport)
#endif

#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>

namespace Utility::Core
{
	namespace FileSystem
	{
		//Output File Name Extension Can Be Custom
		CORESTUFF_API void ImgToDat(sf::Image image, std::string outputFileName);
		CORESTUFF_API sf::Image DatToImg(const char* datFilePath);
		CORESTUFF_API void AudioToDat(sf::SoundBuffer buffer, std::string outputFileName);
		CORESTUFF_API sf::SoundBuffer DatToAudio(const char* datFilePath);

		class CORESTUFF_API DataFolder
		{
		private:
			static const char encryptionKey_ = 0x3f;
			std::string _folderPath = std::string("BackupEngine_Data");
			bool valid = false;
			
			std::string encrypt(const std::string& input);
			std::string decrypt(const std::string& encrypted);

		public:
			DataFolder(const std::string folderPath);

			bool createSubFolder(const std::string& subfolderName);

			bool SaveToFile(const std::string& subFolder, const std::string& fileName, const std::string& content);
			bool SaveToFile(const std::string& filename, const std::string& content);
			std::string LoadFromFile(const std::string& subFolder, const std::string& fileName);
			std::string LoadFormFile(const std::string& filename);

			//Custom
			sf::Image LoadImageFromFile(const std::string& subFolder, const std::string& fileName);
			sf::Image LoadImageFromFile(const std::string& fileName);
		};
	}
}

//Example
/*
	Utility::Core::FileSystem::DataFolder gamedata("BackupEngine_Data");

	gamedata.createSubFolder("playerdata");
	gamedata.createSubFolder("leveldata");
	gamedata.SaveToFile("playerdata", "highscore.data", "1000");
	gamedata.SaveToFile("leveldata", "current_level.data", "3");

	gamedata.SaveToFile("settings.data", "sound=true");
	std::string settings = gamedata.LoadFormFile("settings.data");
	std::cout << "Settings: " << settings << std::endl;

	std::string highscore = gamedata.LoadFromFile("playerdata", "highscore.data");
	std::string currentLevel = gamedata.LoadFromFile("leveldata", "current_level.data");

	std::cout << "HighScore: " << highscore << std::endl;
	std::cout << "Current Level: " << currentLevel << std::endl;
*/