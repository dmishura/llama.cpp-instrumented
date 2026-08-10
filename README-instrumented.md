# llama.cpp Instrumented

Instrumented version of [llama.cpp](https://github.com/ggml-org/llama.cpp)
for performance analysis and profiler experiments.

## Changes

This repository adds performance instrumentation for:

- Attention regions
- FFN regions
- Layer boundaries
- Nested profiler ranges

The original llama.cpp README is available here:

[Original llama.cpp README](../README.md)

## Upstream

Based on:

https://github.com/ggml-org/llama.cpp