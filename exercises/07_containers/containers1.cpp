#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// containers1.cpp
// Make me compile! Go to the folder hint if you want a hint :)

// We sometimes encourage you to keep trying things on shape given exercise,
// even after you already figured it out. 

// Step 1: Make me compile. Replace the array with the appropriate container.


constexpr int num_elements = 4;
unordered_map<int, int> my_sequence; // Fix change this type to the appropriate STL container

void test_containers1() {
	// Try to at least be partially efficient with memory
	my_sequence.reserve(num_elements);

	for (size_t i = 0; i < num_elements; i++)
	{
		my_sequence[i] = 42;
	}
}


#include <catch2/catch.hpp>

TEST_CASE("test_containers1") {
	test_containers1();
	std::cout << "Size of container : " << my_sequence.size() << "\n";
	REQUIRE(my_sequence.size() == num_elements); 

	for (const auto& e : my_sequence) {
		std::cout << "Value :" << e.first << "\n";
		REQUIRE(e.second == 42);
	}
}
