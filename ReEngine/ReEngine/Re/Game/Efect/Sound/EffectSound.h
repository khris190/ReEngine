#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\ResourceManager.h>


namespace Efect
{
	class Sound : public Base
	{
	public:

		Sound(TsId soundId);

		virtual void onUpdate(sf::Time) override;

		Sound* setBuffer(sf::SoundBuffer& buff)
		{
			sound.setBuffer(buff);
			return this;
		}
		Sound* setVolume(float& vol)
		{
			sound.setVolume(vol);
			return this;
		}
	
		Sound*  setWhenPlaying(function<bool()> play)
		{
			whenPlay = play;
			return this;
		};
		void play()
		{
			sound.play();
		}

	public:
		sf::Sound sound;
		function<bool()>whenPlay;
	};
}