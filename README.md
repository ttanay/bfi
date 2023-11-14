# Brainfuck Interpreter - bfi
Simple brainfuck interpreter. ![example workflow](https://github.com/ttanay/bfi/actions/workflows/test.yml/badge.svg)  
Goal: Keep it as uncomplicated/dirty as possible.

## Usage
1. Build binary with `make`
2. Run the binary with the program with `./bfi <filepath>`

You can run the tests with `./test.sh`
## Language Specification[1]
A Brainfuck program has an implicit byte pointer, called "the pointer", which is free to move around within an array of 30000 bytes, initially all set to zero. The pointer itself is initialized to point to the beginning of this array.

The Brainfuck programming language consists of eight commands, each of which is represented as a single character.

`>`: 	Increment the pointer.  
`<`: 	Decrement the pointer.  
`+`: 	Increment the byte at the pointer.  
`-`: 	Decrement the byte at the pointer.  
`.`: 	Output the byte at the pointer.  
`,`: 	Input a byte and store it in the byte at the pointer.  
`[`: 	Jump forward past the matching `]` if the byte at the pointer is zero.  
`]`: 	Jump backward to the matching `[` unless the byte at the pointer is zero.  
The semantics of the Brainfuck commands can also be succinctly expressed in terms of C, as follows (assuming that p has been previously defined as a char):

`>` 	becomes 	`++p`;  
`<` 	becomes 	`--p`;  
`+` 	becomes 	`++*p`;  
`-` 	becomes 	`--*p`;  
`.` 	becomes 	`putchar(*p)`;  
`,` 	becomes 	`*p = getchar()`;  
`[` 	becomes 	`while (*p) {`  
`]` 	becomes 	`}`  

## References
1. https://muppetlabs.com/~breadbox/bf/