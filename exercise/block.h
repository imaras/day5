#pragma once

class block
{
protected:
	double in;
public:
	block() : in(0.){}
	void input(double input);
	virtual double output() const = 0;
	virtual ~block() = 0;
};

class block_with_constant : public block
{
protected:
	double constant;
public:
	block_with_constant(double constant = 0) : constant(constant) {}
};

// returns input
class identity : public block
{
public:
	double output() const override;
};

// returns input + constant
class addition : public block_with_constant
{
public: 
	addition(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns input * constant
class multiplication : public block_with_constant
{
public:
	multiplication(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns pow(input, constant)
class power : public block_with_constant
{
public:
	power(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns input constrained by min and max
class limit : public block
{
private:
	double min;
	double max;
public:
	limit(double min = 0, double max = 0) {}
	double output() const override;
};

// returns -1, 0, 1 based on comparison with constant
class condition : public block_with_constant
{
public:
	condition(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

std::unique_ptr<block> create_block(int type, const std::vector<double>& block_parameters);

