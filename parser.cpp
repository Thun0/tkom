#include "parser.h"
#include "output.h"

void Parser::parse()
{
    char c = fgetc(input_file);
    while((c != EOF))
    {
        std::string str;
        Type token = lexer->get_token(c, str);
        start_symbol(token, c, str);
    }
    print_log("End of file\n");
    print_log("Finished\n");
}

void Parser::check_next_token(Type token, char& c, std::string& str)
{
    Type read_token = lexer->get_token(c, str);
    if(read_token == HEX_OR_INSTRUCTION && (token == HEX || token == INSTRUCTION))
        return;
    if(read_token == DEC && token == HEX)
        return;
    if(read_token != token)
    {
        print_fatal("Syntax error: expected %s but got %s which is %s\n", type_to_string(token), str.c_str(), type_to_string(read_token));
    }
}

Type Parser::y_symbol(char& c, std::string& str)
{
    Type token = lexer->get_token(c, str);
    if(token == HASH)
    {
        token = lexer->get_token(c, str);
        if(token == MINUS)
        {
            token = lexer->get_token(c, str);
        }
        if(token != DEC && token != HEX)
            print_fatal("Syntax error: expected hex or dec but got %s\n", str.c_str());    
    }
    else if(token == REGISTER)
    {
        token = lexer->get_token(c, str);
        if(token == RIGHT_SQ_BRACKET)
            return token;
        if(token == COMMA)
        {
            check_next_token(INSTRUCTION, c, str);
            check_next_token(WHITESPACE, c, str);
            check_next_token(HASH, c, str);
            check_next_token(DEC, c, str);
        }
        else
            print_fatal("Syntax error: expected ']' or ',' but got %s\n", str.c_str());
    }
    else
        print_fatal("Syntax error: expected hash or register but got %s\n", str.c_str());
    return lexer->get_token(c, str);
}

void Parser::z_symbol(char& c, std::string& str)
{
    check_next_token(WHITESPACE, c, str);
    Type token = lexer->get_token(c, str);
    if(token == LESS_THAN)
    {
        check_next_token(STRING, c, str);
        check_next_token(AT, c, str);
        token = lexer->get_token(c, str);
        if(token == AT)
        {
            token = lexer->get_token(c, str);
        }
        x_symbol(token, c, str);
    }
    else if(token == SEMICOLON)
    {
        check_next_token(WHITESPACE, c, str);
        check_next_token(STRING, c, str);
    }
}

Type Parser::operands_symbol(char& c, std::string& str)
{
    Type token = lexer->get_token(c, str);
    for(int i = 0; i < 4; ++i)
    {
        if(token == REGISTER)
        {
            token = lexer->get_token(c, str);
        }
        else if(token == HASH)
        {
            token = lexer->get_token(c, str);
            if(token == MINUS)
                token = lexer->get_token(c, str);
            if(token != DEC && token != HEX)
                print_fatal("Syntax error: expected hex or dec but got %s\n", str.c_str());
            token = lexer->get_token(c, str);
        }
        else if(token == LEFT_SQ_BRACKET)
        {
            check_next_token(REGISTER, c, str);
            token = lexer->get_token(c, str);
            if(token == COMMA)
            {
                token = y_symbol(c, str);
            }
            if(token != RIGHT_SQ_BRACKET)
                print_fatal("Syntax error: expected ',' or ']' but got %s\n", str.c_str());
            token = lexer->get_token(c, str);
            if(token == EXCLAMATION)
                token = lexer->get_token(c, str);
        }
        else if(token == HEX || token == DEC)
        {
            z_symbol(c, str);
            token = lexer->get_token(c, str);
        }
        else if(token == STRING || token == CONDITION)
        {
            token = lexer->get_token(c, str);
        }
        else if(token == INSTRUCTION)
        {
            token = lexer->get_token(c, str);
            if(token == NEWLINE)
                return token;
            if(token != WHITESPACE)
                print_fatal("Syntax error: expected WHITESPACE but got %s\n", str.c_str());
            check_next_token(HASH, c, str);
            check_next_token(DEC, c, str);
            token = lexer->get_token(c, str);   
        }
        else
            break;
        if(token == COMMA)
        {
            token = lexer->get_token(c, str);
            if(token == WHITESPACE)
                token = lexer->get_token(c, str);
        }
    }
    return token;
}

void Parser::comment_symbol(char& c, std::string& str)
{
    Type token = lexer->get_token(c, str);
    if(token == DOUBLE_SLASH)
    {
        check_next_token(WHITESPACE, c, str);
        check_next_token(HASH, c, str);
        token = lexer->get_token(c, str);
        if(token == MINUS)
            check_next_token(DEC, c, str);
        else if(token != DEC)
            print_fatal("Syntax error: expected DEC in comment but got %s\n", str.c_str());
    }
    else if(token == SEMICOLON)
    {
        check_next_token(WHITESPACE, c, str);
        check_next_token(STRING, c, str);
    }
    else
    {
        print_fatal("Syntax error: expected comment but got %s\n", str.c_str());
    }
}

Type Parser::instruction_symbol(char& c, std::string& str)
{
    check_next_token(INSTRUCTION, c, str);
    Type token = lexer->get_token(c, str);
    if(token == WHITESPACE)
        return operands_symbol(c, str);
    else
        return token;
}

void Parser::x_symbol(Type token, char& c, std::string& str)
{
    if(token != STRING)
        print_fatal("Syntax error: expected string but got %s\n", str.c_str());
    token = lexer->get_token(c, str);
    if(token == MINUS || token == PLUS)
    {
        check_next_token(HEX, c, str);
        check_next_token(MORE_THAN, c, str);
    }
    else if(token != MORE_THAN)
    {
        print_fatal("Syntax error: expected '>' but got %s which is %s\n", str.c_str(), type_to_string(token));
    }
}

void Parser::start_symbol(Type token, char& c, std::string& str)
{
    if(token == HEX || token == DEC)
    {
        check_next_token(WHITESPACE, c, str);
        check_next_token(LESS_THAN, c, str);
        check_next_token(STRING, c, str);
        check_next_token(AT, c, str);
        token = lexer->get_token(c, str);
        if(token == AT)
        {
            token = lexer->get_token(c, str);
        }
        x_symbol(token, c, str);
        check_next_token(COLON, c, str);
        check_next_token(NEWLINE, c, str);
    }
    else if(token == WHITESPACE)
    {
        check_next_token(HEX, c, str);
        check_next_token(COLON, c, str);
        check_next_token(WHITESPACE, c, str);
        check_next_token(HEX, c, str);
        check_next_token(WHITESPACE, c, str);
        token = instruction_symbol(c, str);
        if(token == WHITESPACE)
        {
            comment_symbol(c, str);
            check_next_token(NEWLINE, c, str);
        }
        else if(token != NEWLINE)
        {
            print_fatal("Syntax error: expected newline after instruction, got: %s\n", str.c_str());       
        }
    }
    else if(token != NEWLINE)
    {
        print_fatal("Syntax error: expected starting symbol, got: %s\n", str.c_str());
    }
    printf("Syntax accepted, back to starting symbol\n");
}

void Parser::open_file(char* filepath)
{
    input_file = fopen(filepath, "r");
    if(input_file == NULL)
    {
        print_fatal("Error while reading file: %s\n", filepath);
    }
    print_log("File \"%s\" opened\n", filepath);
}

Parser::Parser(char* filepath)
{
    open_file(filepath);
    lexer = new Lexer(input_file);
}

Parser::~Parser()
{
    delete lexer;
}