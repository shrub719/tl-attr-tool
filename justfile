name := "tl-song-tool"

build:
    gcc -o ./target/{{name}} src/main.c src/attributes.c

extract set="0" msbt="./msbt/Metal.msbt.txt" output="./target/extracted.txt": build
    ./target/{{name}} extract {{set}} {{msbt}} {{output}}

merge set="0" attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} merge {{set}} {{attr}} {{msbt}} {{output}}

[default]
test set="0" attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} extract {{set}} {{msbt}} {{attr}}
    ./target/{{name}} merge {{set}} {{attr}} {{msbt}} {{output}}
    diff {{msbt}} {{output}}
