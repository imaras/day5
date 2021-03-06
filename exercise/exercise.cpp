#include "pch.h"
#include "command.h"

int main(int argc, char* argv[])
{
	const std::unique_ptr<command> c = create_command(argc, argv);
	if (c == nullptr) return -1;

	const bool success = c->execute();
	if (!success) return -1;

	return 0;
}
