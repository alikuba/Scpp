# Simple C++ (SC++ / Scpp)

Simple C++ is a simplified C++ syntax that is transpiled into real C++. It aims to keep the speed and ecosystem of C++ while removing common sources of undefined behavior, boilerplate and slow builds.

> **Status:** early design. This README describes the planned features and architecture, not a finished tool.

## Features

### Simpler structure
- **Global scope is the `main` scope.** Top-level statements run as `main`.
- **Functions are hoisted automatically.** The transpiler moves them outside `main` in the generated file and emits forward declarations.
- **Auto header creation and easy linking.** Headers are generated from your declarations.

### Undefined behavior checker
- **Out-of-bounds access** is flagged (statically for constant indexes, at runtime otherwise).

  ```cpp
  int arr[3] = {1, 2, 3};
  std::cout << arr[10];   // C++: no error, random value or crash. SC++: flagged
  ```
- **Uninitialized values get defaults.** `int x;` becomes `int x{};`, so it is always zero.
- **Signed integer overflow** is flagged.
- **Buffer overflow** patterns (`memcpy`, `strcpy`, C arrays) are flagged.

### Safe option and force option
Checked access is the default. Unchecked access is an explicit opt-in.

```cpp
std::vector<int> v = {1, 2, 3};
v[10];      // plain C++: no check -> UB
v.at(10);   // throws an exception, safer
```

### Memory handling
- Pointers are cleaned up automatically by default.
- Manual cleanup is available through an explicit opt-in.

### Easier templates
Cleaner template syntax that is lowered to modern C++ (concepts, `auto` parameters).

### Build system
- Quicker compiling: each file no longer re-reads every `include`, which removes repeated work.
- Content-hash caching, so unchanged files are not re-transpiled or recompiled.

### Developer experience
- Easier debugging: diagnostics point at `.scpp` source lines, not generated C++.
- Many features are wrapped in a prettier, more readable syntax.
- Uses the best and most recent tools and standards available for each task.

## Architecture

| Module | Responsibility |
|---|---|
| `cli_interface` | Commands (`build`, `run`, `check`, `clean`), flags, diagnostics display |
| `file_manager` | Reading `.scpp` files, dependency graph, writing `.cpp`/`.h`, caching, build files |
| `scope_separator` | Global scope as `main`, function hoisting, forward declarations |
| `undefined_behavior_checker` | Bounds, overflow and buffer checks, default initialization, safe/force handling |
| `parser` *(planned)* | Lexer, parser, AST |
| `semantic_analyzer` *(planned)* | Types, symbol tables, name resolution |
| `memory_manager` *(planned)* | Auto-cleaning pointers vs. manual management |
| `template_simplifier` *(planned)* | Easier template syntax lowered to C++ |
| `code_generator` *(planned)* | C++ emission, `#line` mapping, target standard |
| `runtime_support` *(planned)* | Header-only checked wrappers and overflow helpers |

### Pipeline

```
cli_interface
  -> file_manager (read, resolve includes)
  -> parser
  -> semantic_analyzer
  -> scope_separator
  -> memory_manager / template_simplifier / undefined_behavior_checker
  -> code_generator
  -> file_manager (write, build)
```

## Usage (planned)

```
scpp build            # transpile and compile
scpp run              # build and run
scpp check            # analyze only, no output
scpp clean            # remove generated files and cache

scpp build --release  # skip runtime checks
scpp build --force    # allow unchecked access
```

## Roadmap

1. Global-scope `main` and function hoisting
2. Default initialization
3. Checked indexing (safe by default, explicit force option)
4. `#line` mapping for debugging
5. Static out-of-bounds and overflow detection
6. Auto headers, caching and build file generation
7. Memory management and template syntax

## Contributing

The project is in the design stage. Ideas, syntax proposals and issues are welcome.

## License

To be decided.
