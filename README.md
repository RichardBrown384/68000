# 68000 

## About

A Motorola 68000 emulator written in C++ released under a MIT licence.

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
3. [googletest][googletest] fantastic C++ test framework

***

[musashi]: https://github.com/kstenerud/Musashi
[orjson]: https://github.com/ijl/orjson
[nlohmann]: https://github.com/nlohmann/json
[googletest]: https://google.github.io/googletest/