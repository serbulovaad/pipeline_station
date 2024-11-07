#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

std::string inputString(std::istream& in);
//std::string inputString(std::istream& in, const std::string& exeption = "");

template <typename T>
T inputNumber(std::istream& in = std::cin);

template <typename T>
T getCorrectNumber(T a, T b, bool included = true, std::istream& in = std::cin);

template <typename T>
T getPositiveNumber(std::istream& in = std::cin);

bool confirm();