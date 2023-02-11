#include "pch.h"
#include "Foo.h"
#include <ostream>



int    Foo::s_count = 0;


std::ostream& operator<<(std::ostream& ostr, const Foo& foo)
{
	ostr << foo.MyCount();
	return ostr;
}