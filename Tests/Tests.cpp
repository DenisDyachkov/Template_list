#include "pch.h"
#include "CppUnitTest.h"
#include "../Template_list/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::list;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(HasElements_ValidData_Success)
		{
			List list{ 1, 22, 3 ,-1 ,999 };
			Assert::IsTrue(list.has_elements());
		}

		TEST_METHOD(ToString_ValidData_Success)
		{
			List list{ 1, 22, 3 ,-1 ,999 };
			Assert::IsTrue(list.to_string() == "1 22 3 -1 999 ");
		}

		TEST_METHOD(PushForward_ValidData_Success)
		{
			List list{ 1, 22, 3 ,-1 ,999 };
			list.push_forward(100);
			List expected_lsit{ 100, 1, 22, 3 ,-1 ,999 };
			Assert::IsTrue(list.to_string() == list.to_string());
		}

		TEST_METHOD(PushBack_ValidData_Success)
		{
			List list{ 1, 22, 3 ,-1 ,999 };
			list.push_forward(100);
			List expected_lsit{ 1, 22, 3 ,-1 ,999, 100 };
			Assert::IsTrue(list.to_string() == list.to_string());
		}

		TEST_METHOD(PushBackString_ValidData_Success)
		{
			List list{ "1", "22", "3" ,"-1" ,"999" };
			list.push_forward("100");
			List expected_lsit{ "1", "22", "3" ,"-1" ,"999", "100" };
			Assert::IsTrue(list.to_string() == list.to_string());
		}

		TEST_METHOD(PopForward_ValidData_Success)
		{
			List list{ 1, 22, 3 ,-1 ,999 };
			list.pop_forward();
			List expected_lsit{ 22, 3 ,-1 ,999 };
			Assert::IsTrue(list.to_string() == list.to_string());
		}

		TEST_METHOD(CoppyOperator_ValidData_Success)
		{
			List list_1{ 1, 22, 3 ,-1 ,999 };
			List list_2{ 3, 2, 555 ,-233 ,17423 };
			list_1 = list_2;
			Assert::IsTrue(list_1.to_string() == list_2.to_string());
		}
		TEST_METHOD(Pop_AllreadyEmpty_ExeptionExpected)
		{
			Assert::ExpectException<std::out_of_range>([]()
				{List<int> list = List<int>(); list.pop_forward(); });
		}

		TEST_METHOD(OutputOperator_ValidData_Success)
		{
			std::stringstream buffer;
			List list_1{ 1, 22, 3 ,-1 ,999 };
			buffer << list_1;
			Assert::IsTrue(buffer.str() == "1 22 3 -1 999 ");
		}
	};
}
