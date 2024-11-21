#pragma once
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Base class for tokens
 */
class Token {
public:
    enum class MainTypes {
        INVALID,
        VALUE,
        TERMINAL
    };

    enum class SubTypes {
        ANY, // Used for checking parser ruleset and comparison. Ignores subtypes and only checks for maintype
        INVALID,
        LITERAL,
        KEYWORD,
        IDENTIFIER,
        OPERATOR,
        ASSIGN,
        STATEMENT_TERMINATE
    };

public:
    Token(MainTypes newType, SubTypes newSubType, const std::string& newValue = "")
        : _mainType(newType)
        , _subType(newSubType)
        , _value(newValue)
    {
        if (_mainType == MainTypes::TERMINAL) {
            if (!_terminalSubTypes.contains(_subType)) {
                throw std::invalid_argument("Tried to initialize invalid subtype on Terminal Token");
            }
        } else if (_mainType == MainTypes::VALUE) {
            if (!_valueSubTypes.contains(_subType)) {
                throw std::invalid_argument("Tried to initialize invalid subtype on Value Token");
            }
        }
    }

    /**
     * Constructor with main type identification
     */
    Token(SubTypes newSubType, const std::string& newValue = "")
        : _mainType(MainTypes::INVALID)
        , _subType(newSubType)
        , _value(newValue)
    {
        if (newSubType == SubTypes::ANY) {
            throw std::invalid_argument("Tried to defer main type from subtype ANY in Token");
        }
        if (_terminalSubTypes.contains(newSubType)) {
            _mainType = MainTypes::TERMINAL;
        } else if (_valueSubTypes.contains(newSubType)) {
            _mainType = MainTypes::VALUE;
        }
    }

    MainTypes getMainType() const { return _mainType; }
    SubTypes getSubType() const { return _subType; }
    const std::string& getValue() const { return _value; }

    int getPrecedence() const
    {
        if (_mainType != MainTypes::TERMINAL) {
            throw std::runtime_error("Tried to access precedence of token of non terminal type");
        }
        return _precedenceTokens.at(_subType);
    }

    /**
     * Comparison operator with SubType any logic
     */
    friend bool operator==(const Token& lhs, const Token& rhs)
    {
        if (lhs._mainType != rhs._mainType) {
            return false;
        }
        if (lhs._subType == SubTypes::ANY || rhs._subType == SubTypes::ANY) {
            return true;
        }
        if (lhs._subType == rhs._subType) {
            return true;
        }
        return false;
    }

private:
    MainTypes _mainType;
    SubTypes _subType;
    std::string _value;

    inline const static std::unordered_set<SubTypes> _valueSubTypes = {
        SubTypes::ANY,
        SubTypes::IDENTIFIER,
        SubTypes::LITERAL
    };

    inline const static std::unordered_set<SubTypes> _terminalSubTypes = {
        SubTypes::ANY,
        SubTypes::ASSIGN,
        SubTypes::KEYWORD,
        SubTypes::OPERATOR,
    };

    inline const static std::unordered_map<SubTypes, int> _precedenceTokens = {
        { SubTypes::ASSIGN, 0 },
        { SubTypes::KEYWORD, 1 },
        { SubTypes::OPERATOR, 2 }
    };

    bool isValidSubType(SubTypes type) const
    {
        if (_mainType == MainTypes::VALUE) {
            return _valueSubTypes.contains(type);
        } else if (_mainType == MainTypes::TERMINAL) {
            return _terminalSubTypes.contains(type);
        }
        return false;
    }
};
