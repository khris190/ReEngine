#pragma once
#include "EfectSkillManager.h"

namespace Efect
{
	class SkillShadowSpear : public Skill
	{
	public:
		SkillShadowSpear(string _s):s(_s) {}
		
		virtual void onInit() override;
		virtual bool execute() override;
		virtual bool condition() override;

		string s;
	private:
		Game::Actor* createBullet();
	};

}