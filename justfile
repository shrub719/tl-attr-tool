build:
    gcc -o target/main src/main.c

[default]
run: build
    ./target/main
