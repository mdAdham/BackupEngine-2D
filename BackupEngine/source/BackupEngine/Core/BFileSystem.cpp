#include "bcpch.h"
#include "BFileSystem.h"

void Utility::Core::FileSystem::ImgToDat(sf::Image img, std::string outputFileName)
{
	std::fstream data_file(outputFileName, std::ios::out | std::ios::binary);

	if (data_file.is_open())
	{
		const sf::Vector2u imageSize = img.getSize();
		data_file.write(reinterpret_cast<const char*>(&imageSize.x), sizeof(imageSize.x));
		data_file.write(reinterpret_cast<const char*>(&imageSize.y), sizeof(imageSize.y));
		data_file.write(reinterpret_cast<const char*>(img.getPixelsPtr()), imageSize.x * imageSize.y * 4);
		data_file.close();
	}
}

sf::Image Utility::Core::FileSystem::DatToImg(const char* datFilePath)
{
	std::fstream data_file(datFilePath, std::ios::in | std::ios::binary);
	if (data_file.is_open())
	{
		sf::Vector2u imageSize;
		data_file.read(reinterpret_cast<char*>(&imageSize.x), sizeof(imageSize.x));
		data_file.read(reinterpret_cast<char*>(&imageSize.y), sizeof(imageSize.y));

		std::vector<sf::Uint8> pixelData(imageSize.x * imageSize.y * 4);

		data_file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

		sf::Image image;
		image.create(imageSize.x, imageSize.y, pixelData.data());

		data_file.close();
		return image;
	}
	return sf::Image();
}

void Utility::Core::FileSystem::AudioToDat(sf::SoundBuffer soundBuffer, std::string outputFileName)
{
	//Audio To Dat

	const sf::Int16* samples = soundBuffer.getSamples();
	const sf::Uint64 sampleCount = soundBuffer.getSampleCount();
	const unsigned int channelCount = soundBuffer.getChannelCount();
	const unsigned int sampleRate = soundBuffer.getSampleRate();

	std::fstream data_file(outputFileName, std::ios::binary | std::ios::out);
	if (data_file.is_open())
	{
		data_file.write(reinterpret_cast<const char*>(&sampleRate), sizeof(sampleRate));
		data_file.write(reinterpret_cast<const char*>(&channelCount), sizeof(channelCount));
		data_file.write(reinterpret_cast<const char*>(samples), sampleCount * sizeof(sf::Int16));

		data_file.close();
	}
}

sf::SoundBuffer Utility::Core::FileSystem::DatToAudio(const char* datFilePath)
{
	std::fstream data_file(datFilePath, std::ios::in | std::ios::binary);
	if (data_file.is_open())
	{
		unsigned int sampleRate;
		unsigned int channelCount;
		data_file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
		data_file.read(reinterpret_cast<char*>(&channelCount), sizeof(channelCount));

		data_file.seekg(0, std::ios::end);
		std::streampos length = data_file.tellg() - (std::streampos)sizeof(sampleRate) - sizeof(channelCount);
		data_file.seekg(sizeof(sampleRate) + sizeof(channelCount));

		std::vector<sf::Int16> audioData(length / sizeof(sf::Int16));
		data_file.read(reinterpret_cast<char*>(audioData.data()), length);

		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromSamples(audioData.data(), audioData.size(), channelCount, sampleRate);

		data_file.close();
		return soundBuffer;
	}
	return sf::SoundBuffer();
}

namespace Utility::Core::FileSystem
{
	DataFolder::DataFolder(const std::string folderpath)
		:_folderPath(folderpath)
	{
		if (!std::filesystem::exists(folderpath))
		{
			valid = false;
			MessageBeep(1);
			MessageBox(NULL, TEXT("Could not open GameDataFolder"), TEXT("Error"), MB_OK);
			exit(0);
			return;
		}
		else valid = true;
	}

	bool DataFolder::createSubFolder(const std::string& subfolderName)
	{
		if (valid)
		{
			std::string fullPath = _folderPath + "/" + subfolderName;
			return _mkdir(fullPath.c_str()) == 0;
		}
		return false;
	}

	bool DataFolder::SaveToFile(const std::string& subFolder, const std::string& fileName, const std::string& content)
	{
		if(valid)
		{
			std::string fullPath = _folderPath + "/" + subFolder + "/" + fileName;
			std::string encryptedContent = encrypt(content);
			std::ofstream file(fullPath, std::ios::binary);
			if (file.is_open())
			{
				file.write(encryptedContent.c_str(), encryptedContent.size());
				file.close();
				return true;
			}
			return false;
		}
		return false;
	}

	bool DataFolder::SaveToFile(const std::string& filename, const std::string& content)
	{
		if(valid)
		{
			std::string fullpath = _folderPath + "/" + filename;
			std::string encyptedContent = encrypt(content);
			std::ofstream file(fullpath, std::ios::binary);

			if (file.is_open())
			{
				file.write(encyptedContent.c_str(), encyptedContent.size());
				file.close();
				return true;
			}
			return false;
		}
		return false;
	}

	std::string DataFolder::LoadFromFile(const std::string& subFolder, const std::string& fileName)
	{
		if(valid)
		{
			std::string fullPath = _folderPath + "/" + subFolder + "/" + fileName;
			std::ifstream file(fullPath, std::ios::binary);
			std::stringstream buffer;
			if (file.is_open())
			{
				buffer << file.rdbuf();
				file.close();
			}
			std::string encryptedContent = buffer.str();
			return decrypt(encryptedContent);
		}
		return "";
	}

	std::string DataFolder::LoadFormFile(const std::string& filename)
	{
		if(valid)
		{
			std::string fullPath = _folderPath + "/" + filename;
			std::ifstream file(fullPath, std::ios::binary);
			std::stringstream buffer;

			if (file.is_open())
			{
				buffer << file.rdbuf();
				file.close();
			}

			std::string encryptedContent = buffer.str();
			return decrypt(encryptedContent);
		}
		return "";
	}
	std::string DataFolder::encrypt(const std::string& input)
	{
		std::string encrypted = input;
		for (char& c : encrypted)
		{
			c ^= encryptionKey_;
		}
		return encrypted;
	}

	std::string DataFolder::decrypt(const std::string& encrypted)
	{
		std::string decrypted = encrypted;
		for (char& c : decrypted)
		{
			c ^= encryptionKey_;
		}
		return decrypted;
	}

	sf::Image DataFolder::LoadImageFromFile(const std::string& subFolder, const std::string& fileName)
	{
		if (valid)
		{
			std::string fullPath = this->_folderPath + "/" + subFolder + "/" + fileName;
			return DatToImg(fullPath.c_str());
		}
		return sf::Image();
	}

	sf::Image DataFolder::LoadImageFromFile(const std::string& fileName)
	{
		if (valid)
		{
			std::string fullPath = this->_folderPath + "/" + fileName;
			return DatToImg(fullPath.c_str());
		}
		return sf::Image();
	}
}
//Two Hundred line completed