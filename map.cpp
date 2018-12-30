/*
 * map
 *
 *  Created on: 26 dec. 2018
 *      Author: cvengelen
 */

#include <map>
#include <iostream>
#include <utility>

#include "rvo.h"

int main (int argc, char **argv) {
	std::map<int, Rvo> rvoMap;

	// Call to rvoMap with not existing index creates Rvo with default constructor!
	std::cout << "rvoMap[24] rvo id: " << rvoMap[24].getIntVal() << std::endl;
	std::cout << "rvoMap size: " << rvoMap.size() << std::endl;

	// Call to at with not existing index raises out of range exception
	try {
		Rvo rvo{ rvoMap.at(25) };
	}
	catch(std::out_of_range& oor) {
		std::cout << "oor: " << oor.what() << std::endl;
	}
	std::cout << std::endl;

	// Use emplace with explicit pair: Normal constructor, two moves ?
	rvoMap.emplace(std::make_pair<int, Rvo>(26, {126, {2, 3, 4}}));
	std::cout << "rvoMap[26] rvo id: " << rvoMap.at(26).getIntVal() << ", size: " << rvoMap.at(26).getVectorValsRef().size() << std::endl << std::endl;

	// Use emplace with explicit pair: Normal constructor, two moves ?
	rvoMap.emplace(std::make_pair<int, Rvo>(27, Rvo(127, {3, 4, 5, 6})));
	std::cout << "rvoMap[27] rvo id: " << rvoMap.at(27).getIntVal() << ", size: " << rvoMap.at(27).getVectorValsRef().size() << std::endl << std::endl;

	// Best practice: use emplace with direct pair arguments: normal constructor, one move
	rvoMap.emplace(28, Rvo(128, {4, 5, 6, 7, 8}));
	std::cout << "rvoMap[28] rvo id: " << rvoMap.at(28).getIntVal() << ", size: " << rvoMap.at(28).getVectorValsRef().size() << std::endl << std::endl;
}
