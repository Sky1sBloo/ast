#include "VariableHandler.hpp"

VariableHandler::VariableHandler(std::shared_ptr<ProgramMemory> programMemory)
    : variables()
    , memory(programMemory)
{
}

void VariableHandler::allocate(const std::string& id, const std::string& value)
{
    if (variables.contains(id)) {
        throw BadVariableHandling("Tried to allocate on existing variable");
    }
    variables.insert({ id, memory->allocate(value) });
}

const std::string& VariableHandler::getValue(const std::string& id)
{
    if (!variables.contains(id)) {
        throw BadVariableHandling("Tried to access nonexisting variable");
    }
    return memory->retrieve(variables.at(id));
}
