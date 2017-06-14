#include <Re\Game\Efect\Sound\EffectSound.h>

namespace Efect
{
	Sound::Sound(TsId soundId)
	{
		sound.setBuffer(soundInst[soundId]);
	}

	void Sound::onUpdate(sf::Time)
	{
		if (whenPlay())sound.play();

		//else sound.stop();
	}
}