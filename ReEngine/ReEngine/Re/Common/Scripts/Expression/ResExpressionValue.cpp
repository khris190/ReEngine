#include <Re\Common\Scripts\Expression\ResExpressionValue.h>
#include <Re\Common\Math\Math.h>

namespace Res
{

	


	////// Expression value
	float32 ExpressionValue::getValue() const
	{
		return _value;
	}

	////// Expression Ptr
	float32 ExpressionPtr::getValue() const
	{
		assert(_value != nullptr);
		return *_value;
	}
	float32 ExpressionRandom::getValue() const
	{
		return randRange(_min->getValue(),_max->getValue());
	}
}