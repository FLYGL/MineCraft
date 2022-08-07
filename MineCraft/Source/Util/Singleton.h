#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
class Singleton : public NonCopyable, public NonMovable
{

};