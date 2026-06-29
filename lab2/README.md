# Lab 2: Lexical Analyzer for Token Recognition Using Flex

# Experiment Title
Lexical Analyzer for Token Recognition Using Flex

---

# Aim

To design and implement a lexical analyzer using Flex that reads a C-like program and recognizes tokens such as:

- Keywords
- Identifiers
- Operators
- Numbers
- Separators
- Special Symbols

---

# Introduction

A compiler cannot directly understand source code written by programmers.

For example:

```c
int a = 5;
```

To humans, this looks simple.

But for the compiler, this is only a stream of characters.

The first phase of the compiler is called:

# Lexical Analysis

The lexical analyzer reads the program character by character and converts it into meaningful units called:

# TOKENS

Example:

| Source Code | Token Type |
|-------------|------------|
| int | Keyword |
| a | Identifier |
| = | Operator |
| 5 | Number |
| ; | Separator |

The tool used in this experiment is:

# FLEX

Flex automatically generates a lexical analyzer from rules written using regular expressions.

---

# Software Requirements

| Software | Purpose |
|----------|----------|
| Flex | Lexical Analyzer Generator |
| GCC | C Compiler |
| Ubuntu Linux | Operating System |

---

# Step 1: Update Ubuntu Packages

Before installing software, update package information.

## Command

```bash
sudo apt update
```

## Explanation

- `sudo` → runs command as administrator
- `apt` → package manager
- `update` → refreshes package list

This ensures the latest package versions are available.

---

# Step 2: Install Flex and GCC

## Command

```bash
sudo apt install flex gcc -y
```

## Explanation

- `flex` → lexical analyzer generator
- `gcc` → GNU C compiler
- `-y` → automatically confirms installation

This installs all required tools.

---

# Step 3: Install Build Essential Tools

## Command

```bash
sudo apt install build-essential -y
```

## Explanation

This package installs:

- compiler tools
- linker
- standard development utilities

Useful for compiling C programs.

---

# Step 4: Verify Installation

## Check Flex

```bash
flex --version
```

### Example Output

```text
flex 2.6.4
```

---

## Check GCC

```bash
gcc --version
```

### Example Output

```text
gcc (Ubuntu 13.3.0)
```

---

# Step 5: Create Working Directory

## Command

```bash
mkdir lexical_lab
cd lexical_lab
```

## Explanation

- `mkdir` → creates folder
- `cd` → changes current directory

---

# Step 6: Create Flex Source File

Create a file named:

```text
tokenizer.l
```

## Command

```bash
nano tokenizer.l
```

## Explanation

- `nano` → terminal text editor
- `tokenizer.l` → Flex source file

---

# Step 7: Write Flex Program

Paste the following code inside `tokenizer.l`

```c
%{
#include <stdio.h>
#include <string.h>

int line_no = 1;
%}

/* Definitions */

DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD    int|float|if|else|return
OP         ==|!=|<=|>=|\+|\-|\*|\/|>|=
SEPARATOR  [;,(){}]

%%

{KEYWORD} {
    printf("Keyword: %s\n", yytext);
}

{ID} {
    printf("Identifier: %s\n", yytext);
}

{DIGIT}+ {
    printf("Number: %s\n", yytext);
}

{OP} {
    printf("Operator: %s\n", yytext);
}

{SEPARATOR} {
    printf("Separator: %s\n", yytext);
}

\n {
    line_no++;
}

[ \t] {
    /* Ignore spaces and tabs */
}

. {
    printf("Unknown Symbol: %s\n", yytext);
}

%%

int main() {
    printf("Enter the code (Press Ctrl+D to stop input):\n");

    yylex();

    return 0;
}

int yywrap() {
    return 1;
}
```

---

# Step 8: Save the File

Inside nano editor:

## Save File

Press:

```text
Ctrl + O
```

Then press:

```text
Enter
```

---

## Exit Nano

Press:

```text
Ctrl + X
```

---

# Understanding the Flex Program

The Flex program has 3 sections:

```text
Definitions
%%
Rules
%%
User Code
```

---

# Section 1: Definitions

```c
DIGIT      [0-9]
```

Recognizes digits from 0 to 9.

---

```c
ID         [a-zA-Z_][a-zA-Z0-9_]*
```

Recognizes identifiers.

Examples:

```text
a
sum
total_1
```

---

```c
KEYWORD    int|float|if|else|return
```

Recognizes language keywords.

---

# Section 2: Rules

Example:

```c
{DIGIT}+ {
    printf("Number: %s\n", yytext);
}
```

Meaning:

- if digits are found
- print them as numbers

`yytext` stores matched token.

---

# Section 3: User Code

Contains:

