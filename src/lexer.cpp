#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <lexer.h>
#include <unordered_map>

const std::unordered_map<std::string, TokenType> tokenMap = {
    {"(", TokenType::OpenParen},
    {")", TokenType::CloseParen},
    {"{", TokenType::OpenBrace},
    {"}", TokenType::CloseBrace},
    {"=", TokenType::OpEquals},
    {"+=", TokenType::OpAddEquals},
    {"-=", TokenType::OpSubEquals},
    {"*=", TokenType::OpMulEquals},
    {"/=", TokenType::OpDivEquals},
    {"<=", TokenType::OpLessEquals},
    {">=", TokenType::OpGreaterEquals},
    {">>", TokenType::OpShiftRight},
    {"<<", TokenType::OpShiftLeft},
    {"++", TokenType::Increment},
    {"--", TokenType::Decrement},
    {"^=", TokenType::BitwiseXorEquals},
    {"|=", TokenType::BitwiseOrEquals},
    {"&=", TokenType::BitwiseAndEquals},
    {"!=", TokenType::OpNotEquals},
    {"&&", TokenType::OpAndCmp},
    {"||", TokenType::OpOrCmp},
    {"==", TokenType::OpEqualsCmp},
    {"=>", TokenType::OpLambda},
    {"^", TokenType::BitwiseXor},
    {"&", TokenType::BitwiseAnd},
    {"|", TokenType::BitwiseOr},
    {"~", TokenType::BitwiseNot},
    {"+", TokenType::BinOpAdd},
    {"-", TokenType::BinOpSub},
    {"*", TokenType::BinOpMul},
    {"/", TokenType::BinOpDiv},
    {"%", TokenType::OpModulus},
    {";", TokenType::Semicolon},
    {"<", TokenType::OpLess},
    {">", TokenType::OpGreater},
    {",", TokenType::Comma},
    {"?", TokenType::OpQuestion},
    {":", TokenType::OpColon},
};

const std::unordered_map<std::string, TokenType> keywords = {
    {"let", TokenType::Let},
    {"func", TokenType::KeywordFunc},
    {"return", TokenType::KeywordReturn},
    {"if", TokenType::KeywordIf},
    {"else", TokenType::KeywordElse},
    {"while", TokenType::KeywordWhile},
    {"for", TokenType::KeywordFor},
    {"break", TokenType::KeywordBreak},
    {"continue", TokenType::KeywordContinue},
    {"sbyte", TokenType::Int8},
    {"byte", TokenType::UInt8},
    {"short", TokenType::Int16},
    {"ushort", TokenType::UInt16},
    {"int", TokenType::Int32},
    {"uint", TokenType::UInt32},
    {"long", TokenType::Int64},
    {"ulong", TokenType::UInt64},
    {"float", TokenType::Float},
    {"double", TokenType::Double},
    {"string", TokenType::String},
    {"char", TokenType::Char},
    {"void", TokenType::Void},
    {"attr", TokenType::KeywordAttribute},
    {"class", TokenType::KeywordClass},
    {"namespace", TokenType::KeywordNamespace},
    {"struct", TokenType::KeywordStruct},
    {"as", TokenType::KeywordAs},
    {"define", TokenType::KeywordDefine},
    {"import", TokenType::KeywordImport},
    {"from", TokenType::KeywordFrom},
};

std::vector<std::string> splitString(const std::string &sourceCode) {
    std::vector<std::string> words;
    std::string word;
    bool inString = false;

    for (size_t i = 0; i < sourceCode.size(); ++i) {
        char ch = sourceCode[i];

        // Handle string literals
        if (ch == '"') {
            if (inString) {
                // Closing quote
                word += ch;
                words.push_back(word); // Push the entire string
                word.clear();
                inString = false;
            } else {
                if (!word.empty()) {
                    words.push_back(word); // Push the current token
                    word.clear();
                }
                word += ch; // Opening quote
                inString = true;
            }
            continue;
        }

        // Inside a string, add everything including spaces
        if (inString) {
            word += ch;
            continue;
        }

        // Handle alphanumeric characters
        if (isalnum(ch)) {
            word += ch;
        } else {
            // Push the current word if it's not empty
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }

            // Handle multi-character symbols
            if (i + 1 < sourceCode.size()) {
                std::string next = std::string(1, ch) + sourceCode[i + 1];
                if (next == "<=" || next == ">=" || 
                    next == "==" || next == "!=" || 
                    next == "+=" || next == "-=" || 
                    next == "*=" || next == "/=" || 
                    next == "&&" || next == "||" || 
                    next == ">>" || next == "<<" ||
                    next == "++" || next == "--" ||
                    next == "^=" || next == "|=" ||
                    next == "&=" || next == "=>") {
                    words.push_back(next);
                    ++i; // Skip the next character
                    continue;
                }
            }

            // Handle single-character symbols
            if (!isspace(ch)) {
                words.push_back(std::string(1, ch));
            }
        }
    }

    // Push the last word if any
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}





