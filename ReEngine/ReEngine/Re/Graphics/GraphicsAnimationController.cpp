#include <Re\Graphics\GraphicsAnimationController.h>
#include <Re\Graphics\GraphicsModel.h>

namespace Graphics
{

	AnimationController::AnimationController()
	{
	}

	AnimationController::AnimationController(const initializer_list<AnimationPart*>& parts)
	{
		create(parts);
	}

	AnimationController::AnimationController(const char * path)
	{
		deserialise(path);
	}

	void AnimationController::create(const initializer_list<AnimationPart*>& parts)
	{
		for (auto &it : parts)
			addPart(it);
	}

	bool AnimationController::updateInRange(float32 speed)
	{
		// tells wheter or not the animation has exceed the limit
		bool exceed = false;

		// adjust the speed so it wont exceed the interval
		if (speed > 0)
		{
			if (speed + step > stepMax)
			{
				speed = stepMax - step;
				exceed = true;
			}
		}
		else if (speed + step < stepMin)
		{
			speed = stepMin - step;
			exceed = true;
		}

		step += speed;
		return exceed;
	}

	bool AnimationController::updateReturn(float32 & speed)
	{
		bool exceed = updateInRange(speed);
		if (exceed)
			speed *= -1;
		return exceed;
	}

	void AnimationController::addPart(AnimationPart * newPart)
	{
		newPart->setStepPtr(&step);
		parts.push_back(unique_ptr<AnimationPart>(newPart));
	}

	void AnimationController::attachToModel(Model & model)
	{
		vector<Model*> revritedVector;
		model.rewriteToVector(revritedVector);

		for (auto&it : parts)
		{
			assert(it->modelId < revritedVector.size());
			revritedVector[it->modelId]->addPart( &(*it) );
		}
	}

	void AnimationController::disattachFromModel(Model & model)
	{
		vector<Model*> revritedVector;
		model.rewriteToVector(revritedVector);
		
		for (auto&it : parts)
		{
			assert(it->modelId < revritedVector.size());
			revritedVector[it->modelId]->removePart(&(*it));
		}
	}

	void AnimationController::reset(Step_t _new)
	{
		step = _new;
	}

	void AnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_ENGINE
		/// animation serialization available only in editor
		/// TODO
#endif // RE_ENGINE
	}

	void AnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		stepMin = loader.load("stepMin", 0.f);
		stepMax = loader.load("stepMax", 100.f);
		step = loader.load("step", stepMin);
		speed = loader.load("speed", 1.f);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			auto ptr = new AnimationPart;
			ptr->deserialise(file, loader);
			addPart(ptr);
		}
	}

}