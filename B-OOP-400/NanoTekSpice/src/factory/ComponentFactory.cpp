/*
** EPITECH PROJECT, 2024
** ComponentFactory
** File description:
** ComponentFactory
*/

#include <fstream>
#include "ComponentFactory.hpp"

ComponentFactory::ComponentFactory()
{
    this->_creationMap["input"] = []() {return std::make_shared<InputComponent>();};
    this->_creationMap["output"] = []() {return std::make_shared<OutputComponent>();};
    this->_creationMap["true"] = []() {return std::make_shared<TrueComponent>();};;
    this->_creationMap["false"] = []() {return std::make_shared<FalseComponent>();};
    this->_creationMap["clock"] = []() {return std::make_shared<ClockComponent>();};
    this->_creationMap["nand"] = []() {return std::make_shared<NandComponent>();};
}

ComponentFactory::ComponentFactory(const ComponentFactory &obj)
{
    this->_creationMap = obj._creationMap;
}

ComponentFactory::~ComponentFactory()
{
}

bool ComponentFactory::isMappedComponent(const std::string &type)
{
    auto key = this->_creationMap.find(type);
    if (key != this->_creationMap.end())
        return true;
    return false;
}

std::shared_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &type)
{
    if (this->isMappedComponent(type) == false)
        throw ComponentFactory::FactoryError("Don't try to create invalid component ;)");
    return this->_creationMap[type]();
}

std::unordered_map<std::string, std::function<std::shared_ptr<nts::IComponent>()>> ComponentFactory::getMap() const
{
    return this->_creationMap;
}

ComponentFactory &ComponentFactory::operator=(const ComponentFactory &obj)
{
    if (this == &obj)
        return *this;
    this->_creationMap = obj._creationMap;
    return *this;
}
