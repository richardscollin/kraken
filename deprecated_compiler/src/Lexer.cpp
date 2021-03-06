#include "Lexer.h"
#include <cassert>

Lexer::Lexer() {
	//Do nothing
	currentPosition = 0;
}

Lexer::Lexer(std::string inputString) {
	input = inputString;
	currentPosition = 0;
}

Lexer::~Lexer() {
	//No cleanup necessary
}

void Lexer::setInput(std::string inputString) {
	input = inputString;
}

void Lexer::addRegEx(std::string regExString) {
	regExs.push_back(new RegEx(regExString));
}

Symbol Lexer::next() {
	//std::cout << "Current at is \"" << input.substr(currentPosition) << "\" currentPos is " << currentPosition  << " out of " << input.length() <<std::endl;
	//If we're at the end, return an eof
	if (currentPosition >= input.length())
		return Symbol("$EOF$", true);
	int longestMatch = -1;
	RegEx* longestRegEx = NULL;
	std::string remainingString = input.substr(currentPosition);
	for (std::vector<RegEx*>::size_type i = 0; i < regExs.size(); i++) {
		//std::cout << "Trying regex " << regExs[i]->getPattern() << std::endl;
		int currentMatch = regExs[i]->longMatch(remainingString);
		if (currentMatch > longestMatch) {
			longestMatch = currentMatch;
			longestRegEx = regExs[i];
		}
	}
	if (longestRegEx != NULL) {
		std::string eatenString = input.substr(currentPosition, longestMatch);
		currentPosition += longestMatch;
	//std::cout << "Current at is \"" << input.substr(currentPosition) << "\" currentPos is " << currentPosition <<std::endl;
		return Symbol(longestRegEx->getPattern(), true, eatenString);
	} else {
		// std::cout << "Found no applicable regex" << std::endl;
		// std::cout << "Remaining is ||" << input.substr(currentPosition) << "||" << std::endl;
		return Symbol("$INVALID$", true);
	}
}

void Lexer::test() {
    Symbol s;
    {
        Lexer lex;
        lex.addRegEx("b");
        lex.setInput("bb");
        s = lex.next();
        assert(s.getName() == "b" && s.getValue() == "b");
        s = lex.next();
        assert(s.getName() == "b" && s.getValue() == "b");
        assert(lex.next() == Symbol("$EOF$", true));
    }

    {
        Lexer lex;
        lex.addRegEx("a*");
        lex.addRegEx("b");
        lex.setInput("aaabaabb");
        s = lex.next();
        assert(s.getName() == "a*" && s.getValue() == "aaa");
        s = lex.next();
        assert(s.getName() == "b" && s.getValue() == "b");
        s = lex.next();
        assert(s.getName() == "a*" && s.getValue() == "aa");
        s = lex.next();
        assert(s.getName() == "b" && s.getValue() == "b");
        s = lex.next();
        assert(s.getName() == "b" && s.getValue() == "b");
        assert(lex.next() == Symbol("$EOF$", true));
    }

    // Test a lexer error condition.
    {
        Lexer lex;
        lex.addRegEx("a|b");
        lex.setInput("blah");
        s = lex.next();
        assert(s.getName() == "a|b" && s.getValue() == "b");
        assert(lex.next() == Symbol("$INVALID$", true));
    }

    // Lexer can consume all the input at once.
    {
        Lexer lex;
        lex.addRegEx("xyzzy");
        lex.setInput("xyzzy");
        s = lex.next();
        assert(s.getName() == "xyzzy" && s.getValue() == "xyzzy");
        assert(lex.next() == Symbol("$EOF$", true));
    }

    // Lexer produces the longest match, not the first.
    {
        Lexer lex;
        lex.addRegEx("int");
        lex.addRegEx("(i|n|t|e)+");
        lex.setInput("intent");
        s = lex.next();
        assert(s.getName() == "(i|n|t|e)+" && s.getValue() == "intent");
    }

    std::cout << "Lexer tests passed\n";
}

void Lexer::reset() {
    currentPosition = 0;
}
