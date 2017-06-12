#include <Re\Common\Scripts\Expression\ResExpressionManager.h>
#include <Re\Common\Scripts\Expression\ResExpressionOperator.h>
#include <Re\Common\Scripts\Expression\ResExpressionValue.h>

namespace Res
{
	void ExpressionManager::nameExpression(const string & name, const shared_ptr<Expression>& expression)
	{
		_namedExpressions[name] = expression;
	}
	void ExpressionManager::nameExpression(const string & name, const string & code)
	{
		nameExpression(name, createExpression(code));
	}
	shared_ptr<Expression> ExpressionManager::createExpression(const string & code)
	{
		return createExpression(code.begin(), code.end() );
	}


#	define DOUBLE_OPERATOR(_Class1, _Class2, sign1, sign2) \
{ \
	size_t pos1 = string::npos;\
	size_t pos2 = string::npos;\
\
	size_t i = 0;\
	for (auto it : code) \
	{ \
		if (it == sign1) \
		{ \
			pos1 = i; \
			break; \
		} \
		if (it == sign2) \
		{ \
			pos2 = i; \
			break; \
		} \
\
		i++;\
	}\
	if (pos1 != std::string::npos) \
		return make_shared <_Class1 >( \
			createExpression(code.begin(), code.begin() + pos1), \
			createExpression(code.begin() + pos1 + 1, code.end()) \
		);\
	else if (pos2 != std::string::npos) \
		return make_shared < _Class2 >(\
			createExpression(code.begin(), code.begin() + pos2), \
			createExpression(code.begin() + pos2 + 1, code.end()) \
			); \
} 


	shared_ptr<Expression> ExpressionManager::createExpression(const std::string::const_iterator & itBegin, const std::string::const_iterator & itEnd)
	{
		
		string code(itBegin, itEnd);
		string whiteCode; ///< code without white signs, look at standard formating done by stream
		{
			stringstream stream(code); stream >> whiteCode;
		}

		DOUBLE_OPERATOR(ExpressionOperatorPlus, ExpressionOperatorMinus, '+', '-');
		DOUBLE_OPERATOR(ExpressionOperatorMultiplay, ExpressionOperatorDivide, '*', '\\');


		/// Function - Rand
		{
			static const string functionName = "rand";

			auto posName = code.find(functionName);
			if (posName != std::string::npos)
			{
				size_t oppeningBracket = std::string::npos;
				size_t comma = std::string::npos;
				size_t closingBracket = std::string::npos;


				oppeningBracket = code.find('(', posName);
				size_t oppeningCount = 1;
				size_t i = 0;
				for (auto it = code.begin() + oppeningBracket + 1; it != code.end() && oppeningCount > 0; ++it)
				{
					if ( *it == '(')
						oppeningCount++;
					else if (*it == ')')
					{
						oppeningCount--;
						if (oppeningCount == 0)
						{
							closingBracket = i;
						}
					}
					else if (oppeningCount == 1 && *it == ',')
					{
						comma = i;
					}

					++i;
				}

				if (oppeningCount > 0)
				{
					throw std::runtime_error("Error: there are more oppening brackets than closing");
				}
				else
				{
					return make_shared<ExpressionRandom>(
						createExpression(code.begin() + oppeningBracket+1, code.begin() + comma),
						createExpression(code.begin() + comma + 1, code.begin() + closingBracket)
						);
				}
			}
		}
		

		/// rand function
		/// TODO
		/*{
			static const string functionName = "Random";
			/// first word should be equal to name of function
			auto nameIt = code.rfind(functionName);
			if (nameIt != string::npos)
			{
				auto oppeningBracket = code.find('(', nameIt + functionName.size());

				//auto comma = code.find(',', oppeningBracket+1);
				auto comma = oppeningBracket + 1;
				for (; comma < code.size(); ++comma)
				{
					if (code[comma] == '(')
					{
						while (comma < code.size() && code[comma] == ')')
							comma++;
						continue;
					}
					if (code[comma] == ',')
						break;
				}

				auto endingBracket = code.find(')');

				if (nameIt != string::npos &&
					oppeningBracket != string::npos &&
					comma < code.size() &&
					endingBracket != string::npos)
				{
					string sFirstArg(code.begin() + oppeningBracket + 1, code.begin() + comma);
					string sSecondArg(code.begin() + comma + 1, code.begin() + endingBracket);

					return make_shared<ExpressionRandom>(createExpression(sFirstArg), createExpression(sSecondArg));
				}
			}
		}*/


		/// named value
		if (whiteCode[0] == '&')
		{
			whiteCode.erase(whiteCode.begin());
			auto &expr = _namedExpressions[whiteCode];
			if (expr)
				return expr;
			else goto error;
		}

		/// constant value
		{
			stringstream stream(code);
			float32 value; stream >> value;
			if (stream)
				return make_shared<ExpressionValue>(value);
		}

		error:
		throw std::runtime_error("Expression is not valid: \"" + code + "\"\n" );
		return shared_ptr<Expression>();
	}
#	undef DOUBLE_OPERATOR

	shared_ptr<Expression> ExpressionManager::getExpression(const string & name)
	{
		return _namedExpressions[name];
	}

	


	void ExpressionManager::serialiseF(std::ostream & file, DataScriptSaver & saver) const
	{

	}

	void ExpressionManager::deserialiseF(std::istream & file, DataScriptLoader & loader)
	{

	}
}