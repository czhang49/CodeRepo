/**
 * @file parse_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <iostream>
#include <string>
#include "lex.h"
#include "parser.h"

using namespace cs225;

int main()
{
    std::cout << "> ";
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            return 0;
        try
        {
            auto tokens = lex(line);
            auto root = parse(tokens);
            std::cout<<(root==nullptr)<<std::endl;
			std::cout << root->value();
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << ex.what();
        }
        std::cout << "\n> ";
    }
}
