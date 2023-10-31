# Brainfuck Interpreter
Question to self: What is the smallest size of the compiler/interpreter I can write?

## Language Specification[1]
A Brainfuck program has an implicit byte pointer, called "the pointer", which is free to move around within an array of 30000 bytes, initially all set to zero. The pointer itself is initialized to point to the beginning of this array.

The Brainfuck programming language consists of eight commands, each of which is represented as a single character.

`>` 	Increment the pointer.
`<` 	Decrement the pointer.
`+` 	Increment the byte at the pointer.
`-` 	Decrement the byte at the pointer.
`.` 	Output the byte at the pointer.
`,` 	Input a byte and store it in the byte at the pointer.
`[` 	Jump forward past the matching `]` if the byte at the pointer is zero.
`]` 	Jump backward to the matching `[` unless the byte at the pointer is zero.
The semantics of the Brainfuck commands can also be succinctly expressed in terms of C, as follows (assuming that p has been previously defined as a char):

`>` 	becomes 	`++p`;
`<` 	becomes 	`--p`;
`+` 	becomes 	`++*p`;
`-` 	becomes 	`--*p`;
`.` 	becomes 	`putchar(*p)`;
`,` 	becomes 	`*p = getchar()`;
`[` 	becomes 	`while (*p) {`
`]` 	becomes 	`}`


## Design
Components:
1. FuckFuckVM or `ffvm`: A VM that takes each command as an instruction
2. `bfi`: Interpreter that instantiates the `ffvm`, parses the brainfuck program and executes commands on the `ffvm`

### ffvm
Responsible for
1. The byte array of 30,000 bytes intialized to zero
2. The pointer to the byte array


### bfi 
Artificial constraints:
1. Every command needs to be terminated with a newline(`\n`) | So that REPL can be evaluated

#### Conditional evaluation
Conditionals:
1. When `[` is encountered,
  a. if buffer is zero, then start executing from after the matching closing brace.
  b. if buffer is non-zero, then start executing the rest of the loop body
2. When `]` is encountered,
  a. if buffer is zero, then move forward
  b. if buffer is non-zero, then go back to the matching opening brace
Complexity:
  While skipping to the next closing brace, in the case of nested braces, keep pushing to the stack for `[` and popping for `]`, until the corresponding `]` is met

## References
1. https://muppetlabs.com/~breadbox/bf/