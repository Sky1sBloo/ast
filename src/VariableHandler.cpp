#include "VariableHandler.hpp"

VariableHandler::VariableHandler(std::shared_ptr<ProgramMemory> memory)
    : _variables()
    , _memory(memory)
{
}

void VariableHandler::allocate(const std::string& id, const std::string& value)
{
    if (_variables.contains(id)) {
        throw BadVariableHandling("Tried to allocate on existing variable");
    }
    _variables.insert({ id, _memory->allocate(value) });
}

const std::string& VariableHandler::getValue(const std::string& id) const
{
    if (!_variables.contains(id)) {
        throw BadVariableHandling("Tried to access nonexisting variable");
    }
    return _memory->retrieve(_variables.at(id));
}

void VariableHandler::setValue(const std::string& id, const std::string& value)
{
    if (!_variables.contains(id)) {
        throw BadVariableHandling("Tried to set nonexisting variable");
    }
    _memory->set(_variables.at(id), value);
}
