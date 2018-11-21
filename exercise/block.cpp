#include "pch.h"
#include "block.h"

class block_type
{
public:
	static const int identity = 1;
	static const int addition = 2;
	static const int multiplication = 3;
	static const int power = 4;
	static const int limit = 5;
	static const int condition = 6;
};

block::~block()
{
}

void block::input(double input)
{
	in = input;
}

std::ostream& operator<<(std::ostream& os, const block& block)
{
	block.print(os);
	return os;
}

void identity::print(std::ostream& os) const
{
	os << block_type::identity << " ";
}

double identity::output () const
{
	return in;
}

void addition::print(std::ostream& os) const
{
	os << block_type::addition << " " << constant << " ";
}

double addition::output() const
{
	return in + constant;
}

void multiplication::print(std::ostream& os) const
{
	os << block_type::multiplication << " " << constant << " ";
}

double multiplication::output() const
{
	return in * constant;
}

void power::print(std::ostream& os) const
{
	os << block_type::power << " " << constant << " ";
}

double power::output() const
{
	return std::pow(in, constant);
}

void limit::print(std::ostream& os) const
{
	os << block_type::limit << " " << minimum << " " << maximum << " ";
}

double limit::output() const
{
	return std::clamp(in, minimum, maximum);
}

void condition::print(std::ostream& os) const
{
	os << block_type::condition << " " << constant << " ";
}

double condition::output() const
{
	if (in > constant)
	{
		return 1;
	}
	else if (in < constant)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

std::unique_ptr<block> create_block(int type, std::istream& stream)
{
	switch (type)
	{
	case block_type::identity:
	{
		return std::make_unique<identity>();
	}
	case block_type::addition:
	{
		double constant;
		if (stream >> constant)
		{
			return std::make_unique<addition>(constant);
		}
	}
	case block_type::multiplication:
	{
		double constant;
		if (stream >> constant)
		{
			return std::make_unique<multiplication>(constant);
		}
	}
	case block_type::power:
	{
		double constant;
		if (stream >> constant)
		{
			return std::make_unique<power>(constant);
		}
	}
	case block_type::limit:
	{
		double min, max;
		if (stream >> min >> max)
		{
			return std::make_unique<limit>(min, max);
		}
	}
	case block_type::condition:
	{
		double constant;
		if (stream >> constant)
		{
			return std::make_unique<condition>(constant);
		}
	}
	default:
		return nullptr;
	}
}
