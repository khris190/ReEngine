#pragma once
#include <Re\Common\Settings.h>
#include <Re\Common\Scripts\ResISerialisable.h>

namespace Res
{
	/// Expression ( representation of some value) in Re script files
	class Expression
	{
	public:
		virtual float32 getValue() const = 0;
	};

}