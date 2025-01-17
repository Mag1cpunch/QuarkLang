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
    Equals,
    AddEquals,
    SubEquals,
    MulEquals,
    DivEquals,
    Lambda,
    Increment,
    Decrement,

    // comparison operators
    Less,
    Greater,
    LessEquals,
    GreaterEquals,
    AndCmp,
    OrCmp,
    XorCmp,
    NotEquals,
    EqualsCmp,
    Question,
    Colon,

    // arithmetical operators
    LogicalNot,
    Modulus,

    // shift operators
    ShiftRight,
    ShiftLeft,

    // binary operators
    BinAdd,
    BinSub,
    BinMul,
    BinDiv,

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
    Pointer,
};

struct Token {
    std::string value;
    TokenType type;
};

std::vector<Token> tokenize(const std::string &sourceCode);