#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include "../ALGSTRD2/List.h"
#include "../ALGSTRD2/Tree.h"
#include "../ALGSTRD2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(code1)
		{
			string input = "it is test string";
			Sifer S(input);
			string expected = "100111110110111010011110011111100100101000010000";
			Assert::AreEqual(expected, S.get_code());
		}

		TEST_METHOD(code2)
		{
			string input = "aaabb";
			Sifer S(input);
			string expected = "11100";
			Assert::AreEqual(expected, S.get_code());
		}

		TEST_METHOD(decode1)
		{
			string input = "it is test string";
			Sifer S(input);
			string expected = input;
			Assert::AreEqual(expected, S.get_decode());
		}

		TEST_METHOD(decode2)
		{
			string input = "aaabb";
			Sifer S(input);
			string expected = input;
			Assert::AreEqual(expected, S.get_decode());
		}

		TEST_METHOD(compression_ratio1)
		{
			string input = "it is test string";
			Sifer S(input);
			double a = 136;
			double b = 48;
			double expected = a / b;
			Assert::AreEqual(expected, S.get_compression_ratio());
		}

		TEST_METHOD(compression_ratio2)
		{
			string input = "aaabb";
			Sifer S(input);
			double a = 40;
			double b = 5;
			double expected = a / b;
			Assert::AreEqual(expected, S.get_compression_ratio());
		}

		TEST_METHOD(exception)
		{
			string input = "aaa";
			bool b = 1;
			try
			{
				Sifer S(input);
				b = 0;
			}
			catch (invalid_argument& exception) {}
			Assert::IsTrue(b);
		}
	};
}
