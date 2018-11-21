#pragma once

class block
{
protected:
	double in;
	virtual void print(std::ostream& os) const = 0;
public:
	block() : in(0.){}
	void input(double input);
	virtual double output() const = 0;
	virtual ~block() = 0;
	friend std::ostream& operator<<(std::ostream& os, const block& block);
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
protected:
	void print(std::ostream& os) const override;
public:
	double output() const override;
};

// returns input + constant
class addition : public block_with_constant
{
protected:
	void print(std::ostream& os) const override;
public: 
	addition(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns input * constant
class multiplication : public block_with_constant
{
protected:
	void print(std::ostream& os) const override;
public:
	multiplication(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns pow(input, constant)
class power : public block_with_constant
{
protected:
	void print(std::ostream& os) const override;
public:
	power(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// returns input constrained by min and max
class limit : public block
{
private:
	double minimum;
	double maximum;
protected:
	void print(std::ostream& os) const override;
public:
	limit(double minimum = 0, double maximum = 0) : minimum(minimum), maximum(maximum) {}
	double output() const override;
};

// returns -1, 0, 1 based on comparison with constant
class condition : public block_with_constant
{
protected:
	void print(std::ostream& os) const override;
public:
	condition(double constant = 0) : block_with_constant(constant) {}
	double output() const override;
};

// factory function
std::unique_ptr<block> create_block(int type, std::istream& stream);
