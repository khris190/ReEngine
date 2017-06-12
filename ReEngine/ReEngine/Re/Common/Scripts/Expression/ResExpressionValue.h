#pragma once
#include <Re\Common\Scripts\Expression\ResExpression.h>

namespace Res
{
	/// expression to hold simple constant value
	class ExpressionValue : public Expression
	{
	public:
		/// explicit constructor for creation of expression
		explicit ExpressionValue(float32 __value = 0): _value(__value) {};

		virtual float32 getValue() const override;

		/// holded value
		float32 _value;
	};

	/// expression to hold values passed by other modules which changes at runtime
	class ExpressionPtr : public Expression
	{
	public:
		/// explicit constructor for creation of expression
		explicit ExpressionPtr(float32* __value = nullptr) : _value(__value) {};
		virtual float32 getValue() const override;

		/// this dont have to be created by new keyword
		/// so you should keep care of its deletion
		/// also make sure as long as it's used keep he value in memory
		float32* _value;
	};

	/// expression which rands its value within range [_min,_max]
	class ExpressionRandom : public Expression
	{
	public:
		ExpressionRandom(shared_ptr<Expression> __min, shared_ptr<Expression> __max) : _min(__min), _max(__max) {}
		virtual float32 getValue() const;

		shared_ptr<Expression> _min, _max;
	};
}