#pragma once

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::string> Rule;
typedef std::vector<Rule> Rule_collection;
typedef std::map<std::string, Rule_collection> Grammar;

Grammar read_grammar(std::istream&);
bool bracketed(const std::string&);
int nrand(int);
void gen_aux(const Grammar&, const std::string&, 
	std::vector<std::string>&et);
std::vector<std::string> gen_sentence(const Grammar& g);
int gen_sentence_main();
int count();