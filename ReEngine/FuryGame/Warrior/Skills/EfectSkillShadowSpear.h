#pragma once
#include "EfectSkillManager.h"

namespace Efect
{
	class SkillShadowSpear : public Skill
	{
	public:
		SkillShadowSpear(){}
		
		virtual void onInit() override;
		virtual bool execute() override;
		virtual bool condition() override;

	private:
		static Game::Actor* createBullet();
	};

}