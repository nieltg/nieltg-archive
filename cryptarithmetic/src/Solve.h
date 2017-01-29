/*
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Wed Jan 20 2017
 * Topik     : Bruteforce
 * Deskripsi : Cryptarithmetic
 */

#pragma once

#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Solve
{
public:
	class Map;
	
	bool exhaustive;
	
	Solve (void) : exhaustive (true), new_id (0) {};
	
	void put (const std::string& str);
	void set_result (const std::string& str);
	
	void clear (void);
	std::vector<Solve::Map> solve (void);
	
private:
	using Guard = std::bitset<10>;
	using Proxy = std::vector<std::size_t>;
	using Blend = std::vector<std::uint8_t>;
	using Index = std::map<char, std::size_t>;
	
	Proxy input (const std::string& str);
	bool gen (std::vector<Map>& out, Blend& map, std::size_t id, Guard gu);
	
	Index map;
	std::size_t new_id;
	
	Proxy result;
	std::vector<Proxy> db;
};

class Solve::Map : public std::map<char, std::uint8_t>
{
public:
	Map (const Solve::Index& map, const Solve::Blend& mix);
	
	std::string convert (const std::string& str);
};
