/**
 * @file lex.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cstdint>
#include "lex.h"
#include "number.h"
#include "operation.h"

namespace cs225
{

queue<std::unique_ptr<token>> lex(const std::string& line)
{
    queue<std::unique_ptr<token>> tokens;

    token_type prev = token_type::TEXT;
    std::string val;
    auto flush = [&]()
    {
        if (val.empty())
            return;
        tokens.push(make_token<number>(std::move(val)));
        prev = token_type::NUMBER;
    };

    for (uint64_t i = 0; i < line.length(); ++i)
    {
        switch (line[i])
        {
            case '*':
            case '/':
            case '^':
                flush();
                tokens.push(make_token<operation>(std::string{line[i]}));
                prev = token_type::OPERATION;
                break;
            case '-':
                flush();
                if (prev == token_type::NUMBER)
                {
                    // binary minus
                    tokens.push(make_token<operation>(std::string{line[i]}));
                }
                else
                {
                    // unary minus
                    tokens.push(make_token<operation>("~"));
                }
                prev = token_type::OPERATION;
                break;
            case '+':
                flush();
                if (prev == token_type::NUMBER)
                {
                    // binary plus
                    tokens.push(make_token<operation>(std::string{line[i]}));
                }
                else
                {
                    // unary plus
                    tokens.push(make_token<operation>("#"));
                }
                prev = token_type::OPERATION;
                break;
            case '(':
            case ')':
                flush();
                tokens.push(std::make_unique<token>(std::string{line[i]},
                                                    token_type::TEXT));
                prev = token_type::TEXT;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
            case ',':
                val += line[i];
                break;
            default:
                flush();
                // ignore whitespace
                if (std::isspace(line[i]))
                    continue;
                throw std::runtime_error{std::string{"invalid token: "} +
                                         line[i]};
        }
    }
    flush();

    return tokens;
}
}
