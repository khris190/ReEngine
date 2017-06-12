#pragma once
#include <Re\Common\Scripts\Expression\ResExpression.h>
#include <map>
#include <string>

namespace Res
{

	/// class which imitates a stack of variables putted by other modules
	/// to use within .res scripts
	/// some types of varriables can be createt within script
	/// in some places you can put whole matematical expression 
	/// using Res::Expression classes to connest in some way variables on "stack"
	class ExpressionManager : public ISerialisable
	{
	public:

		/// inserts new expression at name,
		void nameExpression(const string& name, const shared_ptr<Expression>& expression);
		void nameExpression(const string& name, const string& code);

		shared_ptr<Expression> createExpression(const string& code);

		shared_ptr<Expression> getExpression(const string& name);
			
	private:
		/// array of references to expressions
		std::map<std::string, shared_ptr<Expression> > _namedExpressions;

		shared_ptr<Expression> createExpression(
			const std::string::const_iterator& itBegin, 
			const std::string::const_iterator& itEnd);

	protected:
		/// at serialisation of stack you are alowded to create some vatiables at script-loading time
		/// most common usage is to create variables which will be used by many fields 
		/// for optimalisation purposes or slighty different result 
		/// ( i.e. Random variable to define how much shaded is color, 
		/// randed value is applied to r,g and b components of color at once )
		virtual void serialiseF(std::ostream& file, DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, DataScriptLoader& loader) override;
	};

}