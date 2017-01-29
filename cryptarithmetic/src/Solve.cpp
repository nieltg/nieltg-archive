/*
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Wed Jan 20 2017
 * Topik     : Bruteforce
 * Deskripsi : Cryptarithmetic
 */

#include <algorithm>

#include "Solve.h"

Solve::Proxy Solve::input (const std::string& str)
{
	const std::size_t len = str.size ();
	Solve::Proxy proxy;
	
	for (std::size_t i = len; i--; )
	{
		char ch = str[i];
		Solve::Index::iterator it = map.find (ch);
		
		size_t id;
		
		if (it == map.end ())
		{
			id = new_id++;
			map[ch] = id;
		}
		else
			id = it->second;
		
		proxy.push_back (id);
	}
	
	proxy.shrink_to_fit ();
	return proxy;
}

void Solve::put (const std::string& str)
{
	db.push_back (input (str));
}

void Solve::set_result (const std::string& str)
{
	result = input (str);
}

bool Solve::gen (std::vector<Solve::Map>& out, Solve::Blend& mix,
                 std::size_t id, Solve::Guard gu)
{
	if (id < mix.size ())
	{
		// Generate
		
		const size_t n_id = id + 1;
		
		for (uint8_t i = 0; i < 10; i++)
		{
			if (!gu.test (i))
			{
				Solve::Guard n_gu = gu;
				n_gu.set (i);
				
				mix[id] = i;
				
				if (!gen (out, mix, n_id, n_gu))
					return false;
			}
		}
	}
	else
	{
		// Test
		
		size_t ci = 0;
		bool loop = true;
		
		uint32_t rem = 0;
		
		while (loop)
		{
			uint32_t sum = rem;
			
			// Addition
			
			bool stop_it = true;
			
			for (const Solve::Proxy& e : db)
			{
				if (ci < e.size ())
				{
					sum += mix[e[ci]];
					stop_it = false;
				}
			}
			
			if (stop_it && (sum == 0))
				break;
			
			// Check
			
			rem = sum / 10;
			sum = sum % 10;
			
			if ((ci < result.size ()) && (sum == mix[result[ci]]))
				ci++;
			else
				loop = false;
		}
		
		if (loop && (ci == result.size ()))
		{
			// BUGFIX: No zero allowed in first character
			
			bool push = true;
			
			for (const Solve::Proxy& e : db)
			{
				if (mix[e.back ()] == 0)
					push = false;
			}
			
			if (mix[result.back ()] == 0)
				push = false;
			
			// Store solution
			
			if (push)
			{
				out.push_back (Solve::Map (map, mix));
				
				if (!exhaustive)
					return false;
			}
		}
	}
	
	return true;
}

void Solve::clear (void)
{
	this->db.clear ();
	
	this->new_id = 0;
	this->map.clear ();
}

std::vector<Solve::Map> Solve::solve (void)
{
	std::vector<Solve::Map> out;
	Solve::Blend mix (new_id);
	
	gen (out, mix, 0, Solve::Guard ());
	
	return out;
}

Solve::Map::Map (const Solve::Index& map, const Solve::Blend& mix)
{
	for (const std::pair<char, std::size_t>& p : map)
		operator[] (p.first) = mix[p.second];
}

std::string Solve::Map::convert (const std::string& str)
{
	std::string out;
	
	for (char ch : str)
	{
		Solve::Map::iterator it = find (ch);
		
		if (it != end ())
			out.push_back ('0' + it->second);
		else
			out.push_back ('?');
	}
	
	return out;
}
