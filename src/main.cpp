/*
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Wed Jan 22 2017
 * Topik     : Bruteforce
 * Deskripsi : Cryptarithmetic
 */

#include <fstream>
#include <iostream>
#include <unistd.h>

#include "Parse.h"
#include "Solve.h"

int main (int argc, char** argv)
{
	char* o_in = NULL;
	bool o_exh = false;
	
	std::cerr << "Crypt-Arithmetic by Daniel (13515071)";
	std::cerr << std::endl << std::endl;
	
	// Option parsing
	
	int c;
	opterr = 0;
	
	while ((c = getopt (argc, argv, "ei:")) != -1)
	{
		switch (c)
		{
		case 'e':
			o_exh = true;
			break;
			
		case 'i':
			o_in = optarg;
			break;
			
		case '?':
			std::cerr << "Usage: " << argv[0] << " [-e] -i FILE" << std::endl;
			return EXIT_FAILURE;
			
		default:
			abort ();
		}
	}
	
	// File handling
	
	std::ifstream ifs;
	
	if (!o_in)
	{
		std::cerr << argv[0] << ": No input file" << std::endl;
		return EXIT_FAILURE;
	}
	
	ifs.open (o_in, std::ifstream::in);
	
	if (ifs.fail ())
	{
		std::cerr << argv[0] << ": Unable to open: " << o_in << std::endl;
		return EXIT_FAILURE;
	}
	
	Parse parser (ifs);
	
	// Solving
	
	bool loop = true;
	
	std::vector<std::string> addend;
	
	Solve solver;
	solver.exhaustive = o_exh;
	
	while (loop)
	{
		Parse::Token tok = parser.next ();
		
		switch (tok.type)
		{
		case Parse::Type::ADDEND:
			addend.push_back (tok.text);
			solver.put (tok.text);
			break;
			
		case Parse::Type::SUM:
		{
			solver.set_result (tok.text);
			
			clock_t cl = clock ();
			std::vector<Solve::Map> out = solver.solve ();
			uint32_t d = (clock () - cl) / (CLOCKS_PER_SEC / 1000);
			
			for (Solve::Map& map : out)
			{
				// Original
				
				if (addend.empty ())
					std::cout << "(empty)";
				else
				{
					std::cout << addend[0];
					
					for (auto it = addend.begin () + 1; it != addend.end (); ++it)
						std::cout << " + " << *it;
				}
				
				std::cout << " = " << tok.text;
				
				// Converted
				
				std::cout << " (";
				
				if (addend.empty ())
					std::cout << "(empty)";
				else
				{
					std::cout << map.convert (addend[0]);
					
					for (auto it = addend.begin () + 1; it != addend.end (); ++it)
						std::cout << " + " << map.convert (*it);
				}
				
				std::cout << " = " << map.convert (tok.text) << ")" << std::endl;
			}
			
			// Summary
			
			if (out.empty ())
				std::cout << "No solution found";
			else
			{
				if (o_exh)
					std::cout << out.size () << " solution(s)";
				else
					std::cout << "Solution found";
			}
			
			std::cout << " in " << d << " ms" << std::endl << std::endl;
			
			// Clean up
			
			solver.clear ();
			addend.clear ();
			
			break;
		}
			
		case Parse::Type::END:
			loop = false;
			break;
		}
	}
	
	return EXIT_SUCCESS;
}
