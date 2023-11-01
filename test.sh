#!/usr/bin/bash

# make the binary before testing it
g++ main.cpp -o bfi

function print_result {
    printf '%s %-30s\n' "$1" "$2"
}
function test_case {
    output="$(echo "$2"| ./bfi)"
    exit_code=`echo $?`
    if [[ $output == $3 ]]; then
        print_result "$1" "PASS"
    elif [[ $exit_code != "0"  ]]; then
        err_msg="ERROR: "
        err_msg+="$exit_code"
        print_result "$1" "$err_msg"
    else
        status="FAIL; Actual output: '"
        status+="$output'"
        print_result "$1" "$status"
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
test_case "bug-finding hello world" ">[-]<[-]++++++++[->+++++++++<]>.----[--<+++>]<-.+++++++.><.+++.[-][[-]>[-]+++++++++[<+++++>-]<+...--------------.>++++++++++[<+++++>-]<.+++.-------.>+++++++++[<----->-]<.-.>++++++++[<+++++++>-]<++.-----------.--.-----------.+++++++.----.++++++++++++++.>++++++++++[<----->-]<..[-]++++++++++.[-]+++++++[.,]-]" "Hello"
test_case "hello world code golf" "+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+." "Hello, World!"