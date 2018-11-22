#include "stdafx.h"
#include "../exercise/block.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(block_test)
	{
	public:
		TEST_METHOD(test_identity)
		{
			identity block;
			block.input(4.5);

			double out = block.output();

			Assert::AreEqual(4.5, out);
		}
	};
}