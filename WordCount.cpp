/*
 * WordCount.cpp
 * From: https://www.artima.com/samples/cpp11-14NotesSample.pdf
 * (sample van The New C++ (C++11/14), Scott Meyers)
 *
 *  Created on: 29 dec. 2018
 *      Author: cvengelen
 */
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <future>

using WordCountMap = std::unordered_map<std::string, std::size_t>;
using WordCountMapIterator = WordCountMap::const_iterator;

// for each word in file, return # of occurrences
WordCountMap wordsInFile(const std::string& fileName) {
	std::ifstream file(fileName);
	WordCountMap wordCounts;
//	for (std::string word; file >> word; ) {
	while (!file.eof()) {
		std::string word;
		file >> word;
		++wordCounts[word];
	}
	return wordCounts;
}

// print n most common words in [begin, end)
// template<typename MapIt>
// void showCommonWords(MapIt begin, MapIt end, const std::size_t n)
void showCommonWords(WordCountMapIterator wordCountMapBegin, WordCountMapIterator wordCountMapEnd, const std::size_t n) {
	std::vector<WordCountMapIterator> wordIters;
	wordIters.reserve(std::distance(wordCountMapBegin, wordCountMapEnd));

	for (auto wordCountMapIterator{ wordCountMapBegin }; wordCountMapIterator != wordCountMapEnd; ++wordCountMapIterator) {
		wordIters.push_back(wordCountMapIterator);
	}

	auto sortedRangeEnd = wordIters.begin() + n;
	std::partial_sort(wordIters.begin(), sortedRangeEnd, wordIters.end(),
			[ ](WordCountMapIterator wordCountMapIterator1, WordCountMapIterator wordCountMapIterator2) { return wordCountMapIterator1->second > wordCountMapIterator2->second; });

	for (auto wordCountMapIterator = wordIters.cbegin(); wordCountMapIterator != sortedRangeEnd; ++wordCountMapIterator) {
		std::printf(" %-10s%10zu\n",(*wordCountMapIterator)->first.c_str(),(*wordCountMapIterator)->second);
	}
}

// take list of file names on command line,
// print most common words within;
int main(int argc, const char** argv)
{
	// process files concurrently
	std::vector<std::future<WordCountMap>> futures;
	for (int argNum = 1; argNum < argc; ++argNum) {
		std::string fileName{argv[argNum]};
		if (!fileName.empty()) {
			// Fix eclipse arguments with quotes bug
			if (fileName[fileName.size()-1] == '\'') fileName = fileName.substr(0, fileName.size()-1);
			if (fileName[0] == '\'') fileName = fileName.substr(1, fileName.size()-1);
			futures.push_back(std::async(std::launch::async,
							  [=]()->WordCountMap{ return wordsInFile(fileName); }));
		}
	}

	WordCountMap wordCounts;
	for (auto& future : futures) {
		const auto wordCountInfoForFile = future.get(); // move map returned by wordsInFile
		for (const auto& wordInfo : wordCountInfoForFile) {
			wordCounts[wordInfo.first] += wordInfo.second;
		}
	}

	std::cout << wordCounts.size() << " words found. Most common:\n" ;
	constexpr std::size_t maxWordsToShow = 50;
	showCommonWords( wordCounts.begin(), wordCounts.end(),
			std::min(wordCounts.size(), maxWordsToShow));
}
