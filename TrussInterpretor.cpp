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

#include <iostream>
#include <fstream>
#include "Variable.h"
#include "Lexer.h"
#include "VariableStore.h"

std::string convertWordType(WordType wt) {
	if (wt == WordType::func_name) {
		return "func_name";
	}

	if (wt == WordType::keyword) {
		return "keyword";
	}

	if (wt == WordType::integer) {
		return "integer";
	}

	if (wt == WordType::floating_point) {
		return "floating_point";
	}

	if (wt == WordType::num_operator) {
		return "num_operator";
	}

	if (wt == WordType::string) {
		return "string";
	}

	if (wt == WordType::undefined) {
		return "undefined";
	}

	if (wt == WordType::var_name) {
		return "var_name";
	}

	return "ERROR";
}

int main() {

	std::fstream file;
	std::string currentLine;
	file.open("Script.truss", std::ios::in);

	std::vector<std::string> funcs;
	VariableStore vStore;
	Lexer lexer(vStore, funcs);

	std::vector<Word> words;
	

	if (file.is_open()) {

		while (std::getline(file, currentLine)) {
			
			words = lexer.parseLine(currentLine);

			//print code
			for (int i = 0; i < words.size(); i++) {
				std::cout << words[i].text << ", ";
			}
			std::cout << "\n";

			//print word types from code
			for (int i = 0; i < words.size(); i++) {
				std::cout << convertWordType(words[i].type) << ", ";
			}
			std::cout << "\n";

		}

	} else {
		std::cout << "Could not open file";
	}

	std::cout << "\n\n\n";


	file.close();

	return 0;
}
