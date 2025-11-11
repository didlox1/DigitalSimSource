# DigitalSim

Command-line source code for a simple digital electronics simulator. There is no GUI — the focus is on learning, clarity, and correctness.  
You can design and simulate small digital circuits using logic gates and clocks, connect components, set constant inputs, and observe signal propagation over time.

## Features

- Logic gates: AND, OR, NOT, XOR
- Clock sources with configurable period
- Per-gate propagation delays
- Wire components together (connect outputs to gate inputs)
- Set constant input levels (HIGH/LOW)
- Time-based signal propagation simulation
- Save projects to a file and load them back later
- Inspect a component's output and list all components
- Disconnect inputs from gates

A typical interactive menu looks like this:

```
=== DigitalSim ===
1. Add Component
2. Connect Connectors
3. Set Constant Input
4. Print Output
5. Print All Components
6. Disconnect Input From Gate
7. Save Module
8. Open Module
0. Exit
>
```

## Quick start

DigitalSim uses only the C/C++ standard library and builds on Windows and Linux.

### Build with CMake (recommended)

```bash
# From the repository root
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

The resulting executable will be in `build/` (or your generator's default output directory).

### Build with a compiler directly (example)

If you prefer to compile without CMake, you can compile the sources with a C++17 compiler. Adjust paths as needed:

```bash
g++ -std=c++17 -O2 -o digitalsim \
    src/*.cpp
```

## Example workflow

Below is a minimal end‑to‑end example showing how to create a small circuit, connect it, and observe output over time.

1) Add an AND gate
- Choose: 1 (Add Component)
- Name: `and1`
- Type: `AND`
- Propagation delay: e.g., `5 ns`

2) Add a clock
- Choose: 1 (Add Component)
- Name: `clk1`
- Type: `CLOCK`
- Period: e.g., `1000 ms`
- Total simulation time: e.g., `5000 ms`

3) Connect components
- Choose: 2 (Connect Connectors)
- Source: `clk1`
- Target: `and1`
- Input pin on `and1`: `1` (choose 1 or 2)

4) Set a constant input on the gate
- Choose: 3 (Set Constant Input)
- Gate name: `and1`
- Pin: `2`
- State: `1` (1 = HIGH, 0 = LOW)

5) Run and inspect output
- Choose: 4 (Print Output)
- Component name: `and1`
- The program will print the output state vs. time.

6) Save and load projects
- Choose: 7 (Save Module) to write the current project to a file.
- Choose: 8 (Open Module) to restore a previously saved project.

Notes:
- Time units shown above (ns, ms) are illustrative; use the units and format supported by the program's prompts.
- Propagation delays let you observe how signals settle over time rather than changing instantaneously.

## Why DigitalSim?

- Learn-by-doing: Build circuits, wire them, and see timing effects.
- Minimal dependencies: Standard library only.
- Portable: Confirmed to run correctly on Windows and Linux.
