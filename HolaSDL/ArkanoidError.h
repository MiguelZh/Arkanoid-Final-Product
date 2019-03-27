#pragma once
#include <exception>
#include <stdexcept>

using namespace std;

class ArkanoidError : public logic_error {
public:
	ArkanoidError(string s) : logic_error("Error: " + s) {}

	string what() {
		return what();
	}
};
