#include "stdafx.h"
#include "../exercise/sequence.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	const std::string file_name = "test.txt";

	TEST_CLASS(sequnece_test)
	{
	public:
		TEST_METHOD_CLEANUP(remove_sequence_file)
		{
			std::remove(file_name.c_str());
		}
		TEST_METHOD(add_block)
		{
			sequence s(file_name);
			s.add(1, "");
			s.add(2, "2.5");
			s.add(3, "3.5");
			s.add(4, "2");
			s.add(5, "-3.5 8.4");
			s.add(6, "5.5");

			std::stringstream ss;
			s.print(ss);

			Assert::AreEqual(0, ss.str().compare("1 2 2.5 3 3.5 4 2 5 -3.5 8.4 6 5.5 "));
		}
		TEST_METHOD(remove_block)
		{
			sequence s(file_name);
			s.add(1, "");
			s.add(2, "2.5");
			s.add(3, "3.5");
			s.remove(0);

			std::stringstream ss;
			s.print(ss);

			Assert::AreEqual(0, ss.str().compare("2 2.5 3 3.5 "));
		}
		TEST_METHOD(front_block)
		{
			sequence s(file_name);
			s.add(1, "");
			s.add(2, "2.5");
			s.add(3, "3.5");
			s.front(2);

			std::stringstream ss;
			s.print(ss);

			Assert::AreEqual(0, ss.str().compare("3 3.5 1 2 2.5 "));
		}
		TEST_METHOD(eval_value)
		{
			sequence s(file_name);
			s.add(1, "");
			s.add(2, "2.5");
			s.add(3, "3.5");
			
			std::stringstream ss;
			s.eval(3.5, ss);

			Assert::AreEqual(0, ss.str().compare("21"));
		}
		TEST_METHOD(eval_stream)
		{
			sequence s(file_name);
			s.add(1, "");
			s.add(2, "2.5");
			s.add(3, "3.5");

			std::stringstream input("1.0 2.3 4.5 7.9");
			std::stringstream output;
			s.eval(input, output);

			Assert::AreEqual(0, output.str().compare("12.25 16.8 24.5 36.4 "));
		}
	};
}