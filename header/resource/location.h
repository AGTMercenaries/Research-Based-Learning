#pragma once
#include <string>

using Location = std::string;
struct Path {
	std::string path;

	explicit Path(std::string s);
};
struct ResourceType {
private:
	const std::string type, ext;

public:
	ResourceType(std::string _type, std::string _ext);
	
	Path operator()(std::string location) const;
};

extern const ResourceType VertexShader; 
extern const ResourceType FragmentShader;
extern const ResourceType TextureImage;
extern const ResourceType AnvilFile;