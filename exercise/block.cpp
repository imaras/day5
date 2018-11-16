#include "pch.h"
#include "block.h"

block::~block()
{
}

void block::input(double input)
{
	in = input;
}

double identity::output () const
{
	return in;
}

double addition::output() const
{
	return in + constant;
}

double multiplication::output() const
{
	return in * constant;
}

double power::output() const
{
	return std::pow(in, constant);
}

double limit::output() const
{
	return std::clamp(in, min, max);
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

std::unique_ptr<block> create_block(int type, const std::vector<double>& block_parameters)
{
	switch (type)
	{
	case 1:
		return std::make_unique<identity>();
	case 2:
		return std::make_unique<addition>(block_parameters[0]);
	case 3:
		return std::make_unique<multiplication>(block_parameters[0]);
	case 4:
		return std::make_unique<power>(block_parameters[0]);
	case 5:
		return std::make_unique<limit>(block_parameters[0], block_parameters[1]);
	case 6:
		return std::make_unique<condition>(block_parameters[0]);
	default:
		return nullptr;
	}
}
