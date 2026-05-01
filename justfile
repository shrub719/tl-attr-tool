build:
    gcc -o target/main src/main.c src/attributes.c

[default]
run file="./msbt/Metal.msbt.txt" set="0": build
    ./target/main {{file}} {{set}}
