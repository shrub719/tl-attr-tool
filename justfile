build:
    gcc -o target/main src/main.c src/attributes.c

extract msbt="./msbt/Metal.msbt.txt" output="./target/extracted.txt": build
    ./target/main extract {{msbt}} {{output}}

merge attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/main merge {{attr}} {{msbt}} {{output}}

[default]
test attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/main extract {{msbt}} {{attr}}
    ./target/main merge {{attr}} {{msbt}} {{output}}
    diff {{msbt}} {{output}}
