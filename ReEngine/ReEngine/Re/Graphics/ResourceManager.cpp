#include <Re\Graphics\ResourceManager.h>

Image ResourceManager::im;
Color ResourceManager::clTransparent(255, 255, 255);

ResourceManager res;

ResourceManager::ResourceManager()
{
}

unique_ptr<Texture> ResourceManager::createTexture(const std::string & path)
{
	unique_ptr<Texture> ptr( new Texture);
	if (im.loadFromFile(path))
	{
		im.createMaskFromColor(clTransparent);
		ptr->loadFromImage(im);
		return ptr;
	}
	else
	{
		std::cout << "Failed to open the texture: \"" << path << "\"" << std::endl;
		return nullptr;
	}
}

void ResourceManager::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
{
	// does not save resources
}
void ResourceManager::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
{
	try
	{
		// heder line
		std::string prepathGraphics = loader.loadRaw("prepathGraphics", "");
		std::string prepathFont = loader.loadRaw("prepathFont", "");
		std::string prepathSound = loader.loadRaw("prepathSound", "");

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string type = loader.load<string>("type", "UNKNOWN");
			if (type == "texture")
			{
				std::string path = prepathGraphics + loader.loadRaw("path", "non_written_path_error");
				TsId name = loader.load("id", 0u);

				if (name == 0u)
					std::cerr << "error: Resource >> textures >> id = non_named\n"
					"\tPath = " << path << "\n";
				else
				{// add Texture to container

					textures.acquire(name, thor::ResourceLoader<Texture>(
						[=]()
					{
						return std::unique_ptr<Texture>(createTexture(path));
					}, path));

				}
			}
			else if (type == "sound")
			{
				std::string path = prepathSound + loader.loadRaw("path", "non_written_error");
				TsId name = loader.load("id", 0u);

				if (name == 0u)
					std::cerr << "error: Resource >> sounds >> id = non_named\n"
					"\tPath = " << path << "\n";
				else
				{//add Sound to container
					sounds.acquire(name, thor::ResourceLoader<SoundBuffer>(
						[=]()
					{
						auto sound = std::make_unique<SoundBuffer>();
						sound->loadFromFile(path);
						return sound;
					}, path));
				}
			} 
			else if (type == "font")
			{
				std::string path = prepathFont + loader.loadRaw("path", "non_written_path_error");
				TsId name = loader.load("id", 0u);

				if (name == 0u)
					std::cerr << "error: Resource >> Font >> id = non_named\n"
					"\tPath = " << path << "\n";
				else
				{// add Texture to container
					fonts.acquire(name, thor::ResourceLoader<Font>(
						[=]()
					{
						auto font = std::make_unique<Font>();
						font->loadFromFile(path);
						return font;
					}, path));

				}
			}
			else
			{
				cerr << "Error: Undefined type of resource: \"" << type << "\"\n";
			}
		}

	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
}
