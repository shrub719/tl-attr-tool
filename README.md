# Tomodachi Life (3DS) Song Tool

A command line tool for editing the attributes of MSBT files from Tomodachi Life 3DS.

## Usage

Still very WIP, but it is useable!

Although I plan to support importing an `.msbp.txt` file for your own custom attribute
definitions, for now the only available ones are set `0` (Songs) and set `1` (Items).

```
tl-song-tool [command]

    extract [set] [msbt] [output]
        Extract the attribute values from an MSBT file into a human readable and 
        editable TOML file.

        set - which set of MSBP attribute definitions to use
        msbt - decompressed .msbt.txt file

    merge [set] [attr] [msbt] [output]
        Merge an edited attribute file with the MSBT file it was extracted from 
        to produce an edited MSBT file.

        set - which set of MSBP attribute definitions to use
        attr - extracted attribute file
        msbt - original decompressed .msbt.txt file
```

<!---->

