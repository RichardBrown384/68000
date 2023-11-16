#include <gtest/gtest.h>

#include "M68000/M68000.h"
#include "Mocks.h"

struct TestData;

class TestFixture : public testing::TestWithParam<TestData> {
public:
    TestFixture();
    auto Given(const struct Given&) -> void;
    auto When(const std::vector<std::string>&, uint32_t, uint32_t) -> void;
    auto Then(const struct Then&) -> void;
public:
    InterruptsMock interrupts;
    MemoryMock memory;
    ObserverMock observer;
    rbrown::m68000::M68000 m68000;
};