/*
** EPITECH PROJECT, 2024
** bsarcarde
** File description:
** CLibEncapsulation
*/

#include "DlLoader/CLibEncapsulation.hpp"

/**
 * @brief Construct a new CLibEncapsulation object.
 */
CLibEncapsulation::CLibEncapsulation()
{
}

/**
 * @brief Construct a new CLibEncapsulation object and open the library.
 * @param libPath The path to the library.
 */
CLibEncapsulation::CLibEncapsulation(std::string &libPath)
{
    this->libPath = libPath;
    this->openLib(libPath);
}

/**
 * @brief Destroy the CLibEncapsulation object and close the library.
 */
CLibEncapsulation::~CLibEncapsulation()
{
    if (this->isLibOpen)
        this->closeLib();
}

/**
 * @brief Open a library.right
 * @param libPath The path to the library.
 */
void CLibEncapsulation::openLib(std::string const libPath)
{
    if (this->isLibOpen)
        this->closeLib();
    this->lib = dlopen(libPath.c_str(), RTLD_LAZY | RTLD_NODELETE);
    if (!this->lib)
        throw LibException(dlerror());
    this->isLibOpen = true;
}

/**
 * @brief Close the library.
 */
void CLibEncapsulation::closeLib()
{
    if (this->isLibOpen) {
        dlclose(this->lib);
        this->isLibOpen = false;
    }
}

/**
 * @brief Get the library.
 * @return void* The library.
 */
void *CLibEncapsulation::getLib()
{
    return this->lib;
}


/**
 * @brief get last error
 * @return the last error
 */
std::string CLibEncapsulation::getError()
{
    return this->_error;
}

/*
 * @brief Set an error message.
 */
void CLibEncapsulation::setError(std::string const &error)
{
    this->_error = error;
    this->failed = true;
}

/**
 * @brief Get a function from the library.
 * @param functionName The name of the function to get.
 * @return void* The function.
 */
void *CLibEncapsulation::getFunction(std::string const &functionName)
{
    void *function = dlsym(this->lib, functionName.c_str());
    if (!function)
        throw LibException(dlerror());
    return function;
}
