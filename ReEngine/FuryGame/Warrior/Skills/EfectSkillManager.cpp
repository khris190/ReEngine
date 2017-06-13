#include "EfectSkillManager.h"
#include <Re\Graphics\Graphics.h>

namespace Efect
{




	void Skill::onUpdate()
	{
		if (isExecuting())
		{
			if (execute())
				atExecution = false;
		}
	}

	void Skill::callForExecution()
	{
		atExecution = true;
		/// TODO pay cost
	}

	SkillManager::SkillManager()
	{
	}

	SkillManager::~SkillManager()
	{
		for(auto it: skills)
			delete it;
	}

	void SkillManager::onUpdate(sf::Time dt)
	{
		Efect::Base::onUpdate(dt);
		
		/// if at execution check if skill is still in run
		/// if not yet pressed wait check if key is pressed

		if (actualSkill)
		{
			/// wait until skill execution ends
			if (actualSkill->isExecuting() == false)
			{
				actualSkill = nullptr;
				isPressed = false;
			}else
				actualSkill->onUpdate();
		}
		else
		{
			if (isPressed)
			{
				if (actionMap.isActive(keyCode) == false)
				{
					isPressed = false;
					Region endRegion = getActualRegion();
					/// activate first skills that fits to pattern start-end
					for (auto& it : moves)
						if (it.start == startRegion && it.end == endRegion &&
							it.skill->condition() )
						{
							assert(it.skill);
							it.skill->callForExecution();
							actualSkill = it.skill;
							break;
						}
				}
			}
			else
			{
				if (actionMap.isActive(keyCode))
				{
					/// mark starting region
					startRegion = getActualRegion();
					isPressed = true;
				}
			}

		}

		/// Test of getActualRegion
		/*static Clock clock;
		if (clock.getElapsedTime() < sf::seconds(0.4))
		{
			//getActualRegion();
			cout << getActualRegion() << endl; 
			clock.restart();
		}*/
	}

	SkillManager::Region SkillManager::getActualRegion() const
	{
		/// prepare offset
		Vector2D mousePos = cam.mapPixelToCoords(sf::Mouse::getPosition(wnd));
		Vector2D mouseOffset =  mousePos - getOwner()->getPosition();
		float32 mouseOffsetLenghtSq = mouseOffset.getLenghtSq();
		
		/// which circle?
		unsigned int circleN = 0;
		for (auto r : radius)
			if ( mouseOffsetLenghtSq < r*r)
				break;
			else
				++circleN;
		/// which side
		Angle angle = mouseOffset.angle() - getOwner()->getRotation()+Degree(45);
		//if()
		Region dir = (angle < Angle::zero ? angle.asDegree() + 360 : angle.asDegree())/90;
		return circleN*4 +dir + 1;
	}

}