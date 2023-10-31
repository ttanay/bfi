#!/usr/bin/bash

# make the binary before testing it
g++ main.cpp -o bfi

function output {
    printf '%s %-30s\n' "$1" "$2"
}
function test_case {
    output="$(echo "$2"| ./bfi)"
    echo "$output"
    if [[ $output == $3 ]]; then
        output "$1" "PASS"
    else
        output "$1" "FAIL"
    fi
}

# TODO: Add failure test cases too
# Increment
test_case "increment" "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++." "A"
test_case "decrement" "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++--------." "9"
test_case "next" "+++++++++++++++++++++++++++++++++++++++++++++++++>+++++++++++++++++++++++++++++++++++++++++++++++++++++." "5"
test_case "prev" "+++++++++++++++++++++++++++++++++++++++++++++++++>+++++++++++++++++++++++++++++++++++++++++++++++++++++<." "1"
test_case "printable_loop" "++>+++++[<+>-]++++++++[<++++++>-]<." "7"
test_case "nested_loops" "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++." "Hello World!"
