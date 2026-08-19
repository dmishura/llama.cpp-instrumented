# llama.cpp Instrumented

Instrumented fork of [llama.cpp](https://github.com/ggml-org/llama.cpp) for
performance analysis and execution-graph-level profiling.

This fork extends the llama.cpp execution graph with dedicated profiling marker
nodes. These markers are inserted directly into the model graph alongside normal
GGML operations, allowing model-level execution regions such as Attention and
FFN blocks to be represented explicitly in the graph.

When the graph is executed, marker nodes generate corresponding profiler ranges.
Any regions still open when graph execution reaches a synchronization point are
closed there, preventing profiling ranges from leaking into subsequent graph
executions.

Currently, this instrumentation is implemented for **Gemma 3** and **Llama (3)** only.

---

## Backend support

Profiling marker nodes are currently supported by:

- CPU backend
- CUDA backend

For CUDA execution, marker nodes are handled by the host-side CUDA backend.
This allows model-level profiling regions such as Attention and FFN to be
correlated with CUDA API activity and GPU kernel execution in profilers such
as NVIDIA Nsight Systems.

CUDA Graph execution is also supported. Profiling markers do not require
CUDA Graphs to be disabled.

---

## Why this fork exists

Low-level profilers provide detailed information about functions, kernels,
threads, and hardware activity, but they do not inherently know which part of
the transformer model that activity belongs to.

This fork adds semantic information to the execution graph itself.

Dedicated marker nodes are inserted into the GGML graph to describe model-level
execution regions, for example:

- Transformer layers
- Attention blocks
- Feed-forward network (FFN) blocks

When the graph is executed, these nodes generate corresponding profiler regions.
This makes it possible to correlate low-level profiler data with the logical
structure of the model.

## Region lifetime

Profiling regions are opened and closed by marker nodes executed as part of the
GGML graph.

Because graph execution may finish without encountering an explicit closing
marker for every currently open region, the synchronization point acts as a
final boundary: any regions that are still open when synchronization is reached
are closed there.

This ensures that profiler ranges do not leak across graph executions.

---

## Key additions

- Profiling marker nodes integrated directly into the GGML execution graph
- Model-level regions for Attention and FFN execution
- Layer-aware region labels
- Support for nested profiling regions
- Translation of graph markers into profiler-specific tracing ranges
- Instrumentation that follows normal graph construction and execution

---

## Interface / screenshots

### Overview

![UI overview](images/ui-overview.png)

### Profile markers

![Profile details](images/ui-profile-view.png)

### CUDA events with instrumentation mix
![CUDA events](images/ui-cuda.png)

### Vtune example of "Task" view
![Vtune example](images/vtune-example.png)


---

## What is changed compared to upstream

This repository is based on the upstream `llama.cpp` project and keeps it as the main codebase.

Custom changes in this fork currently include:

- computation graph based instrumentation;
- improved region naming;
- profiling-oriented modifications for experimentation.

If you are looking for the original project documentation, see:

- [Original upstream repository](https://github.com/ggml-org/llama.cpp)
- [Original README](README.md)

---

## Repository layout

```text
README.md                  # original upstream README
README-instrumented.md     # custom repository landing page
.github/README.md          # symlink to README-instrumented.md
docs/images/               # screenshots used in this page