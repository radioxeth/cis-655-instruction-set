#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <vector>

class Parser {
private:

public: 

    std::vector<std::string> parse(std::ifstream &in);
};

#endif // PARSER_H