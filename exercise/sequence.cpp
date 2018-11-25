#include "pch.h"
#include "sequence.h"

sequence::sequence(std::string file) : file(file)
{
	std::ifstream fs(file);
	
	int type;
	while(fs >> type)
	{
		blocks.push_back(create_block(type, fs));
	}
}

sequence::~sequence()
{
	std::ofstream fs(file);
	for (auto it = blocks.begin(); it != blocks.end(); ++it)
	{
		fs << **it;
	}
}

bool sequence::add(int type, const std::string& parameters)
{
	bool result = false;

	std::stringstream ss(parameters);
	std::unique_ptr<block> block = create_block(type, ss);
	if (block != nullptr)
	{
		blocks.push_back(std::move(block));
		result = true;
	}

	return result;
}

bool sequence::check_index(size_t index) const
{
	return 0 <= index && index <= blocks.size() - 1;
}

bool sequence::remove(size_t index)
{
	bool result = false;

	if (check_index(index))
	{
		auto it = blocks.begin();
		std::advance(it, index);
		blocks.erase(it);
		result = true;
	}

	return result;
}

bool sequence::front(size_t index)
{
	bool result = false;

	if (check_index(index))
	{
		auto it = blocks.begin();
		std::advance(it, index);
		std::unique_ptr<block> block = std::move(*it);
		blocks.erase(it);
		blocks.insert(blocks.begin(), std::move(block));
		result = true;
	}

	return result;
}

bool sequence::print(std::ostream& os) const
{
	for (auto it = blocks.begin(); it != blocks.end(); ++it)
	{
		os << **it;
	}

	return true;
}

double sequence::eval_impl(double input) const
{
	double result = input;
	for (auto it = blocks.begin(); it != blocks.end(); ++it)
	{
		(*it)->input(result);
		result = (*it)->output();
	}
	return result;
}

bool sequence::eval(double value, std::ostream& os) const
{
	bool result = false;

	if (blocks.size() > 0)
	{
		os << eval_impl(value);
		result = true;
	}
	
	return result;
}

bool sequence::eval(std::istream& is, std::ostream& os) const
{
	bool result = false;

	if (blocks.size() > 0)
	{
		double value;
		while (is >> value) 
		{
			os << eval_impl(value) << " ";
		}
		result = true;
	}

	return result;
}