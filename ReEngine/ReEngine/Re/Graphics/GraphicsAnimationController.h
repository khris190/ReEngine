#pragma once
#include <Re\Graphics\GraphicsAnimationPart.h>

namespace Graphics
{

	class Model;

	class AnimationController : public Res::ISerialisable
	{
	public:
		AnimationController();
		AnimationController(const initializer_list<AnimationPart*>& parts);
		AnimationController(const char* path);

		void create(const initializer_list<AnimationPart*>& parts);

		/// update animation to play forward/backward
		/// if exceeds [stepMin, stepMax] range( inclusive) 
		/// then animation is aligned to the edge step value
		/// and stop played
		/// @return did the animation have exceed [stepMin,stepMax] range?
		bool updateInRange()
		{
			return updateInRange(speed);
		}
		/// version which uses speed taken as an argument
		/// instead speed holded in the class
		bool updateInRange(float32 speed);
		
		/// updates animation to play forward/backward
		/// if exceeds [stepMin, stepMax] range( inclusive) 
		/// speed changes its sign and animation is played in other direction
		/// @return did the animation have exceed [stepMin,stepMax] range?
		bool updateReturn()
		{
			return updateReturn(speed);
		}
		/// version which uses speed taken as an argument
		/// instead speed holded in the class
		/// @Note - speed value can change its sign in order of calling the function
		bool updateReturn(float32& speed);



		/// add new animation part 
		/// this should be created by new keyword because of future deletion
		void addPart(AnimationPart *newPart);

		/// attach the animation to model
		/// models holds pointners to animation parts that affects them
		/// you need to apply the animation onto model first
		/// make sure that model object will be deleted before animation 
		/// or use dissatach function to remove pointners 
		/// @Warring! slow operation. Don't use that on every frame
		/// @Warring! make sure model after revrite to vector will have enough elements
		///				that there is no part with modelId not pointing to model
		void attachToModel(Model& model);
		/// if the animation were attached to the model passed as an argument 
		/// deletes all pointners to animation parts of this animation from model
		/// @Warring slow operation. Don't use that on every frame
		/// @Warring! make sure model after revrite to vector will have enough elements
		///				that there is no part with modelId not pointing to model
		void disattachFromModel(Model& model);

		/// set step to the new value
		void reset(Step_t _new = 0);

		/// animation is only playable within the range of [stepMin, stepMax] inclusive
		Step_t stepMin{ 0 };
		Step_t stepMax{ 100.f };
	
		/// speed with the animation will be played
		/// if speed is positive the animation will be played forward
		/// otherwise backward
		Step_t speed{0};
	private:
		/// actual speed of animation
		Step_t step{0};

		
		/// animation parts holded
		list<unique_ptr<AnimationPart> > parts;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}