- `main()`
- `yywrap()`

---

# Step 9: Generate Scanner Using Flex

## Command

```bash
flex tokenizer.l
```

## Explanation

Flex reads `tokenizer.l` and generates:

```text
lex.yy.c
```

This file contains the generated scanner written in C language.

---

# Step 10: Verify Generated File

## Command

```bash
ls
```

## Expected Output

```text
lex.yy.c
tokenizer.l
```

---

# Step 11: Compile Generated Code

## Command

```bash
gcc lex.yy.c -o tokenizer
```

## Explanation

- `gcc` → C compiler
- `lex.yy.c` → generated scanner source
- `-o tokenizer` → executable name

This creates executable:

```text
tokenizer
```

---

# Step 12: Run the Program

## Command

```bash
./tokenizer
```

## Explanation

- `./` → current directory
- `tokenizer` → executable file

Program starts lexical analysis.

---

# Step 13: Enter Sample Input

```c
int a = 5;
float b = a + 10;

if (b > 10) {
    return b;
}
```

---

# Step 14: Stop Input

Press:

```text
Ctrl + D
```

This sends EOF (End Of File).

---

# Expected Output

```text
Keyword: int
Identifier: a
Operator: =
Number: 5
Separator: ;

Keyword: float
Identifier: b
Operator: =
Identifier: a
Operator: +
Number: 10
Separator: ;

Keyword: if
Separator: (
Identifier: b
Operator: >
Number: 10
Separator: )

Separator: {
Keyword: return
Identifier: b
Separator: ;
Separator: }
```

---

# Internal Working of the Scanner

Suppose input is:

```c
int a = 5;
```

The scanner works like this:

---

## Step 1

Reads:

```text
int
```

Matches:

```c
KEYWORD
```

Output:

```text
Keyword: int
```

---

## Step 2

Reads:

```text
a
```

Matches:

```c
ID
```

Output:

```text
Identifier: a
```

---

## Step 3

Reads:

```text
=
```

Matches:

```c
OP
```

Output:

```text
Operator: =
```

---

## Step 4

Reads:

```text
5
```

Matches:

```c
DIGIT+
```

Output:

```text
Number: 5
```

---

## Step 5

Reads:

```text
;
```

Matches:

```c
SEPARATOR
```

Output:

```text
Separator: ;
```

---

# Important Concepts

# 1. Tokens

Smallest meaningful unit in source code.

Examples:

- keywords
- identifiers
- numbers
- operators

---

# 2. Regular Expressions

Patterns used for token recognition.

Examples:

| Pattern | Meaning |
|---------|----------|
| [0-9] | digit |
| [a-z] | lowercase letters |
| + | one or more |
| * | zero or more |

---

# 3. yytext

Stores current matched token.

Example:

```c
printf("%s", yytext);
```

---

# 4. yylex()

Main scanner function generated by Flex.

Starts lexical analysis.

---

# 5. yywrap()

Called when input ends.

```c
int yywrap() {
    return 1;
}
```

Returning `1` stops scanning.

---

# Errors Faced During Experiment

# Error 1: unrecognized rule

## Reason

Incorrect formatting in Flex rules.

## Wrong Example

```c
{ID}
{ printf("Identifier"); }
```

## Correct Example

```c
{ID} {
    printf("Identifier");
}
```

---

# Error 2: lex.yy.c not found

## Reason

Flex failed to generate scanner.

## Solution

Fix Flex syntax and rerun:

```bash
flex tokenizer.l
```

---

# Error 3: expected declaration or statement at end of input

## Reason

Missing closing brace `}` in C code.

## Wrong Example

```c
int yywrap() {
    return 1;
```

## Correct Example

```c
int yywrap() {
    return 1;
}
```

---

# Error 4: GitHub Authentication Failed

## Reason

GitHub removed password authentication.

## Solution

Use GitHub Personal Access Token (PAT).

---

# Git Commands Used

## Add Files

```bash
git add .
```

Stages all files.

---

## Commit Files

```bash
git commit -m "Added Lab 2 lexical analyzer"
```

Creates snapshot of project.

---

## Push to GitHub

```bash
git push -u origin master
```

Uploads local repository to GitHub.

---

# Learning Outcomes

After completing this experiment, we learned:

- Basics of lexical analysis
- Token recognition
- Regular expressions
- Working of Flex
- Scanner generation
- C code compilation using GCC
- Error debugging
- Git and GitHub workflow

---

# Conclusion

In this experiment, a lexical analyzer was successfully implemented using Flex.

The scanner correctly recognized:

- keywords
- identifiers
- operators
- numbers
- separators

This experiment provided practical understanding of the first phase of compiler design: lexical analysis.