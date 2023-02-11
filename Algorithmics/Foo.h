#pragma once
#include <cstdio>

#include <iosfwd>


#define USE_FOO_MOVE 1

class    Foo
{
public:

	Foo()
	{
		m_id = s_count++;
		std::printf("Create Foo_%d\n", m_id);
	}


	Foo(int id) :
		m_id(id)
	{
		std::printf("Create Foo_%d\n", m_id);
	}


	Foo(const Foo& foo)
	{
		m_id = foo.m_id + 1;
		std::printf("Create Foo_%d copy of Foo_%d\n", m_id, foo.m_id);
	}

	Foo& operator=(const Foo& foo)
	{
		std::printf("Copying Foo_%d into Foo_%d\n", foo.m_id, m_id);
		m_id = foo.m_id;
		return *this;
	}

#if USE_FOO_MOVE
	Foo& operator=(Foo&& foo) noexcept
	{
		std::printf("Moving Foo_%d (now set to -1) into Foo_%d (now set to %d)\n", foo.m_id, m_id, foo.m_id);
		m_id = foo.m_id;
		foo.m_id = -1;

		return *this;
	}

	Foo(Foo&& foo) noexcept
	{
		m_id = foo.m_id;
		std::printf("Create Foo_%d move copy of Foo_%d (now set to -1)\n", m_id, foo.m_id);
		foo.m_id = -1;
	}
#endif

	virtual ~Foo()
	{
		std::printf("Destroy Foo_%d\n\n", m_id);
	}

	static void ResetCount()
	{
		s_count = 0;
	}


	static int	Count()
	{
		return s_count;
	}


	int	MyCount() const
	{
		return m_id;
	}


	bool operator==(const Foo& foo) const
	{
		return (m_id == foo.m_id);
	}



private:
	int    m_id = -1;

	static int s_count;
};

std::ostream& operator<<(std::ostream& ostr, const Foo& foo);