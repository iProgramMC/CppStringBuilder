#include <stdio.h>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include "StringBuilder.hpp"
#define LogMsg(fmt,...) printf(fmt "\n", __VA_ARGS__)

inline int min(int a, int b) {
	return a > b ? b : a;
}

uint64_t g_startTime;
uint64_t GetCurrentTimeMS()
{
	using namespace std::chrono;
	return (duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch())).count();
}

void StartStopwatch() {
	g_startTime = GetCurrentTimeMS();
}
uint64_t EndStopwatch() {
	auto backup = g_startTime;
	g_startTime = 0;
	return GetCurrentTimeMS() - backup;
}

#include "FunnyStrings.hpp"

int main() {
	LogMsg("StringBuilder test (C) 2021 iProgramInCpp");
	LogMsg("This code has been released under the GPL3 license.");
	//LogMsg("This will benchmark the performance of continuous string concatenations, using three methods:\n- std::string,\n- std::stringstream, and\n- my StringBuilder");

	// do the string method
	StartStopwatch();
	std::string testing_string = "";
	for (int i = 0; i < g_toConcat_size; i++) {
		testing_string += g_toConcat[i];
	}
	LogMsg("Using `std::string` method, successfully concatenated to %d bytes, took %lld microseconds", testing_string.size(), EndStopwatch());

	// do the stringstream method
	StartStopwatch();
	std::stringstream my_stream;
	for (int i = 0; i < g_toConcat_size; i++) {
		my_stream << g_toConcat[i];
	}
	LogMsg("Using `std::stringstream` method, successfully concatenated to %d bytes, took %lld microseconds", my_stream.str().size(), EndStopwatch());

	// do our StringBuilder method
	StartStopwatch();
	StringBuilder *my_builder = new StringBuilder();
	for (int i = 0; i < g_toConcat_size; i++) {
		my_builder->Append(g_toConcat[i]);
	}
	std::string the_string = my_builder->GetString();
	int size = the_string.size(), size2 = my_builder->GetLength();
	LogMsg("Using `StringBuilder` default method, successfully concatenated to %d bytes (%d bytes in builder), took %lld microseconds", size, size2, EndStopwatch());
	delete my_builder;

	// do it again, but this time allocate a set amount of 100005 bytes
	StartStopwatch();
	my_builder = new StringBuilder(100005);
	for (int i = 0; i < g_toConcat_size; i++) {
		my_builder->Append(g_toConcat[i]);
	}
	the_string = my_builder->GetString();
	size = the_string.size(); size2 = my_builder->GetLength();
	LogMsg("Using `StringBuilder` default method, successfully concatenated to %d bytes (%d bytes in builder), took %lld microseconds", size, size2, EndStopwatch());

	std::ofstream file1("out1.txt"), file2("out2.txt");
	file2 << my_builder->GetString();
	file1 << testing_string;
	file1.close();
	file2.close();

	delete my_builder;
}