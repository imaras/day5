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
	sequence(std::string file);
	~sequence();
	bool add(int type, const std::string& parameters);
	bool remove(size_t index);
	bool front(size_t index);
	bool print(std::ostream& os) const;
	bool eval(double value, std::ostream& os) const;
	bool eval(std::istream& is, std::ostream& os) const;
};
