#!/usr/bin/bash

# make the binary before testing it
make

function print_result {
    printf '%s %-30s\n' "$1" "$2"
}

function test_result {
    if [[ $2 == $3 ]]; then
        print_result "$1" "PASS"
    elif [[ $4 != "0"  ]]; then
        err_msg="ERROR: "
        err_msg+="$4"
        print_result "$1" "$err_msg"
    else
        status="FAIL; Actual output: '"
        status+="$2'"
        print_result "$1" "$status"
    fi
}

function test_case {
    output="$(echo "$2"| ./bfi)"
    exit_code=`echo $?`
    test_result "$1" "$output" "$3" "$exit_code"
}

function test_case_file {
    output="$(./bfi $2 <<< $4)"
    exit_code=`echo $?`
    test_result "$1" "$output" "$3" "$exit_code"
}

# TODO: Add failure test cases too
test_case "increment" "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++." "A"
test_case "decrement" "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++--------." "9"
test_case "next" "+++++++++++++++++++++++++++++++++++++++++++++++++>+++++++++++++++++++++++++++++++++++++++++++++++++++++." "5"
test_case "prev" "+++++++++++++++++++++++++++++++++++++++++++++++++>+++++++++++++++++++++++++++++++++++++++++++++++++++++<." "1"
test_case "printable_loop" "++>+++++[<+>-]++++++++[<++++++>-]<." "7"
test_case "nested_loops" "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++." "Hello World!"
test_case "bug-finding hello" ">[-]<[-]++++++++[->+++++++++<]>.----[--<+++>]<-.+++++++.><.+++.[-][[-]>[-]+++++++++[<+++++>-]<+...--------------.>++++++++++[<+++++>-]<.+++.-------.>+++++++++[<----->-]<.-.>++++++++[<+++++++>-]<++.-----------.--.-----------.+++++++.----.++++++++++++++.>++++++++++[<----->-]<..[-]++++++++++.[-]+++++++[.,]-]" "Hello"
test_case "hello world code golf" "+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+." "Hello, World!"
#test_case "input" ",." "i"; FIXME

test_case_file "increment file" "tests/increment.bf" "A"
test_case_file "decrement file" "tests/decrement.bf" "9"
test_case_file "next file" "tests/next.bf" "5"
test_case_file "prev file" "tests/prev.bf" "1"
test_case_file "printable_loop file" "tests/printable_loop.bf" "7"
test_case_file "nested_loops file" "tests/nested_loops.bf" "Hello World!"
test_case_file "bug-finding hello file" "tests/hello.bf" "Hello"
test_case_file "hello world code golf file" "tests/hello_world_code_golf.bf" "Hello, World!"
test_case_file "input file" "tests/input.bf" "i" "i"

