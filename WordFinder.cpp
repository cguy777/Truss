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

#include "WordFinder.h"
#include <string>

std::string line;
int count;

WordFinder::WordFinder() {
	line = "";
	count = 0;
}

WordFinder::~WordFinder() {

}

void WordFinder::setLine(std::string lineToParse) {
	line = lineToParse;
	count = 0;
}

std::string WordFinder::getNextWord() {

	std::string word = "";

	//Return null string if there is no more words.
	if (count >= line.length()) {
		return "";
	}

	//Check for comments
	if (line.length() >= 2) {
		if (line.at(0) == '/' && line.at(1) == '/')
			return "";
	}

	//Remove leading whitespaces
	for (int i = count; i < line.length(); i++) {
		if (line.at(i) == ' ') {
			count++;
		} else {
			//If it isn't whitespace, then break out of it and start reading the actual word
			break;
		}
	}

	//Check for quotes.  If so, read until the next quote
	if (line.at(count) == '"') {

		//Add the first quote into the word
		word.append(1, line.at(count));
		count++;

		for (int i = count; i < line.length(); i++) {
			if (line.at(i) != '"') {
				word.append(1, line.at(i));
				count++;
			} else {
				word.append(1, line.at(i));
				count++;
				break;
			}
		}

	} else {
		//read until we see the next whitespace.
		for (int i = count; i < line.length(); i++) {

			//Read until the next space
			if (line.at(i) != ' ') {
				word.append(1, line.at(i));
				count++;
			} else {
				break;
			}
		}
	}

	return word;
}