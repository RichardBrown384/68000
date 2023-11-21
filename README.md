# 68000 

## About

A Motorola 68000 emulator, assembler and disassembler written in C++ released under a MIT licence.

The project was originally started in 2019 when [Musashi][musashi] wasn't available on GitHub.

It represents an attempt to develop a 68000 emulator in a TDD manner.

## Testing strategy 

There are two sets of tests for the emulator

1. Approximately 3000 handwritten tests that try to cover a good number of cases for each instruction
2. Approximately 700,000 generated tests that cover more cases and address modes for each instruction

The tests are written in such a way that it should be possible to use them in your own projects with
minimal effort.

### Note

The tests were written with my understanding of how the 68000 works with information pulled from
the 68000 Programmer's Reference Manual, the 68000 User Manual and various other online sources. 

It is possible, with an effort this size, that something was overlooked and the tests may be in some way incorrect.

## Assembler and Disassembler

The assembler is currently not a fully featured assembler. It was written to support the concept of 
human-readable tests. As such it doesn't support branch labels, setting memory and expressions.

Most 68000 assemblers allow for implicit sizing in the instructions. For example, `ADD D1, D2` really means
`ADD.W D1, D2`. However, in the case of testing we want to be precise and therefore the size, when there 
is a choice, must be specified.

## Contributing

Contributions are welcome in the form of pull requests or issues with the following conditions

1. No named reference is to be made to any software that isn't behaving correctly
2. There must be either
   1. A reference to official documentation that demonstrates the correctness of the proposed fix
   2. A reference to documentation that shows the hardware behaves in an undocumented or different fashion
3. It must be supported by unit testing
4. Be nice

The first clause I feel is necessary because the project goal is to build a fully tested 68000 implementation and
not to support piracy. 

## Thanks

This project would have been harder if it had not for the following libraries

1. [orjson][orjson] this significantly outperforms Python's native JSON support and reduced the time spent waiting
2. [nlohmann][nlohmann] made consuming JSON data for testing purposes easy
3. [googletest][googletest] great C++ test framework
4. [fmtlib][fmtlib] fantastic C++ substitute for std::format which isn't available on my compiler

***

[musashi]: https://github.com/kstenerud/Musashi
[orjson]: https://github.com/ijl/orjson
[nlohmann]: https://github.com/nlohmann/json
[googletest]: https://google.github.io/googletest/
[fmtlib]: https://github.com/fmtlib/fmt.git