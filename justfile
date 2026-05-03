name := "tl-song-tool"

build:
    gcc -o ./target/{{name}} src/main.c src/attributes.c

extract set="./msbt/Song.msbp.txt" msbt="./msbt/Metal.msbt.txt" output="./target/extracted.txt": build
    ./target/{{name}} extract {{set}} {{msbt}} {{output}}

merge set="./msbt/Song.msbp.txt" attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} merge {{set}} {{attr}} {{msbt}} {{output}}

[default]
test set="./msbt/Song.msbp.txt" attr="./target/extracted.txt" msbt="./msbt/Metal.msbt.txt" output="./target/merged.txt": build
    ./target/{{name}} extract {{set}} {{msbt}} {{attr}}
    ./target/{{name}} merge {{set}} {{attr}} {{msbt}} {{output}}
    diff {{msbt}} {{output}}
