#include <Re\Common\Scripts\Expression\ResExpressionOperator.h>

namespace Res
{


	float32 ExpressionOperatorPlus::getValue() const
	{
		return _left->getValue() + _right->getValue();
	}

	float32 ExpressionOperatorMinus::getValue() const
	{
		return _left->getValue() - _right->getValue();
	}

	float32 ExpressionOperatorMultiplay::getValue() const
	{
		return _left->getValue() * _right->getValue();
	}

	float32 ExpressionOperatorDivide::getValue() const
	{
		float32 right = _right->getValue();
		assert(right != 0);
		return _left->getValue() / right;
	}

}