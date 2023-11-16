#pragma once

#include <cstdint>
#include <string>
#include <initializer_list>
#include <memory>

#include <gtest/gtest.h>

class M68000Test: public ::testing::Test {
public:
    M68000Test();
    ~M68000Test() override;
    void Given(std::initializer_list<std::string>);
    void When(std::initializer_list<const char*>);
    void When(std::initializer_list<uint32_t>);
    void Then(std::initializer_list<std::string>);
private:
    void Apply(uint32_t, const std::vector<uint32_t>&);
    void Apply(const char*);
    void Expect(const char*);
    struct M68000TestImpl;
    std::unique_ptr<M68000TestImpl> impl;
};