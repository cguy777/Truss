/* Copyright 2022 Noah McLean
 *
 * Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the
 *    above copyright notice, this list of conditions and
 *    the following disclaimer in the documentation and/or
 *    other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the
 *    names of its contributors may be used to endorse or
 *    promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Lexer.h"

std::vector<std::string> tr_num_operators{ "=", "+", "-", "*", "/", "(", ")" };
std::vector<std::string> tr_keywords{ "func", "var" };

WordFinder* finder;
std::vector<Word> words;
VariableStore variables;
std::vector<std::string> functions;

Lexer::Lexer(VariableStore vStore, std::vector<std::string> funcs) {
	finder = new WordFinder();
	variables = vStore;
	functions = funcs;
}

Lexer::~Lexer() {
	delete finder;
}

std::vector<Word> Lexer::parseLine(std::string lineToParse) {
	words.clear();
	finder->setLine(lineToParse);

	parse();

	return words;
}

void Lexer::parse() {
	std::string wordText;
	
	while (true) {
		wordText = finder->getNextWord();

		//quit if null (EOL) is found
		if (wordText.compare("") == 0) {
			break;
		}

		Word word;
		word.text = wordText;
		word.type = determineType(wordText);

		words.push_back(word);
	}
}

WordType Lexer::determineType(std::string word) {
	
	//Check if keyword
	if (isMatch(word, tr_keywords))
		return WordType::keyword;

	if (isMatch(word, tr_num_operators))
		return WordType::num_operator;

	//Check if variable name
	if (isMatch(word, variables.getVariableNames()))
		return WordType::var_name;

	//Check if function
	if (isMatch(word, functions))
		return WordType::func_name;

	//Check if string
	if (isString(word))
		return WordType::string;

	//Check if integer
	if (isInteger(word))
		return WordType::integer;

	//check if float
	if (isFloat(word))
		return WordType::floating_point;

	//Return undefined by default
	return WordType::undefined;
}

bool Lexer::isMatch(std::string word, std::vector<std::string> wordList) {
	//If a match is found in the word list, then return true
	for (int i = 0; i < wordList.size(); i++) {
		if (word.compare(wordList[i]) == 0) {
			return true;
		}
	}

	return false;
}