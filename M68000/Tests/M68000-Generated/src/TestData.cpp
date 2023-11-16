#include <nlohmann/json.hpp>
#include <fstream>
#include "TestData.h"

void from_json(const nlohmann::json& j, StatusRegister& statusRegister) {
    statusRegister.t = j.at("t");
    statusRegister.s = j.at("s");
    statusRegister.interrupt_mask = j.at("interrupt_mask");
    statusRegister.x = j.at("x");
    statusRegister.n = j.at("n");
    statusRegister.z = j.at("z");
    statusRegister.v = j.at("v");
    statusRegister.c = j.at("c");
}

void from_json(const nlohmann::json& j, Given& given) {
    given.status_register = j.at("status_register");
    given.pc = j.at("pc");
    given.d = j.at("d");
    given.a = j.at("a");
    given.memory = j.at("memory");
    given.usp = j.at("usp");
    given.ssp = j.at("ssp");
    given.stopped = j.at("stopped");
}

void from_json(const nlohmann::json& j, Then& then) {
    then.status_register = j.at("status_register");
    then.pc = j.at("pc");
    then.d = j.at("d");
    then.a = j.at("a");
    then.memory = j.at("memory");
    then.cycles = j.at("cycles");
    then.usp = j.at("usp");
    then.ssp = j.at("ssp");
    then.stopped = j.at("stopped");
}

void from_json(const nlohmann::json& j, TestData& data) {
    data.given = j.at("given");
    data.when = j.at("when");
    data.then = j.at("then");
}

std::vector<TestData> GetTests(const std::string& path) {
    std::ifstream input(path);
    return nlohmann::json::parse(input);
}