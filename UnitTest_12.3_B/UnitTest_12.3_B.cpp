#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12.3_B/lab_12.3_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest123B
{
	TEST_CLASS(UnitTest123B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(calc_n(1000),4);
		}
	};
}
