#include "stdafx.h"
#include "../exercise/block.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(block_test)
	{
	public:
		TEST_METHOD(identity_output)
		{
			identity block;
			block.input(4.5);
			double out = block.output();
			Assert::AreEqual(4.5, out);
		}
		TEST_METHOD(addition_output)
		{
			addition block(4.5);
			block.input(1);
			double out = block.output();
			Assert::AreEqual(5.5, out);
		}
		TEST_METHOD(multiplication_output)
		{
			multiplication block(3.5);
			block.input(2);
			double out = block.output();
			Assert::AreEqual(7.0, out);
		}
		TEST_METHOD(power_output)
		{
			power block(3.0);
			block.input(2);
			double out = block.output();
			Assert::AreEqual(8.0, out);
		}
		TEST_METHOD(limit_output_bellow_range)
		{
			limit block(3.5, 8.7);
			block.input(2);
			double out = block.output();
			Assert::AreEqual(3.5, out);
		}
		TEST_METHOD(limit_output_in_range)
		{
			limit block(3.5, 8.7);
			block.input(5.5);
			double out = block.output();
			Assert::AreEqual(5.5, out);
		}
		TEST_METHOD(limit_output_above_range)
		{
			limit block(3.5, 8.7);
			block.input(9.3);
			double out = block.output();
			Assert::AreEqual(8.7, out);
		}
		TEST_METHOD(condition_output_bellow_limit)
		{
			condition block(5.0);
			block.input(2);
			double out = block.output();
			Assert::AreEqual(-1.0, out);
		}
		TEST_METHOD(condition_output_at_limit)
		{
			condition block(5.0);
			block.input(5);
			double out = block.output();
			Assert::AreEqual(0.0, out);
		}
		TEST_METHOD(condition_output_above_limit)
		{
			condition block(5.0);
			block.input(7);
			double out = block.output();
			Assert::AreEqual(1.0, out);
		}
		TEST_METHOD(print_identity)
		{
			std::stringstream ss;
			identity block;
			ss << block;
			Assert::AreEqual(0, ss.str().compare("1 "));
		}
		TEST_METHOD(print_addition)
		{
			std::stringstream ss;
			addition block(4.5);
			ss << block;
			Assert::AreEqual(0, ss.str().compare("2 4.5 "));
		}
		TEST_METHOD(print_multiplication)
		{
			std::stringstream ss;
			multiplication block(3.5);
			ss << block;
			Assert::AreEqual(0, ss.str().compare("3 3.5 "));
		}
		TEST_METHOD(print_power)
		{
			std::stringstream ss;
			power block(3.0);
			ss << block;
			Assert::AreEqual(0, ss.str().compare("4 3 "));
		}
		TEST_METHOD(print_limit)
		{
			std::stringstream ss;
			limit block(3.5, 8.7);
			ss << block;
			Assert::AreEqual(0, ss.str().compare("5 3.5 8.7 "));
		}
		TEST_METHOD(print_condition)
		{
			std::stringstream ss;
			condition block(5.0);
			ss << block;
			Assert::AreEqual(0, ss.str().compare("6 5 "));
		}
		TEST_METHOD(create_non_existing_block)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(100, ss);
			Assert::IsTrue(nullptr == block);
		}
		TEST_METHOD(create_identity)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(1, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(identity)));
		}
		TEST_METHOD(create_addition_from_valid_parameters)
		{
			std::stringstream ss("4");
			std::unique_ptr<block> block = create_block(2, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(addition)));
		}
		TEST_METHOD(create_addition_from_invalid_parameters)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(2, ss);
			Assert::IsTrue(nullptr == block);
		}
		TEST_METHOD(create_multiplication_from_valid_parameters)
		{
			std::stringstream ss("4");
			std::unique_ptr<block> block = create_block(3, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(multiplication)));
		}
		TEST_METHOD(create_multiplication_from_invalid_parameters)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(3, ss);
			Assert::IsTrue(nullptr == block);
		}
		TEST_METHOD(create_power_from_valid_parameters)
		{
			std::stringstream ss("4");
			std::unique_ptr<block> block = create_block(4, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(power)));
		}
		TEST_METHOD(create_power_from_invalid_parameters)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(4, ss);
			Assert::IsTrue(nullptr == block);
		}
		TEST_METHOD(create_limit_from_valid_parameters)
		{
			std::stringstream ss("4 6");
			std::unique_ptr<block> block = create_block(5, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(limit)));
		}
		TEST_METHOD(create_limit_from_invalid_parameters)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(5, ss);
			Assert::IsTrue(nullptr == block);
		}
		TEST_METHOD(create_condition_from_valid_parameters)
		{
			std::stringstream ss("4");
			std::unique_ptr<block> block = create_block(6, ss);
			Assert::IsTrue(nullptr != block);
			Assert::IsTrue(std::type_index(typeid(*block)) == std::type_index(typeid(condition)));
		}
		TEST_METHOD(create_condition_from_invalid_parameters)
		{
			std::stringstream ss;
			std::unique_ptr<block> block = create_block(6, ss);
			Assert::IsTrue(nullptr == block);
		}
	};
}