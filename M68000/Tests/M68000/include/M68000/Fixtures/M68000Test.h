#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>

#include <gtest/gtest.h>

class M68000Test: public ::testing::Test {
public:
    M68000Test();
    ~M68000Test() override;
    void Given(const std::initializer_list<const char*>&);
    void When(const std::initializer_list<const char*>&);
    void When(const std::initializer_list<uint32_t>&);
    void Then(const std::initializer_list<const char*>&);
    void Then(uint32_t);
private:
    void Apply(uint32_t, const std::vector<uint32_t>&);
    struct M68000TestImpl;
    std::unique_ptr<M68000TestImpl> impl;
};