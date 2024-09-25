# ctest-example-crash-on-timeout

An example of how to debug a test that times out by making CTest send a custom signal to the test in question, handling that signal in the test, crashing.

This works because, when processes crash on macOS, a crash log is written to `~/Library/Logs/DiagnosticReports/`.
We have to send USR1 because CTest only supports sending SIGINT, SIGQUIT, SIGTERM, SIGUSER1, and SIGUSR2 so we can't directly send SIGSEGV.

## Pre-requisites

- C++ compiler
- CMake

## Running

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
ctest --output-on-failure
```

Now go check `~/Library/Logs/DiagnosticReports/`.
