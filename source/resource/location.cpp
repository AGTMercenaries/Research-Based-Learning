#include "resource/location.h"

ResourceType::ResourceType(std::string _type, std::string _ext) : type(_type), ext(_ext) {}
Path ResourceType::operator()(std::string location) const {
	 return Path("resource\\" + type + "\\" + location + "." + ext);
}

Path::Path(std::string s) : path(s) {}

const ResourceType VertexShader("shaders", "vs");
const ResourceType FragmentShader("shaders", "fs");
const ResourceType TextureImage("textures", "png");
const ResourceType AnvilFile("map", "mca");