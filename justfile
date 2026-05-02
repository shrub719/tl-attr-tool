name := "tl-song-tool"

build:
    gcc -o ./target/{{name}} src/main.c src/attributes.c

extract msbt="./msbt/Metal.msbt.txt" output="./target/extracted.txt": build
    ./target/{{name}} extract {{msbt}} {{output}}

merge attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} merge {{attr}} {{msbt}} {{output}}

[default]
test attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} extract {{msbt}} {{attr}}
    ./target/{{name}} merge {{attr}} {{msbt}} {{output}}
    diff {{msbt}} {{output}}
