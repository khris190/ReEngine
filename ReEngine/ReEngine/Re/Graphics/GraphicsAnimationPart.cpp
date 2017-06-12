#include <Re\Graphics\GraphicsAnimationPart.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{
	AnimationPart::AnimationPart()
	{
	}
	AnimationPart::AnimationPart(size_t _modelId, const ModelDef& modelDef, Step_t _stepMin, Step_t _stepMax)
		: ModelDef(modelDef), stepMin(_stepMin), stepMax(_stepMax), modelId(_modelId)
	{
	}
	AnimationPart::AnimationPart(char * path)
	{
		deserialise(path);
	}
	void AnimationPart::countOffset(ModelDef & out) const
	{
		assert(step != nullptr);

		/*out.move(position.x*getActualStep(), position.y*getActualStep() );
		out.setScale(out.getScale() + scale* getActualStep());
		out.rotate(rotation*getActualStep());
		out.setOrigin(out.getOrigin() + origin *getActualStep());*/
		out.color += color *getStep();
		out.pos += pos *getStep();
		out.scale += scale*getStep();
		out.rotAround += rotAround * getStep();
		out.rot += rot * getStep();
		out.posNoRot += posNoRot * getStep();
	}
	bool AnimationPart::isWithinRange() const
	{
		return getStep() >= stepMin && getStep() <= stepMax;
	}

	Step_t AnimationPart::getActualStep() const
	{
		return clamp(getStep(), stepMin, stepMax);//-stepMin;
	}

	void AnimationPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		ModelDef::serialiseF(file, saver);
		/// serialization of animation available only in editor
#	ifdef RE_EDITOR
		saver.save("model", modelId);
		saver.save("stepMin", stepMin);
		saver.save("stepMax", stepMax);
#	endif // RE_EDITOR
	}
	void AnimationPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		//ModelDef::deserialiseF(file, loader);
		
		pos.x = loader.load("posX", ModelDef::zero.pos.x);
		pos.y = loader.load("posY", ModelDef::zero.pos.y);

		posNoRot.x = loader.load("posNoRotX", ModelDef::zero.posNoRot.x);
		posNoRot.y = loader.load("posNoRotY", ModelDef::zero.posNoRot.y);

		scale.x = loader.load("scaleX", ModelDef::zero.scale.x);
		scale.y = loader.load("scaleY", ModelDef::zero.scale.y);

		rot = Degree(loader.load("rot", ModelDef::zero.rot.asDegree()));
		rotAround = Degree(loader.load("rotAround", ModelDef::zero.rotAround.asDegree()));

		color.r = loader.load("clR", ModelDef::zero.color.r);
		color.g = loader.load("clG", ModelDef::zero.color.g);
		color.b = loader.load("clB", ModelDef::zero.color.b);
		color.a = loader.load("clA", ModelDef::zero.color.a);
		
		modelId = loader.load("model", (size_t)0);

		stepMin = loader.load("stepMin", -numeric_limits<Step_t>::max() );
		stepMax = loader.load("stepMax", numeric_limits<Step_t>::max());
	}
}