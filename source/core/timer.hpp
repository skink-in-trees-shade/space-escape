#ifndef CORE_TIMER_HPP
#define CORE_TIMER_HPP

#include <entityx/entityx.h>

class Timer final {
public:
	entityx::TimeDelta time();
};

#endif