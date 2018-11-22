#pragma once

#include "block.h"

class sequence
{
private:
	std::string file;
	std::vector <std::unique_ptr<block>> blocks;
	bool check_index(size_t index) const;
	double eval_impl(double) const;
public:
	sequence(std::string file = "local.txt");
	~sequence();
	bool add(int type, const std::string& parameters);
	bool remove(size_t index);
	bool front(size_t index);
	bool print() const;
	bool eval(double value) const;
	bool eval(const std::string& input, const std::string& output) const;
};
