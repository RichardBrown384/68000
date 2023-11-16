#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>
#include <vector>

struct StatusRegister {
    bool t{};
    bool s{};
    uint32_t interrupt_mask{};
    bool x{};
    bool n{};
    bool z{};
    bool v{};
    bool c{};
};

struct Given {
    StatusRegister status_register{};
    uint32_t pc{};
    std::unordered_map<std::string, uint32_t> d{};
    std::unordered_map<std::string, uint32_t> a{};
    std::unordered_map<std::string, uint8_t> memory{};
    uint32_t usp{};
    uint32_t ssp{};
    bool stopped{};
};

struct Then {
    StatusRegister status_register{};
    uint32_t pc{};
    std::unordered_map<std::string, uint32_t> d{};
    std::unordered_map<std::string, uint32_t> a{};
    std::unordered_map<std::string, uint8_t> memory{};
    uint32_t cycles{};
    uint32_t usp{};
    uint32_t ssp{};
    bool stopped{};
};

struct TestData {
    Given given;
    std::vector<std::string> when;
    Then then;
};

std::vector<TestData> GetTests(const std::string&);