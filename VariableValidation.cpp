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

#include "VariableValidation.h"

VariableType determineVariableType(std::string s) {

	if (isString(s))
		return VariableType::STRING;

	if (isInteger(s))
		return VariableType::INTEGER;

	if (isFloat(s)) {
		return VariableType::FLOAT;
	}

	//If we don't match anything, it must be incorrectly formatted
	return VariableType::INVALID;
}

bool isString(std::string s) {
	//Check for quotes at the beginning and end
	if (s.at(0) == '"' && s.at(s.length() - 1) == '"') {

		return true;
	} else {
		return false;
	}
}

bool isInteger(std::string s) {

	//Check for invalid characters
	for (int i = 0; i < s.length(); i++) {

		if (!isIntChars(s.at(i)))
			return false;

	}

	//If nothing is invalid, then it is an integer
	return true;
}

bool isFloat(std::string s) {

	bool containsDecimal = false;

	for (int i = 0; i < s.length(); i++) {

		//Check for invalid float characters first
		if (!isFloatChars(s.at(i)))
			return false;

		//If there's two decimals, it's not a float
		if (containsDecimal && s.at(i) == '.') {
			return false;
		}

		//Enable flag if we found a decimal
		if (!containsDecimal && s.at(i) == '.') {
			containsDecimal = true;
		}
	}

	if (containsDecimal) {
		return true;
	} 

	//didn't contain a decimal, so it's not a float
	return false;
}

bool isIntChars(char c) {
	if (c == '0') {
		return true;
	}

	if (c == '1') {
		return true;
	}

	if (c == '2') {
		return true;
	}

	if (c == '3') {
		return true;
	}

	if (c == '4') {
		return true;
	}

	if (c == '5') {
		return true;
	}

	if (c == '6') {
		return true;
	}

	if (c == '7') {
		return true;
	}

	if (c == '8') {
		return true;
	}

	if (c == '9') {
		return true;
	}

	//If no matches, it can't be an integer
	return false;
}

bool isFloatChars(char c) {

	if (c == '0') {
		return true;
	}

	if (c == '1') {
		return true;
	}

	if (c == '2') {
		return true;
	}

	if (c == '3') {
		return true;
	}

	if (c == '4') {
		return true;
	}

	if (c == '5') {
		return true;
	}

	if (c == '6') {
		return true;
	}

	if (c == '7') {
		return true;
	}

	if (c == '8') {
		return true;
	}

	if (c == '9') {
		return true;
	}

	if (c == '.') {
		return true;
	}

	//If no matches, it can't be an integer
	return false;
}

std::string stripQuotes(std::string s) {
	std::string temp = "";

	for (int i = 1; i < s.length() - 1; i++) {
		temp.append(1, s.at(i));
	}

	return temp;
}

std::string fixFloatFormatting(std::string s) {
	//If starts with a decimal, add a zero to the beginning
	if (s.at(0) == '.') {
		std::string temp = "0";
		temp.append(s);
		return temp;
	}

	//If ends with a decimal, add a zero to the end
	if (s.at(s.length() - 1) == '.') {
		std::string temp = s;
		s.append(1, '0');
		return temp;
	}

	//Return the original if formatting is fine.
	return s;
}