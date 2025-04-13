# Google Test
Copy your downloaded release 
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
