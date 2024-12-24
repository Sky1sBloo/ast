#include "VariableHandler.hpp"

VariableHandler::VariableHandler(std::shared_ptr<ProgramMemory> memory)
    : _variables()
    , _memory(memory)
{
    allocateStackFrame();
}

void VariableHandler::allocate(const std::string& id, const std::string& value)
{
    if (_variables.front().contains(id)) {
        throw BadVariableHandling("Tried to allocate on existing variable");
    }
    _variables.front().insert({ id, _memory->allocate(value) });
}

void VariableHandler::allocate(const std::string& id, const MemoryCell& cell)
{
    if (_variables.front().contains(id)) {
        throw BadVariableHandling("Tried to allocate on existing variable");
    }
    _variables.front().insert({ id, _memory->allocate(cell) });
}

void VariableHandler::deallocate(const std::string& id)
{
    if (!_variables.front().contains(id)) {
        throw BadVariableHandling("Tried to deallocate nonexistent variable");
    }
    _memory->deallocate(_variables.front().at(id));
}
const MemoryCell& VariableHandler::getValue(const std::string& id) const
{
    for (const auto& varMap : _variables) {
        if (varMap.contains(id)) {
            return _memory->retrieve(varMap.at(id));
        }
    }
    const std::string message = "Tried to access non existing variable of type: " + id;
    throw BadVariableHandling(message.c_str());
}

void VariableHandler::setValue(const std::string& id, const std::string& value)
{
    for (auto& varMap : _variables) {
        if (varMap.contains(id)) {
            _memory->set(varMap.at(id), value);
            return;
        }
    }
    throw BadVariableHandling("Tried to set nonexisting variable");
}

void VariableHandler::setValue(const std::string& id, const MemoryCell& cell)
{
    for (auto& varMap : _variables) {
        if (varMap.contains(id)) {
            _memory->set(varMap.at(id), cell);
            return;
        }
    }
    throw BadVariableHandling("Tried to set nonexisting variable");
}
