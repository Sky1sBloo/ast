#pragma once
#include <string>
#include <variant>

/**
 * Class that will be stored in ProgramMemory
 * Can deduce types based on string
 */
class MemoryCell {
public:
    MemoryCell(const std::string& value);

private:
    std::variant<int, float, bool, std::string> _value;

    /**
     * Deduces the type based on string and sets it to _value
     */
    void typeDeducer(const std::string& value);

    /**
     * Converts string to Float
     * If successful, sets it to _value
     *
     * @return If operation is success
     */
    bool strToFloat(const std::string& value);

    /**
     * Converts string to int
     * If successful, sets it to _value
     *
     * @return If operation is successful
    */
    bool strToInt(const std::string& value);

    /**
     * Converts string to bool
     * If successful, sets it to _value
     *
     * @return If operation is success
     */
    bool strToBool(const std::string& value);
};
