#pragma once
#include "components/simple_scene.h"

namespace m1
{
	class ITimeDependant
	{
	public:
		virtual void changeInTime(float time) = 0;
	};
}
