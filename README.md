# Tomodachi Life (3DS) Song Tool

A command line tool for editing the attributes of MSBT files from Tomodachi Life 3DS.

## Usage

Still very WIP, but it is useable! This is intended to work on the extracted
`.txt` files you can get by using **Export (Text)** in [MSBT Editor](https://msbt-editor.aeonsake.com/).

It should theoretically work with any Nintendo game that uses the same MSBT
format, but I haven't tested anything so bewarned.

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

**Extract:** using `[msbp]`, extract `[msbt]` to `[output]`.  
**Merge:** using `[msbp]`, merge `[attr]` onto `[msbt]` and into the new file `[output]`.

### Example

For example, if I wanted to edit the timings of the Metal song, I would use MSBT Editor 
on the dumped romfs of my Tomodachi Life ROM
to extract the text files from `Metal.msbt` (in `ArcBase`) and `Song.msbp` in
`Song_US_English_LZ.bin` to `Metal.msbt.txt` and `Song.msbp.txt`.

I would then run ```tl-song-tool extract Song.msbp.txt Metal.msbt.txt attributes.toml```

Then I would use my favourite text editor and edit `attributes.toml`
to change the `StartTick` values of each line to whatever I want.

Finally, I would run ```tl-song-tool merge Song.msbp.txt attributes.toml Metal.msbt.txt cool_new_metal.txt```

I would finish it off by importing `cool_new_metal.txt` into `Metal.msbt` 
using MSBT Editor and saving to `Song_US_English_LZ.bin`.

The new `Song_US_English_LZ.bin` is patched with my very own changes to
`attributes.toml` and I can use it to mod Tomodachi Life by placing it
into my LayeredFS modded romfs folder.

<!---->

