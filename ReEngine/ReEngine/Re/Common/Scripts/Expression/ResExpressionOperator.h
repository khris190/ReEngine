#pragma once
#include <Re\Common\Scripts\Expression\ResExpression.h>

namespace Res
{
	class ExpressionOperatorPlus : public Expression
	{
	public:
		ExpressionOperatorPlus(shared_ptr<Expression> __left, shared_ptr<Expression> __right) : _left(__left), _right(__right){}
		float32 getValue() const;

		shared_ptr<Expression> _left, _right;
	};

	class ExpressionOperatorMinus : public Expression
	{
	public:
		ExpressionOperatorMinus(shared_ptr<Expression>__left, shared_ptr<Expression>__right) : _left(__left), _right(__right) {}
		float32 getValue() const;

		shared_ptr<Expression> _left, _right;
	};

	class ExpressionOperatorMultiplay : public Expression
	{
	public:
		ExpressionOperatorMultiplay(shared_ptr<Expression> __left, shared_ptr<Expression> __right) : _left(__left), _right(__right) {}
		float32 getValue() const;

		shared_ptr<Expression> _left, _right;
	};

	/// Warring! make sure right expression is never equal to 0 otherwise program will assert
	class ExpressionOperatorDivide : public Expression
	{
	public:
		ExpressionOperatorDivide(shared_ptr<Expression> __left, shared_ptr<Expression> __right) : _left(__left), _right(__right) {}
		float32 getValue() const;

		shared_ptr<Expression> _left, _right;
	};
}