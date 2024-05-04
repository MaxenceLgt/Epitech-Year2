/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <Shell.hpp>
#include <new>
#include <unordered_map>

Test(parsingFile, InvalidFile) {
    std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> map;
    std::unordered_map<std::string, std::size_t> linkIndex;
    Parsing parsing;
    std::string fileName = "tests/invalid_file.nts";
    cr_assert_throw(parsing.parsingFile(fileName, map, linkIndex), Parsing::ParsingError);
}

Test(parsingFile, ValidFileWithoutComponents) {
    std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> map;
    std::unordered_map<std::string, std::size_t> linkIndex;
    Parsing parsing;
    std::string fileName = "tests/invalid_test_no_components.nts";
    cr_assert_throw(parsing.parsingFile(fileName, map, linkIndex), Parsing::ParsingError);
    cr_assert(map.empty());
}

Test(parsingFile, BadLineInFile) {
    std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> map;
    std::unordered_map<std::string, std::size_t> linkIndex;
    Parsing parsing;
    std::string fileName = "tests/invalid_test_bad_line.nts";
    cr_assert_throw(parsing.parsingFile(fileName, map, linkIndex), Parsing::ParsingError);
}

Test(parsingFile, ValidFile_xor) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/xor_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_or) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/or_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_not) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/not_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_gate_nor) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/4001_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_gate_or) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/4071_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_gate_xor) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/4030_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}

Test(parsingFile, ValidFile_gate_and) {
    CircuitComponent circuit;
    Parsing parsing;
    std::string fileName = "tests/4081_config.nts";

    try {
        circuit.fillCircuitComponent(fileName);
        cr_expect(true);
    } catch (...) {
        cr_assert_fail("parsingFile should not throw an exception");
    }
}