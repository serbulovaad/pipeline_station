#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <format>
#include <vector>
#include <set>
#include <stack>


std::string inputString(std::istream& in = std::cin);
//std::string inputString(std::istream& in, const std::string& exeption = "");

template <typename T>
T inputNumber(std::istream& in = std::cin);

template <typename T>
T getCorrectNumber(T a, T b, bool included = true, std::istream& in = std::cin);

template <typename T>
T getPositiveNumber(std::istream& in = std::cin);

bool confirm(std::string);

void coutNoObjectFound(std::string = "objects");

void coutV();

// ����� 
class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
