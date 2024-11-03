#pragma once
#include <string>
#include <variant>

/**
 * Class that will be stored in ProgramMemory
 * Can deduce types based on string
 */
class MemoryCell {
public:
    using TypeVariants = std::variant<int, float, bool, std::string, std::monostate>;
    /**
     * Constructor for memory MemoryCell
     *
     * Empty string implies std::monostate
     */
    MemoryCell(const std::string& value = "");

    void set(const std::string& value = "");
    const TypeVariants& get() const { return _value; }

private:
    TypeVariants _value;

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
