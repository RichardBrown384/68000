#pragma once

#include <gtest/gtest.h>

class PositiveTest : public ::testing::TestWithParam<const char*> {};
class NegativeTest : public ::testing::TestWithParam<const char*> {};
