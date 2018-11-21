#pragma once

#include "block.h"

class sequence
{
private:
	std::string file{};
	std::vector <std::unique_ptr<block>> blocks;
	bool check_index(int index) const;
	double eval_impl(double) const;
public:
	sequence(std::string file = "local.txt");
	~sequence();
	bool add(int type, const std::string& parameters);
	bool remove(int index);
	bool front(int index);
	bool print() const;
	bool eval(double value) const;
	bool eval(const std::string& input, const std::string& output) const;
};
