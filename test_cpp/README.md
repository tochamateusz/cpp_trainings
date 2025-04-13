# Google Test
Downloaded release 
[googletest](https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz)

Rename to `googletest` and copy to `./external`
# Generate project
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
```

# Build
```bash
cmake --build build -j 12
```

# Test
```bash
GTEST_COLOR=1 ctest --test-dir build --output-on-failure -j12
```

```bash
GTEST_COLOR=1 ctest --test-dir build --output-on-failure -j12                                                                                                               ─╯
Internal ctest changing into directory: /Users/toch88/develop/c++/test_cpp/build
Test project /Users/toch88/develop/c++/test_cpp/build
    Start 2: TestTopic.MoreEqualityTests
    Start 1: TestTopic.TrivialEquality
1/2 Test #1: TestTopic.TrivialEquality ........   Passed    0.00 sec
2/2 Test #2: TestTopic.MoreEqualityTests ......***Failed    0.01 sec
Running main() from /Users/toch88/develop/c++/test_cpp/external/googletest/googletest/src/gtest_main.cc
Note: Google Test filter = TestTopic.MoreEqualityTests
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from TestTopic
[ RUN      ] TestTopic.MoreEqualityTests
/Users/toch88/develop/c++/test_cpp/my_project/my_test.cpp:8: Failure
Expected equality of these values:
  GetMeaningOfLife()
    Which is: 42
  0
Oh

[  FAILED  ] TestTopic.MoreEqualityTests (0 ms)
[----------] 1 test from TestTopic (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] TestTopic.MoreEqualityTests

 1 FAILED TEST


50% tests passed, 1 tests failed out of 2

Total Test time (real) =   0.01 sec

The following tests FAILED:
          2 - TestTopic.MoreEqualityTests (Failed)
Errors while running CTest

```
