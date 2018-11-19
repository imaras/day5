#include "pch.h"
#include "command.h"

bool help::execute()
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

bool add_block::execute()
{
	return false;
}

bool remove_block::execute()
{
	return false;
}

bool front_block::execute()
{
	return false;
}

bool print_seq::execute()
{
	return false;
}

bool eval_value::execute()
{
	return false;
}

bool eval_file::execute()
{
	return false;
}

std::optional<int> parse_int(std::string s)
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

std::optional<double> parse_double(std::string s)
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
	std::string types(argv[2]);
	std::optional<int> type = parse_int(types);
	if(!type.has_value())
	{
		return nullptr;
	}

	// get parameters
	std::string parameters(argv[3]);
	for (int i = 4; i < argc; i++)
	{
		parameters.append(" ");
		parameters.append(argv[i]);
	}

	return std::make_unique<add_block>(type.value(), parameters);
}

std::unique_ptr<command> create_remove_block(char* argv[])
{
	// get index
	std::string indexs(argv[2]);
	std::optional<int> index = parse_int(indexs);
	return index.has_value() ? std::make_unique<remove_block>(index.value()) : nullptr;
}

std::unique_ptr<command> create_front_block(char* argv[])
{
	// get index
	std::string indexs(argv[2]);
	std::optional<int> index = parse_int(indexs);
	return index.has_value() ? std::make_unique<front_block>(index.value()) : nullptr;
}

std::unique_ptr<command> create_eval_value(char* argv[])
{
	// get value
	std::string values(argv[2]);
	std::optional<int> value = parse_double(values);
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
	else if (argc >= 4 && command.compare("--add") == 0)
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
