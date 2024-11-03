#pragma once
#include <optional>
#include <string>
#include <variant>

#include "DataTypes.hpp"

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

    /**
     * Returns type of memory cell
     */
    DataType getType() const;

    /**
     * Gets the value on specified type
     */
    template <typename T>
    std::optional<T> getAs() const
    {
        if (auto ptr = std::get_if<T>(&_value)) {
            return *ptr;
        }
        return std::nullopt;
    }

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
