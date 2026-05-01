build:
    gcc -o target/main src/main.c

[default]
run attributes="./msbt/test.msbt.txt": build
    ./target/main {{attributes}}
