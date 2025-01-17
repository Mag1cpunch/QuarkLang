#pragma once

#include <string>
#include <vector>

enum TokenType {
    // literals
    NumberLiteral,
    FloatLiteral,
    StringLiteral,
    CharLiteral,

    // symbols
    OpenBrace,
    CloseBrace,
    Semicolon,
    Comma,
    OpenParen,
    CloseParen,

    // identifiers
    Identifier,
    Let,
    
    // assignment operators
    OpEquals,
    OpAddEquals,
    OpSubEquals,
    OpMulEquals,
    OpDivEquals,
    OpLambda,
    Increment,
    Decrement,

    // comparison operators
    OpLess,
    OpGreater,
    OpLessEquals,
    OpGreaterEquals,
    OpAndCmp,
    OpOrCmp,
    OpXorCmp,
    OpNotEquals,
    OpEqualsCmp,
    OpQuestion,
    OpColon,

    // arithmetical operators
    OpLogicalNot,
    OpModulus,

    // shift operators
    OpShiftRight,
    OpShiftLeft,

    // binary operators
    BinOpAdd,
    BinOpSub,
    BinOpMul,
    BinOpDiv,

    // bitwise operators
    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    BitwiseNot,
    BitwiseAndEquals,
    BitwiseOrEquals,
    BitwiseXorEquals,
    
    // keywords
    KeywordFunc,
    KeywordReturn,
    KeywordIf,
    KeywordElse,
    KeywordWhile,
    KeywordFor,
    KeywordBreak,
    KeywordContinue,
    KeywordAttribute,
    KeywordClass,
    KeywordNamespace,
    KeywordStruct,
    KeywordAs,
    KeywordDefine,
    KeywordImport,
    KeywordFrom,

    // data types
    Int8,
    Int16,
    Int32,
    Int64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Float,
    Double,
    String,
    Char,
    Void,

    // versatile operators
    OpPointer,
};

struct Token {
    std::string value;
    TokenType type;
};

std::vector<Token> tokenize(const std::string &sourceCode);