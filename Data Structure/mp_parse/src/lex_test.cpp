/**
 * @file lex_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <iostream>
#include <string>
#include "lex.h"
#include "number.h"
#include "operation.h"

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
            while (!tokens.empty())
            {
                const auto& tok = tokens.front();
                switch (tok->type())
                {
                    case token_type::TEXT:
                        std::cout << "text(" << tok->text() << ") ";
                        break;
                    case token_type::NUMBER:
                        std::cout << "num(" << tok->as_number()->value()
                                  << ") ";
                        break;
                    case token_type::OPERATION:
                        std::cout << "op(" << tok->text() << ") ";
                        break;
                }
                tokens.pop();
            }
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << "exception: " << ex.what();
        }
        std::cout << "\n> ";
    }
}
