#include "pch.h"
#include "command.h"
#include "sequence.h"

command::~command()
{
}

bool help::execute() const
{
	std::cout
		<< "Sequence Help" << std::endl
		<< "Commands:" << std::endl
		<< "exercise --help" << std::endl
		<< "exercise --add <block type> <block parameters>" << std::endl
		<< "exercise --remove <block index>" << std::endl
		<< "exercise --front <block index>" << std::endl
		<< "exercise --print" << std::endl
		<< "exercise --eval <value>" << std::endl
		<< "exercise --eval <input file> <output file>" << std::endl;
	return true;
}

const std::string file_name = "local.txt";

bool add_block::execute() const
{
	sequence s(file_name);
	return s.add(type, parameters);
}

bool remove_block::execute() const
{
	sequence s(file_name);
	return s.remove(index);
}

bool front_block::execute() const
{
	sequence s(file_name);
	return s.front(index);
}

bool print_seq::execute() const
{
	sequence s(file_name);
	return s.print(std::cout);
}

bool eval_value::execute() const
{
	sequence s(file_name);
	return s.eval(value, std::cout);
}

bool eval_file::execute() const
{
	std::ifstream in(input);
	std::ofstream out(output);

	sequence s(file_name);
	return s.eval(in, out);
}

std::optional<int> parse_int(const std::string& s)
{
	try
	{
		return std::stoi(s);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<double> parse_double(const std::string& s)
{
	try
	{
		return std::stod(s);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::unique_ptr<command> create_add_block(int argc, char* argv[])
{
	// get type
	const std::string type_s(argv[2]);
	std::optional<int> type = parse_int(type_s);
	if(!type.has_value())
	{
		return nullptr;
	}

	// get parameters
	std::string parameters;
	for (int i = 3; i < argc; i++)
	{
		parameters.append(" ");
		parameters.append(argv[i]);
	}

	return std::make_unique<add_block>(type.value(), parameters);
}

std::unique_ptr<command> create_remove_block(char* argv[])
{
	// get index
	const std::string index_s(argv[2]);
	std::optional<int> index = parse_int(index_s);
	return index.has_value() ? std::make_unique<remove_block>(index.value()) : nullptr;
}

std::unique_ptr<command> create_front_block(char* argv[])
{
	// get index
	const std::string index_s(argv[2]);
	std::optional<int> index = parse_int(index_s);
	return index.has_value() ? std::make_unique<front_block>(index.value()) : nullptr;
}

std::unique_ptr<command> create_eval_value(char* argv[])
{
	// get value
	const std::string value_s(argv[2]);
	std::optional<double> value = parse_double(value_s);
	return value.has_value() ? std::make_unique<eval_value>(value.value()) : nullptr;
}

std::unique_ptr<command> create_eval_file(char* argv[])
{
	// get file paths
	std::string input(argv[2]);
	std::string output(argv[3]);

	return std::make_unique<eval_file>(input, output);
}

std::unique_ptr<command> create_command(int argc, char* argv[])
{
	if (argc < 2)
	{
		return nullptr;
	}

	std::string command(argv[1]);
	if (argc == 2 && command.compare("--help") == 0)
	{
		return std::make_unique<help>();
	}
	else if (argc >= 3 && command.compare("--add") == 0)
	{
		return create_add_block(argc, argv);
	}
	else if (argc == 3 && command.compare("--remove") == 0)
	{
		return create_remove_block(argv);
	}
	else if (argc == 3 && command.compare("--front") == 0)
	{
		return create_front_block(argv);
	}
	else if (argc == 2 && command.compare("--print") == 0)
	{
		return std::make_unique<print_seq>();
	}
	else if (argc == 3 && command.compare("--eval") == 0)
	{
		return create_eval_value(argv);
	}
	else if (argc == 4 && command.compare("--eval") == 0)
	{
		return create_eval_file(argv);
	}
	else
	{
		return nullptr;
	}
}
