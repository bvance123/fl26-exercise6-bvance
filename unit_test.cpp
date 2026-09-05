////////////////////////////////////////////////////////
// ECE 3574 Exercise: Unit Tests with Catch - starter code
//
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#define CATCH_CONFIG_MAIN  // This line tells Catch to provide a main() function

                           // - do this in one cpp file only
#include "catch.hpp"       // This line provides access to all Catch macros
                           // - do not modify catch.hpp
#include <cassert>    
#include <cstdlib>
#include <map>
#include <string>

TEST_CASE("multimap unit test1", "[multimap]") {
	std::multimap<std::string, std::string> m;	
	REQUIRE(m.size() == 0);
	
	m.insert(std::pair<std::string, std::string>("Ross", "Betsy"));
	REQUIRE(m.size() == 1);

}

TEST_CASE("multimap unit test2", "[multimap]") {
	std::multimap<std::string, std::string> m;

	m.insert(std::pair<std::string, std::string>("Pikachu", "Blastoise"));
	m.insert(std::pair<std::string, std::string>("Pikachu", "Charmander"));
	m.insert(std::pair<std::string, std::string>("Mootank", "Charizard"));

	REQUIRE(m.size() == 3);
	auto range = m.equal_range("Pikachu");
	int count = 0;
	for (auto it = range.first; it != range.second; ++it) {
		++count;
	}
	REQUIRE(count == 2);
}

TEST_CASE("multimap unit test3 - with SECTION", "[multimap]") {
	std::multimap<int, std::string> mm;
	SECTION("insert and find elements") {
		mm.insert({ 1, "one" });
		mm.insert({ 2, "two" });
		mm.insert({ 1, "uno" });
		REQUIRE(mm.size() == 3);
	}
	SECTION("count elements with key 1") {
		mm.insert({ 1, "one" });
		mm.insert({ 2, "two" });
		mm.insert({ 1, "uno" });
		REQUIRE(mm.count(1) == 2);
	}
}

TEST_CASE("multimap: operator=, size, insert", "[multimap]") {
	std::multimap<int, std::string> m1 = { {1, "one"}, {2, "two"}, {1, "three"} };
	std::multimap<int, std::string> m2;
	m2 = m1; 
	REQUIRE(m2.size() == 3);
	REQUIRE(m2.count(1) == 2);
	REQUIRE(m2.count(2) == 1);

	REQUIRE(m2.size() == m1.size());
	REQUIRE(m2.count(1) == m1.count(1));

	m2.insert({ 3, "four" });

	REQUIRE(m2.size() == m1.size() + 1);
	REQUIRE(m1.size() == 3);
}

TEST_CASE("multimap: empty, insert", "[multimap]") {
	std::multimap<int, std::string> m;
	REQUIRE(m.empty() == true);
	m.insert({ 1, "one" });
	REQUIRE(m.empty() == false);
}

TEST_CASE("multimap: size, insert", "[multimap]") {
	std::multimap<double, double> m;
	REQUIRE(m.size() == 0);
	m.insert({ 1.1, 2.2 });
	m.insert({ 3.3, 4.4 });
	REQUIRE(m.size() == 2);
}

TEST_CASE("multimap: clear, empty, size", "[multimap]") {
	std::multimap < std::string, int> m = { {"a", 1}, {"b", 2}, {"c", 3} };

	m.clear();
	REQUIRE(m.empty() == true);
	REQUIRE(m.size() == 0);
}

TEST_CASE("multimap: erase, size, count, find", "[multimap]") {
	std::multimap<int, std::string> m = { {1, "A"}, {1, "B"}, {2, "C"} };

	SECTION("erase using key") {
		size_t removed_entries = m.erase(1);
		REQUIRE(removed_entries == 2);
		REQUIRE(m.size() == 1);
		REQUIRE(m.count(1) == 0);
	}

	SECTION("erase using iterator (using find)") {
		auto entry = m.find(2);
		m.erase(entry);
		REQUIRE(m.size() == 2);
		REQUIRE(m.count(2) == 0);
	}
}

TEST_CASE("multimap: find, end", "[multimap]") {
	std::multimap<int, std::string> m = { {1, "one"}, {2, "two"} };

	auto entry = m.find(1);
	REQUIRE(entry != m.end());
	REQUIRE(entry->second == "one");
	
	auto absent_entry = m.find(1000000);
	REQUIRE(absent_entry == m.end());

}


