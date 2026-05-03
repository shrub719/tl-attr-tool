# Tomodachi Life (3DS) Song Tool

A command line tool for editing the attributes of MSBT files from Tomodachi Life 3DS.

## Usage

Still very WIP, but it is useable! This is intended to work on the extracted 
`.txt` files you can get by using **Export (Text)** in [MSBT Editor](https://msbt-editor.aeonsake.com/).

```
tl-song-tool [command]

    extract [msbp] [msbt] [output]
        Extract the attribute values from an MSBT file into a human readable and 
        editable TOML file.

        msbp - decompressed .msbp.txt file which contains the attribute 
        definitions for the MSBT file
        msbt - decompressed .msbt.txt file

    merge [msbp] [attr] [msbt] [output]
        Merge an edited attribute file with the MSBT file it was extracted from 
        to produce an edited MSBT file.

        msbp - decompressed .msbp.txt file belonging to the original MSBT file
        attr - extracted attribute file
        msbt - original decompressed .msbt.txt file
```

<!---->

