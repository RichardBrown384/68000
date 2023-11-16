#include <gtest/gtest.h>

#include "TestFixture.h"
#include "TestData.h"

std::string PrintToString(const TestData& test) {
    return test.when[0];
}

TEST_P(TestFixture, Test) {
    const auto& [given, when, then] = GetParam();
    Given(given);
    When(when, given.pc, then.pc);
    Then(then);
}

//#define SKIP_ARITHMETIC_TESTS
//#define SKIP_IMMEDIATE_TESTS
//#define SKIP_IMMEDIATE_QUICK_TESTS
//#define SKIP_BITWISE_TESTS
//#define SKIP_SHIFT_ROTATE_RIGHT_TESTS
//#define SKIP_SHIFT_ROTATE_LEFT_TESTS
//#define SKIP_SINGLE_OPERAND_TESTS
//#define SKIP_MULTIPRECISION_TESTS
//#define SKIP_CONDITIONAL_TESTS
//#define SKIP_MOVE_TESTS
//#define SKIP_MISCELLANEOUS_TESTS
//#define SKIP_CONTROL_INSTRUCTION_TESTS


#ifndef SKIP_ARITHMETIC_TESTS
INSTANTIATE_TEST_SUITE_P(AddByte, TestFixture, testing::ValuesIn(GetTests("add_byte.json")));
INSTANTIATE_TEST_SUITE_P(AddWord, TestFixture, testing::ValuesIn(GetTests("add_word.json")));
INSTANTIATE_TEST_SUITE_P(AddLong, TestFixture, testing::ValuesIn(GetTests("add_long.json")));

INSTANTIATE_TEST_SUITE_P(AddaWord, TestFixture, testing::ValuesIn(GetTests("adda_word.json")));
INSTANTIATE_TEST_SUITE_P(AddaLong, TestFixture, testing::ValuesIn(GetTests("adda_long.json")));

INSTANTIATE_TEST_SUITE_P(AndByte, TestFixture, testing::ValuesIn(GetTests("and_byte.json")));
INSTANTIATE_TEST_SUITE_P(AndWord, TestFixture, testing::ValuesIn(GetTests("and_word.json")));
INSTANTIATE_TEST_SUITE_P(AndLong, TestFixture, testing::ValuesIn(GetTests("and_long.json")));

INSTANTIATE_TEST_SUITE_P(CmpByte, TestFixture, testing::ValuesIn(GetTests("cmp_byte.json")));
INSTANTIATE_TEST_SUITE_P(CmpWord, TestFixture, testing::ValuesIn(GetTests("cmp_word.json")));
INSTANTIATE_TEST_SUITE_P(CmpLong, TestFixture, testing::ValuesIn(GetTests("cmp_long.json")));

INSTANTIATE_TEST_SUITE_P(CmpaWord, TestFixture, testing::ValuesIn(GetTests("cmpa_word.json")));
INSTANTIATE_TEST_SUITE_P(CmpaLong, TestFixture, testing::ValuesIn(GetTests("cmpa_long.json")));

INSTANTIATE_TEST_SUITE_P(EorByte, TestFixture, testing::ValuesIn(GetTests("eor_byte.json")));
INSTANTIATE_TEST_SUITE_P(EorWord, TestFixture, testing::ValuesIn(GetTests("eor_word.json")));
INSTANTIATE_TEST_SUITE_P(EorLong, TestFixture, testing::ValuesIn(GetTests("eor_long.json")));

INSTANTIATE_TEST_SUITE_P(OrByte, TestFixture, testing::ValuesIn(GetTests("or_byte.json")));
INSTANTIATE_TEST_SUITE_P(OrWord, TestFixture, testing::ValuesIn(GetTests("or_word.json")));
INSTANTIATE_TEST_SUITE_P(OrLong, TestFixture, testing::ValuesIn(GetTests("or_long.json")));

INSTANTIATE_TEST_SUITE_P(SubByte, TestFixture, testing::ValuesIn(GetTests("sub_byte.json")));
INSTANTIATE_TEST_SUITE_P(SubWord, TestFixture, testing::ValuesIn(GetTests("sub_word.json")));
INSTANTIATE_TEST_SUITE_P(SubLong, TestFixture, testing::ValuesIn(GetTests("sub_long.json")));

