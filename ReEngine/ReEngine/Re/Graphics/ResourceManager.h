#pragma once
#include <Re\Common\utility.h>
#include <string>

using namespace sf;
using namespace std;

using TsId = uint16;


/// class which contains game resources
///		- textures
///		- TODO (models, animations ect)
/// 
/// use res.deserialize("path"); at initialisation
/// then use tsInst[id] to get texture with id
class ResourceManager : public Res::ISerialisable
{
public:
	ResourceManager();

	/// list of loaded textures
	thor::ResourceHolder< Texture, TsId> textures;
	thor::ResourceHolder< Font, TsId> fonts;
	thor::ResourceHolder< sf::SoundBuffer, TsId> sounds;

	unique_ptr<Texture> createTexture(const std::string& path);

	/// set color which shoud be treated as transparent
	static inline void setClTransparent(const Color& s)
	{
		clTransparent = s;
	}
	/// get color which shoud be treated as transparent
	static inline const Color& getClTransparent()
	{
		return clTransparent;
	}

private:
	static Image im;
	static Color clTransparent;

protected:
	virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
	virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
};
extern ResourceManager res;

#define tsInst res.textures
#define fontInst res.fonts
