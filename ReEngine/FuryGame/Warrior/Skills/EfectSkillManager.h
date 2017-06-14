#pragma once
#include <Re\Game\Efect\efects.h>

namespace Efect
{
	class SkillManager;

	class Skill
	{
	public:
		virtual ~Skill() = default;
		void onUpdate();
		
		/// called when owner is set up
		virtual void onInit() {};

		/// do a real spell execution
		/// return true when spell is finnished
		virtual bool execute() = 0;
		/// return whether or not skill can be activated
		virtual bool condition() { return true; };

		void callForExecution();
		__forceinline bool isExecuting() { return atExecution; }

		/// cost in soul energy payed afret usage;
		float32 cost;

		Game::Actor* getOwner() { return owner; }
		Game::Actor* getOwner() const  { return owner; }


	private:
		/// tells whether the spell is at run;
		bool atExecution{false};
		Game::Actor* owner;

		friend SkillManager;
	};

	/// skill manager for player usage
	/// TODO ai bassed one
	class SkillManager : public Base
	{
	public:
		typedef unsigned short Region;

			/// struct for representing moves plyer can do
			/// there is choosen first move that fits to actual start-end pattern
			/// and then execution of skill lasts until next is choosen
			struct SkillMove
			{
				Region start;
				Region end;
				Skill* skill;
			};

			SkillManager();
			~SkillManager();


		/// setters
		SkillManager* setRadius(initializer_list<float> s)
		{
			int i = 0;
			for (auto r : s)
			{
				radius[i] = r;
				++i;
			}
			return this;
		}
		SkillManager* setKeyCode(const string& s)
		{
			keyCode = s;
			return this;
		}
		SkillManager* addSkill(Skill* s, const initializer_list<pair<Region,Region>>& moveList)
		{
			s->owner = getOwner();
			s->onInit();

			skills.push_back(s);
			for (auto it : moveList)
			{
				SkillMove move;
				move.skill = s;
				move.start = it.first;
				move.end = it.second;
				moves.push_back(move);
			}
			return this;
		}

		virtual void onUpdate(sf::Time dt) override;



		/// returns region onto which actually mouse points
		Region getActualRegion() const;


		/// list of learned moves
		vector<SkillMove> moves;
		/// radiuses of skill circles. 
		/// what is above last circle is added to size+1 circle
		array<float32, 3> radius;
		string keyCode{"fire1"};

	private:
		vector<Skill*> skills;
		Region startRegion;
		bool isPressed {false};
		Skill* actualSkill{ nullptr };
	};

}