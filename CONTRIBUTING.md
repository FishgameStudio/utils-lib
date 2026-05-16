# Contributing Guidelines

Thank you for your interest in contributing to this project!
All kinds of contributions are welcome, including bug reports, feature requests, code improvements, documentation updates and more.

## Code of Conduct
- Keep communication polite and respectful.
- Follow consistent code style and project specifications.
- Do not submit malicious code, invalid or spam content.

## How to Contribute

### 1. Report Bugs
- Open a new [Issue](https://github.com/FishgameStudio/utils-lib/issues)
- Clearly describe the bug phenomenon, reproduction steps and expected behavior
- Attach system environment, compiler version and error logs if possible

### 2. Suggest Features
- Create an Issue with `[Feature]` tag
- Explain usage scenarios, implementation ideas and practical value

### 3. Submit Code Changes
1. Fork this repository
2. Create your feature branch
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Write code and follow the rules below
4. Commit your changes with standard commit messages
5. Push branch to your forked repo
6. Open a Pull Request to target the main development branch

## Development Specifications

### Language & Compiler
- Main language: Standard C++
- Recommended compiler: `clang++`
- Follow C++17 or above standard by default
- Avoid non-standard extensions and platform-dependent code as much as possible

### Code Style
- Use clear naming, avoid ambiguous abbreviations
- Add necessary English comments for core logic
- Keep function single responsibility, split large functions properly
- Try to use Object-Oriented style code, namespace, etc. to standardize the code.

### Build Rules
- Uniform compilation configuration, unified compiler and standard settings
- Ensure the project can compile and run normally under Linux / Windows

## Commit Message Format
Suggest simple unified format:
```
feat: add new sha512 hash function
fix: fix buffer overflow bug
docs: update contributing document
refactor: optimize core algorithm logic
```

## Pull Request Rules
1. Ensure local compilation passes without warnings and errors
2. Keep PR content focused, one PR solves one thing
3. Describe modification content and design ideas clearly

## Environment Suggestion
- Local build: Clang++
- Recommend using standard tools to unify development environment

## Contact
If you have any questions about contribution rules, you can leave a message in Issues for discussion.
