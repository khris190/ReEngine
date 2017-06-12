#pragma once
#include <Re\Game\Efect\efects.h>


namespace Efect
{
	class SkillBase : public Base
	{
	public:

		
		/// TODO consider virtual or lambda

		/// tells whether input for skill was activated;
		function<bool()> isInputReady;
		/// tells whether skill can be activated
		virtual bool isReady() { return true; };
		
		/// returns value in range from 0 to 1 indicating how much time/ resource left to allow activate again
		virtual float getPercentReady() { return (float)isReady();  }

		virtual void executeSkill() = 0;

		void onUpdate(sf::Time dt) override;

		
		/// TODO cdr
		/// TODO Resource managment (energy ect)

		/// TODO hold icon of spell in hud
		///		create in game icon with usage indicator

	};

	/// test skill which makes champion walk faster
	class SkillJump : public SkillBase
	{
	public:

		
		float movementSpeedSprint;

		void onStart();
		void onUpdate(sf::Time dt) override;

	private:
		MovementAim *movement;

		float baseMovementSpeed;
	};


}