#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ProgramMemory.hpp"

/**
 * Class designed for allocation and deallocation of variables
 * This also holds variable id and address information for easy data retrieval
 */
class VariableHandler {
public:
    VariableHandler(std::shared_ptr<ProgramMemory> programMemory);

    /**
     * Allocates a new variable in memory and adds it in the variables map
     *
     * Throws BadVariableHandling on fail
     */
    void allocate(const std::string& id, const std::string& value = "NULL");

    /**
     * Retrieves value of allocated variable
     *
     * Throws BadVariableHandling on fail
    */
    const std::string& getValue(const std::string& id) const;

    /**
     * Sets the value of the allocated variable
     *
     * Throws BadVariableHandling on fail
    */
    void setValue(const std::string& id, const std::string& value);

private:
    std::unordered_map<std::string, int> _variables;
    std::shared_ptr<ProgramMemory> _memory;
};

class BadVariableHandling : public std::runtime_error {
public:
    BadVariableHandling(const char what[])
        : std::runtime_error(what)
    {
    }
};
