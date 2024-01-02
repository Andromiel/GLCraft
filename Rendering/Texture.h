#pragma once
#include <GL/glew.h>

#include <iostream>

#include <../Rendering/res/stb_image.h>

#define TEXTURE_WIDTH 16
#define TEXTURE_HEIGHT 16

static int GetFirstPixelOfTexture(int texture_id, int nChannels) {
	int texturerow = texture_id / TEXTURE_WIDTH;
	int firstpixelofrow = texturerow * TEXTURE_WIDTH * TEXTURE_WIDTH * TEXTURE_HEIGHT * nChannels;
	int firstpixel = firstpixelofrow + (texture_id % TEXTURE_WIDTH) * TEXTURE_WIDTH * nChannels;
	return firstpixel;
}

class Texture {
private:
	unsigned int _texture;
public:
	Texture(std::string source);
	~Texture();

	void Bind();
};

Texture::Texture(std::string source) {

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(3);
	unsigned char* data = stbi_load(source.c_str(), &width, &height, &nrChannels, 0);

	

	std::cout << GetFirstPixelOfTexture(17, nrChannels) << std::endl;
	

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {

}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, _texture);
}

class Texture2DArray {
private:
	unsigned int _texture;
public:
	Texture2DArray(std::string source);
	~Texture2DArray();

	void Bind();
};





Texture2DArray::Texture2DArray(std::string atlas) {

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, depth, nrChannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(atlas.c_str(), &width, &height, &nrChannels, 0);
	unsigned char* sorted_data = stbi_load(atlas.c_str(), &width, &height, &nrChannels, 0);

	depth = TEXTURE_WIDTH * TEXTURE_HEIGHT;

	for (int i = 0; i < (width / TEXTURE_WIDTH) * (height / TEXTURE_HEIGHT); i++) {
		int firstpixel_indata = GetFirstPixelOfTexture(i, nrChannels);
		int firstpixel_insorteddata = width * nrChannels * i;

		for (int j = 0; j < TEXTURE_WIDTH * TEXTURE_HEIGHT * nrChannels; j++) {
			sorted_data[firstpixel_insorteddata + j] = data[firstpixel_indata + j % (TEXTURE_WIDTH * nrChannels) + (j / (TEXTURE_WIDTH * nrChannels)) * width * nrChannels];
		}
	}


	if (data)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width / TEXTURE_WIDTH, height / TEXTURE_HEIGHT, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, sorted_data);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	stbi_image_free(sorted_data);

}

Texture2DArray::~Texture2DArray() {

}

void Texture2DArray::Bind() {
	glBindTexture(GL_TEXTURE_2D, _texture);
}

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

std::vector<std::string> ListAllFilesWithExtension(std::string directory, std::string extension) {
	std::vector<std::string> list;
	for (const auto& entry : fs::directory_iterator(directory)) {
		std::string file = entry.path().string();
		if(file.find(extension) != std::string::npos)
			list.push_back(file);
	}
	return list;
}