INSTANTIATE_TEST_SUITE_P(SubaWord, TestFixture, testing::ValuesIn(GetTests("suba_word.json")));
INSTANTIATE_TEST_SUITE_P(SubaLong, TestFixture, testing::ValuesIn(GetTests("suba_long.json")));

INSTANTIATE_TEST_SUITE_P(MuluWord, TestFixture, testing::ValuesIn(GetTests("mulu_word.json")));
INSTANTIATE_TEST_SUITE_P(MulsWord, TestFixture, testing::ValuesIn(GetTests("muls_word.json")));

INSTANTIATE_TEST_SUITE_P(DivuWord, TestFixture, testing::ValuesIn(GetTests("divu_word.json")));
INSTANTIATE_TEST_SUITE_P(DivsWord, TestFixture, testing::ValuesIn(GetTests("divs_word.json")));
#endif

#ifndef SKIP_IMMEDIATE_TESTS
INSTANTIATE_TEST_SUITE_P(AndiByte, TestFixture, testing::ValuesIn(GetTests("andi_byte.json")));
INSTANTIATE_TEST_SUITE_P(AndiWord, TestFixture, testing::ValuesIn(GetTests("andi_word.json")));
INSTANTIATE_TEST_SUITE_P(AndiLong, TestFixture, testing::ValuesIn(GetTests("andi_long.json")));

INSTANTIATE_TEST_SUITE_P(AddiByte, TestFixture, testing::ValuesIn(GetTests("addi_byte.json")));
INSTANTIATE_TEST_SUITE_P(AddiWord, TestFixture, testing::ValuesIn(GetTests("addi_word.json")));
INSTANTIATE_TEST_SUITE_P(AddiLong, TestFixture, testing::ValuesIn(GetTests("addi_long.json")));

INSTANTIATE_TEST_SUITE_P(CmpiByte, TestFixture, testing::ValuesIn(GetTests("cmpi_byte.json")));
INSTANTIATE_TEST_SUITE_P(CmpiWord, TestFixture, testing::ValuesIn(GetTests("cmpi_word.json")));
INSTANTIATE_TEST_SUITE_P(CmpiLong, TestFixture, testing::ValuesIn(GetTests("cmpi_long.json")));

INSTANTIATE_TEST_SUITE_P(EoriByte, TestFixture, testing::ValuesIn(GetTests("eori_byte.json")));
INSTANTIATE_TEST_SUITE_P(EoriWord, TestFixture, testing::ValuesIn(GetTests("eori_word.json")));
INSTANTIATE_TEST_SUITE_P(EoriLong, TestFixture, testing::ValuesIn(GetTests("eori_long.json")));

INSTANTIATE_TEST_SUITE_P(OriByte, TestFixture, testing::ValuesIn(GetTests("ori_byte.json")));
INSTANTIATE_TEST_SUITE_P(OriWord, TestFixture, testing::ValuesIn(GetTests("ori_word.json")));
INSTANTIATE_TEST_SUITE_P(OriLong, TestFixture, testing::ValuesIn(GetTests("ori_long.json")));

INSTANTIATE_TEST_SUITE_P(SubiByte, TestFixture, testing::ValuesIn(GetTests("subi_byte.json")));
INSTANTIATE_TEST_SUITE_P(SubiWord, TestFixture, testing::ValuesIn(GetTests("subi_word.json")));
INSTANTIATE_TEST_SUITE_P(SubiLong, TestFixture, testing::ValuesIn(GetTests("subi_long.json")));
#endif

#ifndef SKIP_IMMEDIATE_QUICK_TESTS
INSTANTIATE_TEST_SUITE_P(AddqByte, TestFixture, testing::ValuesIn(GetTests("addq_byte.json")));
INSTANTIATE_TEST_SUITE_P(AddqWord, TestFixture, testing::ValuesIn(GetTests("addq_word.json")));
INSTANTIATE_TEST_SUITE_P(AddqLong, TestFixture, testing::ValuesIn(GetTests("addq_long.json")));

