# Tomodachi Life (3DS) Song Tool

A command line tool for editing the Tomodachi Life 3DS Concert Hall songs.

## Usage

Still very WIP, but it is useable!

This is intended to be used on `.msbt.txt` files extracted from `Song_[...].bin` using [MSBT Editor](https://msbt-editor.aeonsake.com/). 
The filename differs by localisation. 
You want to edit the song itself (e.g. `Metal.msbt`), not the lyrics (e.g. `Metal_Lyrics.msbt`).

```
tl-song-tool [command]

    extract [msbt] [output]
        Extract the attribute values from a song's MSBT file into human readable and editable TOML file.
        msbt - decompressed .msbt.txt file

    merge [attr] [msbt] [output]
        Merge an edited attribute file with the MSBT file it was extracted from to produce an edited MSBT file.
        attr - extracted attribute file
        msbt - original decompressed .msbt.txt file
```

<!---->