bool isNumber(const std::string &word) {
    return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
}

bool isAlpha(const std::string &word) {
    return !word.empty() && std::all_of(word.begin(), word.end(), ::isalpha);
}

bool isSkippable(char ch) {
    return isspace(ch);
}

std::string shift(std::vector<std::string> &sourceCode) {
    std::string word;
    if (!sourceCode.empty()) {
        word = sourceCode.front();
        sourceCode.erase(sourceCode.begin());
    }
    return word;
}

std::vector<Token> processString(std::vector<std::string> &sourceCode) {
    std::vector<Token> tokens;

    if (!sourceCode.empty()) {
        std::string token = shift(sourceCode);

        // Ensure the token starts and ends with quotes
        if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
            // Remove quotes for the token value
            token = token.substr(1, token.size() - 2);
            tokens.push_back({token, TokenType::StringLiteral});
        } else {
            std::cerr << "Error: Invalid string literal: " << token << std::endl;
            std::exit(1);
        }
    }

    return tokens;
}


std::vector<Token> processChar(std::vector<std::string> &sourceCode) {
    if (sourceCode.empty()) {
        std::cerr << "Error: Unterminated character literal" << std::endl;
        std::exit(1);
    }

    std::string str = shift(sourceCode);
    if (str.size() != 1) {
        std::cerr << "Error: Invalid character literal" << std::endl;
        std::exit(1);
    }

    if (sourceCode.empty() || sourceCode.front() != "'") {
        std::cerr << "Error: Unterminated character literal" << std::endl;
        std::exit(1);
    }

    shift(sourceCode); // Consume closing quote
    return {{str, TokenType::CharLiteral}};
}



std::vector<Token> tokenize(const std::string &sourceCode) {
    std::vector<Token> tokens;
    std::vector<std::string> src = splitString(sourceCode);

    while (!src.empty()) {
        std::string current = src.front();

        if (current == "//") {
            while (!src.empty() && src.front() != "\n") {
                shift(src);
            }
            continue;
        } else if (current == "/*") {
            while (!src.empty()) {
                if (src.front() == "*/") {
                    shift(src);
                    break;
                }
                shift(src);
            }
            continue;
        }

        if (isNumber(current)) {
            std::string number;
            
            while (!src.empty() && isNumber(src.front()))
                number += shift(src);

            tokens.push_back({number, TokenType::NumberLiteral});
        } 
        else if (!src.empty() && src.front().front() == '"' && src.front().back() == '"') {
            std::string token = shift(src);
            // Remove quotes and add as a string literal
            tokens.push_back({token.substr(1, token.size() - 2), TokenType::StringLiteral});
        }
        else if (current == "'") {
            shift(src); // Consume the opening quote
            auto charTokens = processChar(src);
            tokens.insert(tokens.end(), charTokens.begin(), charTokens.end());
        }
        else if (isAlpha(current)) {
            std::string ident = shift(src);

            if (keywords.find(ident) != keywords.end()) {
                tokens.push_back({ident, keywords.at(ident)});
            } else {
                tokens.push_back({ident, TokenType::Identifier});
            }
        } 
        else if (isSkippable(current[0]))
            shift(src);
        else {
            auto it = tokenMap.find(current);

            if (it != tokenMap.end()) 
                tokens.push_back({shift(src), it->second});
            else 
            {
                // Fallback for unrecognized tokens
                std::cerr << "Unrecognized token: " << current << std::endl;
                shift(src); // Remove the unrecognized token to avoid infinite loop
            }
        }
    }

    return tokens;
}