INSTANTIATE_TEST_SUITE_P(AddqaWord, TestFixture, testing::ValuesIn(GetTests("addqa_word.json")));
INSTANTIATE_TEST_SUITE_P(AddqaLong, TestFixture, testing::ValuesIn(GetTests("addqa_long.json")));

INSTANTIATE_TEST_SUITE_P(SubqByte, TestFixture, testing::ValuesIn(GetTests("subq_byte.json")));
INSTANTIATE_TEST_SUITE_P(SubqWord, TestFixture, testing::ValuesIn(GetTests("subq_word.json")));
INSTANTIATE_TEST_SUITE_P(SubqLong, TestFixture, testing::ValuesIn(GetTests("subq_long.json")));

INSTANTIATE_TEST_SUITE_P(SubqaWord, TestFixture, testing::ValuesIn(GetTests("subqa_word.json")));
INSTANTIATE_TEST_SUITE_P(SubqaLong, TestFixture, testing::ValuesIn(GetTests("subqa_long.json")));

INSTANTIATE_TEST_SUITE_P(MoveqLong, TestFixture, testing::ValuesIn(GetTests("moveq_long.json")));
#endif

#ifndef SKIP_BITWISE_TESTS
INSTANTIATE_TEST_SUITE_P(BchgDynamicByte, TestFixture, testing::ValuesIn(GetTests("bchg_dynamic_byte.json")));
INSTANTIATE_TEST_SUITE_P(BchgDynamicLong, TestFixture, testing::ValuesIn(GetTests("bchg_dynamic_long.json")));
INSTANTIATE_TEST_SUITE_P(BchgStaticByte, TestFixture, testing::ValuesIn(GetTests("bchg_static_byte.json")));
INSTANTIATE_TEST_SUITE_P(BchgStaticLong, TestFixture, testing::ValuesIn(GetTests("bchg_static_long.json")));

INSTANTIATE_TEST_SUITE_P(BclrDynamicByte, TestFixture, testing::ValuesIn(GetTests("bclr_dynamic_byte.json")));
INSTANTIATE_TEST_SUITE_P(BclrDynamicLong, TestFixture, testing::ValuesIn(GetTests("bclr_dynamic_long.json")));
INSTANTIATE_TEST_SUITE_P(BclrStaticByte, TestFixture, testing::ValuesIn(GetTests("bclr_static_byte.json")));
INSTANTIATE_TEST_SUITE_P(BclrStaticLong, TestFixture, testing::ValuesIn(GetTests("bclr_static_long.json")));

INSTANTIATE_TEST_SUITE_P(BsetDynamicByte, TestFixture, testing::ValuesIn(GetTests("bset_dynamic_byte.json")));
INSTANTIATE_TEST_SUITE_P(BsetDynamicLong, TestFixture, testing::ValuesIn(GetTests("bset_dynamic_long.json")));
INSTANTIATE_TEST_SUITE_P(BsetStaticByte, TestFixture, testing::ValuesIn(GetTests("bset_static_byte.json")));
INSTANTIATE_TEST_SUITE_P(BsetStaticLong, TestFixture, testing::ValuesIn(GetTests("bset_static_long.json")));

INSTANTIATE_TEST_SUITE_P(BtstDynamicByte, TestFixture, testing::ValuesIn(GetTests("btst_dynamic_byte.json")));
INSTANTIATE_TEST_SUITE_P(BtstDynamicLong, TestFixture, testing::ValuesIn(GetTests("btst_dynamic_long.json")));
INSTANTIATE_TEST_SUITE_P(BtstStaticByte, TestFixture, testing::ValuesIn(GetTests("btst_static_byte.json")));
INSTANTIATE_TEST_SUITE_P(BtstStaticLong, TestFixture, testing::ValuesIn(GetTests("btst_static_long.json")));
#endif

