#pragma once

class command
{
public:
	virtual bool execute() const = 0;
	virtual ~command() = 0;
};

class help : public command
{
public:
	bool execute() const override;
};

class add_block : public command
{
private:
	int type;
	std::string parameters;
public:
	add_block(int type, std::string parameters) : type(type), parameters(parameters) {};
	bool execute() const override;
};

class remove_block : public command
{
private: 
	int index;
public:
	remove_block(int index) : index(index) {};
	bool execute() const override;
};

class front_block : public command
{
private:
	int index;
public:
	front_block(int index) : index(index) {};
	bool execute() const override;
};

class print_seq : public command
{
public:
	bool execute() const override;
};

class eval_value : public command
{
private:
	double value;
public:
	eval_value(double value) : value(value) {};
	bool execute() const override;
};

class eval_file : public command
{
private:
	std::string input;
	std::string output;
public:
	eval_file(std::string input, std::string output) : input(input), output(output) {};
	bool execute() const override;
};

std::unique_ptr<command> create_command(int argc, char* argv[]);