#ifndef SKIP_SHIFT_ROTATE_RIGHT_TESTS
INSTANTIATE_TEST_SUITE_P(AsrByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AsrWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AsrLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(AsrByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AsrWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AsrLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(AsrWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("asr_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(LsrByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LsrWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LsrLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(LsrByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LsrWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LsrLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(LsrWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsr_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(RoxrByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxrWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxrLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RoxrByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxrWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxrLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RoxrWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxr_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(RorByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RorWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RorLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RorByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RorWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RorLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RorWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("ror_word_to_memory.json")));

#endif

#ifndef SKIP_SHIFT_ROTATE_LEFT_TESTS
INSTANTIATE_TEST_SUITE_P(AslByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AslWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AslLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(AslByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AslWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(AslLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(AslWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("asl_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(LslByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LslWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LslLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(LslByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LslWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(LslLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(LslWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("lsl_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(RoxlByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxlWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxlLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RoxlByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxlWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RoxlLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RoxlWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("roxl_word_to_memory.json")));


INSTANTIATE_TEST_SUITE_P(RolByteCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_byte_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RolWordCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_word_count_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RolLongCountToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_long_count_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RolByteRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_byte_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RolWordRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_word_register_to_data_register.json")));
INSTANTIATE_TEST_SUITE_P(RolLongRegisterToDataRegister,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_long_register_to_data_register.json")));

INSTANTIATE_TEST_SUITE_P(RolWordToMemory,
                         TestFixture,
                         testing::ValuesIn(GetTests("rol_word_to_memory.json")));
#endif

#ifndef SKIP_SINGLE_OPERAND_TESTS
INSTANTIATE_TEST_SUITE_P(NegxByte, TestFixture, testing::ValuesIn(GetTests("negx_byte.json")));
INSTANTIATE_TEST_SUITE_P(NegxWord, TestFixture, testing::ValuesIn(GetTests("negx_word.json")));
INSTANTIATE_TEST_SUITE_P(NegxLong, TestFixture, testing::ValuesIn(GetTests("negx_long.json")));

INSTANTIATE_TEST_SUITE_P(ClrByte, TestFixture, testing::ValuesIn(GetTests("clr_byte.json")));
INSTANTIATE_TEST_SUITE_P(ClrWord, TestFixture, testing::ValuesIn(GetTests("clr_word.json")));
INSTANTIATE_TEST_SUITE_P(ClrLong, TestFixture, testing::ValuesIn(GetTests("clr_long.json")));

INSTANTIATE_TEST_SUITE_P(NegByte, TestFixture, testing::ValuesIn(GetTests("neg_byte.json")));
INSTANTIATE_TEST_SUITE_P(NegWord, TestFixture, testing::ValuesIn(GetTests("neg_word.json")));
INSTANTIATE_TEST_SUITE_P(NegLong, TestFixture, testing::ValuesIn(GetTests("neg_long.json")));

INSTANTIATE_TEST_SUITE_P(NotByte, TestFixture, testing::ValuesIn(GetTests("not_byte.json")));
INSTANTIATE_TEST_SUITE_P(NotWord, TestFixture, testing::ValuesIn(GetTests("not_word.json")));
INSTANTIATE_TEST_SUITE_P(NotLong, TestFixture, testing::ValuesIn(GetTests("not_long.json")));

INSTANTIATE_TEST_SUITE_P(NbcdByte, TestFixture, testing::ValuesIn(GetTests("nbcd_byte.json")));

INSTANTIATE_TEST_SUITE_P(STByte, TestFixture, testing::ValuesIn(GetTests("st_byte.json")));
INSTANTIATE_TEST_SUITE_P(SFByte, TestFixture, testing::ValuesIn(GetTests("sf_byte.json")));
INSTANTIATE_TEST_SUITE_P(SHIByte, TestFixture, testing::ValuesIn(GetTests("shi_byte.json")));
INSTANTIATE_TEST_SUITE_P(SLSByte, TestFixture, testing::ValuesIn(GetTests("sls_byte.json")));
INSTANTIATE_TEST_SUITE_P(SCCByte, TestFixture, testing::ValuesIn(GetTests("scc_byte.json")));
INSTANTIATE_TEST_SUITE_P(SCSByte, TestFixture, testing::ValuesIn(GetTests("scs_byte.json")));
INSTANTIATE_TEST_SUITE_P(SNEByte, TestFixture, testing::ValuesIn(GetTests("sne_byte.json")));
INSTANTIATE_TEST_SUITE_P(SEQByte, TestFixture, testing::ValuesIn(GetTests("seq_byte.json")));
INSTANTIATE_TEST_SUITE_P(SVCByte, TestFixture, testing::ValuesIn(GetTests("svc_byte.json")));
INSTANTIATE_TEST_SUITE_P(SVSByte, TestFixture, testing::ValuesIn(GetTests("svs_byte.json")));
INSTANTIATE_TEST_SUITE_P(SPLByte, TestFixture, testing::ValuesIn(GetTests("spl_byte.json")));
INSTANTIATE_TEST_SUITE_P(SMIByte, TestFixture, testing::ValuesIn(GetTests("smi_byte.json")));
INSTANTIATE_TEST_SUITE_P(SGEByte, TestFixture, testing::ValuesIn(GetTests("sge_byte.json")));
INSTANTIATE_TEST_SUITE_P(SLTByte, TestFixture, testing::ValuesIn(GetTests("slt_byte.json")));
INSTANTIATE_TEST_SUITE_P(SGTByte, TestFixture, testing::ValuesIn(GetTests("sgt_byte.json")));
INSTANTIATE_TEST_SUITE_P(SLEByte, TestFixture, testing::ValuesIn(GetTests("sle_byte.json")));

INSTANTIATE_TEST_SUITE_P(Tas, TestFixture, testing::ValuesIn(GetTests("tas.json")));

INSTANTIATE_TEST_SUITE_P(TstByte, TestFixture, testing::ValuesIn(GetTests("tst_byte.json")));
INSTANTIATE_TEST_SUITE_P(TstWord, TestFixture, testing::ValuesIn(GetTests("tst_word.json")));
INSTANTIATE_TEST_SUITE_P(TstLong, TestFixture, testing::ValuesIn(GetTests("tst_long.json")));
#endif

#ifndef SKIP_MULTIPRECISION_TESTS
INSTANTIATE_TEST_SUITE_P(AddxByte, TestFixture, testing::ValuesIn(GetTests("addx_byte.json")));
INSTANTIATE_TEST_SUITE_P(AddxWord, TestFixture, testing::ValuesIn(GetTests("addx_word.json")));
INSTANTIATE_TEST_SUITE_P(AddxLong, TestFixture, testing::ValuesIn(GetTests("addx_long.json")));

INSTANTIATE_TEST_SUITE_P(SubxByte, TestFixture, testing::ValuesIn(GetTests("subx_byte.json")));
INSTANTIATE_TEST_SUITE_P(SubxWord, TestFixture, testing::ValuesIn(GetTests("subx_word.json")));
INSTANTIATE_TEST_SUITE_P(SubxLong, TestFixture, testing::ValuesIn(GetTests("subx_long.json")));

INSTANTIATE_TEST_SUITE_P(CmpmByte, TestFixture, testing::ValuesIn(GetTests("cmpm_byte.json")));
INSTANTIATE_TEST_SUITE_P(CmpmWord, TestFixture, testing::ValuesIn(GetTests("cmpm_word.json")));
INSTANTIATE_TEST_SUITE_P(CmpmLong, TestFixture, testing::ValuesIn(GetTests("cmpm_long.json")));

INSTANTIATE_TEST_SUITE_P(AbcdByte, TestFixture, testing::ValuesIn(GetTests("abcd_byte.json")));

INSTANTIATE_TEST_SUITE_P(SbcdByte, TestFixture, testing::ValuesIn(GetTests("sbcd_byte.json")));
#endif

#ifndef SKIP_CONDITIONAL_TESTS
INSTANTIATE_TEST_SUITE_P(DBTWord, TestFixture, testing::ValuesIn(GetTests("dbt_word.json")));
INSTANTIATE_TEST_SUITE_P(DBFWord, TestFixture, testing::ValuesIn(GetTests("dbf_word.json")));
INSTANTIATE_TEST_SUITE_P(DBHIWord, TestFixture, testing::ValuesIn(GetTests("dbhi_word.json")));
INSTANTIATE_TEST_SUITE_P(DBLSWord, TestFixture, testing::ValuesIn(GetTests("dbls_word.json")));
INSTANTIATE_TEST_SUITE_P(DBCCWord, TestFixture, testing::ValuesIn(GetTests("dbcc_word.json")));
INSTANTIATE_TEST_SUITE_P(DBCSWord, TestFixture, testing::ValuesIn(GetTests("dbcs_word.json")));
INSTANTIATE_TEST_SUITE_P(DBNEWord, TestFixture, testing::ValuesIn(GetTests("dbne_word.json")));
INSTANTIATE_TEST_SUITE_P(DBEQWord, TestFixture, testing::ValuesIn(GetTests("dbeq_word.json")));
INSTANTIATE_TEST_SUITE_P(DBVCWord, TestFixture, testing::ValuesIn(GetTests("dbvc_word.json")));
INSTANTIATE_TEST_SUITE_P(DBVSWord, TestFixture, testing::ValuesIn(GetTests("dbvs_word.json")));
INSTANTIATE_TEST_SUITE_P(DBPLWord, TestFixture, testing::ValuesIn(GetTests("dbpl_word.json")));
INSTANTIATE_TEST_SUITE_P(DBMIWord, TestFixture, testing::ValuesIn(GetTests("dbmi_word.json")));
INSTANTIATE_TEST_SUITE_P(DBGEWord, TestFixture, testing::ValuesIn(GetTests("dbge_word.json")));
INSTANTIATE_TEST_SUITE_P(DBLTWord, TestFixture, testing::ValuesIn(GetTests("dblt_word.json")));
INSTANTIATE_TEST_SUITE_P(DBGTWord, TestFixture, testing::ValuesIn(GetTests("dbgt_word.json")));
INSTANTIATE_TEST_SUITE_P(DBLEWord, TestFixture, testing::ValuesIn(GetTests("dble_word.json")));

INSTANTIATE_TEST_SUITE_P(BRAByte, TestFixture, testing::ValuesIn(GetTests("bra_byte.json")));
INSTANTIATE_TEST_SUITE_P(BHIByte, TestFixture, testing::ValuesIn(GetTests("bhi_byte.json")));
INSTANTIATE_TEST_SUITE_P(BLSByte, TestFixture, testing::ValuesIn(GetTests("bls_byte.json")));
INSTANTIATE_TEST_SUITE_P(BCCByte, TestFixture, testing::ValuesIn(GetTests("bcc_byte.json")));
INSTANTIATE_TEST_SUITE_P(BCSByte, TestFixture, testing::ValuesIn(GetTests("bcs_byte.json")));
INSTANTIATE_TEST_SUITE_P(BNEByte, TestFixture, testing::ValuesIn(GetTests("bne_byte.json")));
INSTANTIATE_TEST_SUITE_P(BEQByte, TestFixture, testing::ValuesIn(GetTests("beq_byte.json")));
INSTANTIATE_TEST_SUITE_P(BVCByte, TestFixture, testing::ValuesIn(GetTests("bvc_byte.json")));
INSTANTIATE_TEST_SUITE_P(BVSByte, TestFixture, testing::ValuesIn(GetTests("bvs_byte.json")));
INSTANTIATE_TEST_SUITE_P(BPLByte, TestFixture, testing::ValuesIn(GetTests("bpl_byte.json")));
INSTANTIATE_TEST_SUITE_P(BMIByte, TestFixture, testing::ValuesIn(GetTests("bmi_byte.json")));
INSTANTIATE_TEST_SUITE_P(BGEByte, TestFixture, testing::ValuesIn(GetTests("bge_byte.json")));
INSTANTIATE_TEST_SUITE_P(BLTByte, TestFixture, testing::ValuesIn(GetTests("blt_byte.json")));
INSTANTIATE_TEST_SUITE_P(BGTByte, TestFixture, testing::ValuesIn(GetTests("bgt_byte.json")));
INSTANTIATE_TEST_SUITE_P(BLEByte, TestFixture, testing::ValuesIn(GetTests("ble_byte.json")));

INSTANTIATE_TEST_SUITE_P(BRAWord, TestFixture, testing::ValuesIn(GetTests("bra_word.json")));
INSTANTIATE_TEST_SUITE_P(BHIWord, TestFixture, testing::ValuesIn(GetTests("bhi_word.json")));
INSTANTIATE_TEST_SUITE_P(BLSWord, TestFixture, testing::ValuesIn(GetTests("bls_word.json")));
INSTANTIATE_TEST_SUITE_P(BCCWord, TestFixture, testing::ValuesIn(GetTests("bcc_word.json")));
INSTANTIATE_TEST_SUITE_P(BCSWord, TestFixture, testing::ValuesIn(GetTests("bcs_word.json")));
INSTANTIATE_TEST_SUITE_P(BNEWord, TestFixture, testing::ValuesIn(GetTests("bne_word.json")));
INSTANTIATE_TEST_SUITE_P(BEQWord, TestFixture, testing::ValuesIn(GetTests("beq_word.json")));
INSTANTIATE_TEST_SUITE_P(BVCWord, TestFixture, testing::ValuesIn(GetTests("bvc_word.json")));
INSTANTIATE_TEST_SUITE_P(BVSWord, TestFixture, testing::ValuesIn(GetTests("bvs_word.json")));
INSTANTIATE_TEST_SUITE_P(BPLWord, TestFixture, testing::ValuesIn(GetTests("bpl_word.json")));
INSTANTIATE_TEST_SUITE_P(BMIWord, TestFixture, testing::ValuesIn(GetTests("bmi_word.json")));
INSTANTIATE_TEST_SUITE_P(BGEWord, TestFixture, testing::ValuesIn(GetTests("bge_word.json")));
INSTANTIATE_TEST_SUITE_P(BLTWord, TestFixture, testing::ValuesIn(GetTests("blt_word.json")));
INSTANTIATE_TEST_SUITE_P(BGTWord, TestFixture, testing::ValuesIn(GetTests("bgt_word.json")));
INSTANTIATE_TEST_SUITE_P(BLEWord, TestFixture, testing::ValuesIn(GetTests("ble_word.json")));

INSTANTIATE_TEST_SUITE_P(BSRByte, TestFixture, testing::ValuesIn(GetTests("bsr_byte.json")));
INSTANTIATE_TEST_SUITE_P(BSRWord, TestFixture, testing::ValuesIn(GetTests("bsr_word.json")));
#endif

#ifndef SKIP_MOVE_TESTS
INSTANTIATE_TEST_SUITE_P(MoveByte, TestFixture, testing::ValuesIn(GetTests("move_byte.json")));
INSTANTIATE_TEST_SUITE_P(MoveWord, TestFixture, testing::ValuesIn(GetTests("move_word.json")));
INSTANTIATE_TEST_SUITE_P(MoveLong, TestFixture, testing::ValuesIn(GetTests("move_long.json")));

INSTANTIATE_TEST_SUITE_P(MoveaWord, TestFixture, testing::ValuesIn(GetTests("movea_word.json")));
INSTANTIATE_TEST_SUITE_P(MoveaLong, TestFixture, testing::ValuesIn(GetTests("movea_long.json")));
#endif

#ifndef SKIP_MISCELLANEOUS_TESTS
INSTANTIATE_TEST_SUITE_P(AndiCcr, TestFixture, testing::ValuesIn(GetTests("andi_ccr_byte.json")));
INSTANTIATE_TEST_SUITE_P(EoriCcr, TestFixture, testing::ValuesIn(GetTests("eori_ccr_byte.json")));
INSTANTIATE_TEST_SUITE_P(OriCcr, TestFixture, testing::ValuesIn(GetTests("ori_ccr_byte.json")));

INSTANTIATE_TEST_SUITE_P(AndiSr, TestFixture, testing::ValuesIn(GetTests("andi_sr_word.json")));
INSTANTIATE_TEST_SUITE_P(EoriSr, TestFixture, testing::ValuesIn(GetTests("eori_sr_word.json")));
INSTANTIATE_TEST_SUITE_P(OriSr, TestFixture, testing::ValuesIn(GetTests("ori_sr_word.json")));

INSTANTIATE_TEST_SUITE_P(MoveFromSRWord, TestFixture, testing::ValuesIn(GetTests("move_from_sr_word.json")));

INSTANTIATE_TEST_SUITE_P(MoveToCCRWord, TestFixture, testing::ValuesIn(GetTests("move_to_ccr_word.json")));
INSTANTIATE_TEST_SUITE_P(MoveToSRWord, TestFixture, testing::ValuesIn(GetTests("move_to_sr_word.json")));

INSTANTIATE_TEST_SUITE_P(MoveFromUsp, TestFixture, testing::ValuesIn(GetTests("move_from_usp.json")));
INSTANTIATE_TEST_SUITE_P(MoveToUsp, TestFixture, testing::ValuesIn(GetTests("move_to_usp.json")));

INSTANTIATE_TEST_SUITE_P(MovepWord, TestFixture, testing::ValuesIn(GetTests("movep_word.json")));
INSTANTIATE_TEST_SUITE_P(MovepLong, TestFixture, testing::ValuesIn(GetTests("movep_long.json")));

INSTANTIATE_TEST_SUITE_P(Nop, TestFixture, testing::ValuesIn(GetTests("nop.json")));
INSTANTIATE_TEST_SUITE_P(Reset, TestFixture, testing::ValuesIn(GetTests("reset.json")));

INSTANTIATE_TEST_SUITE_P(Rte, TestFixture, testing::ValuesIn(GetTests("rte.json")));
INSTANTIATE_TEST_SUITE_P(Rtr, TestFixture, testing::ValuesIn(GetTests("rtr.json")));
INSTANTIATE_TEST_SUITE_P(Rts, TestFixture, testing::ValuesIn(GetTests("rts.json")));

INSTANTIATE_TEST_SUITE_P(Link, TestFixture, testing::ValuesIn(GetTests("link.json")));
INSTANTIATE_TEST_SUITE_P(Unlk, TestFixture, testing::ValuesIn(GetTests("unlk.json")));

INSTANTIATE_TEST_SUITE_P(Exg, TestFixture, testing::ValuesIn(GetTests("exg.json")));

INSTANTIATE_TEST_SUITE_P(Swap, TestFixture, testing::ValuesIn(GetTests("swap.json")));

INSTANTIATE_TEST_SUITE_P(ExtWord, TestFixture, testing::ValuesIn(GetTests("ext_word.json")));
INSTANTIATE_TEST_SUITE_P(ExtLong, TestFixture, testing::ValuesIn(GetTests("ext_word.json")));

INSTANTIATE_TEST_SUITE_P(Trapv, TestFixture, testing::ValuesIn(GetTests("trapv.json")));

INSTANTIATE_TEST_SUITE_P(ChkWord, TestFixture, testing::ValuesIn(GetTests("chk_word.json")));

INSTANTIATE_TEST_SUITE_P(Stop, TestFixture, testing::ValuesIn(GetTests("stop.json")));
#endif

#ifndef SKIP_CONTROL_INSTRUCTION_TESTS
INSTANTIATE_TEST_SUITE_P(Jmp, TestFixture, testing::ValuesIn(GetTests("jmp.json")));
INSTANTIATE_TEST_SUITE_P(Jsr, TestFixture, testing::ValuesIn(GetTests("jsr.json")));
INSTANTIATE_TEST_SUITE_P(Lea, TestFixture, testing::ValuesIn(GetTests("lea.json")));
INSTANTIATE_TEST_SUITE_P(Pea, TestFixture, testing::ValuesIn(GetTests("pea.json")));

INSTANTIATE_TEST_SUITE_P(MovemWordMemory, TestFixture, testing::ValuesIn(GetTests("movem_word_memory.json")));
INSTANTIATE_TEST_SUITE_P(MovemLongMemory, TestFixture, testing::ValuesIn(GetTests("movem_long_memory.json")));

INSTANTIATE_TEST_SUITE_P(MovemWordRegister, TestFixture, testing::ValuesIn(GetTests("movem_word_register.json")));
INSTANTIATE_TEST_SUITE_P(MovemLongRegister, TestFixture, testing::ValuesIn(GetTests("movem_long_register.json")));
#endif