# A little bit less boring minesweeper using raylib
> [!IMPORTANT]
> Raylib must be compiled with the SVG macro enabled in config.h.
>  Otherwise some images will not be able to load.
> 
- This program was tested on a Macbook air M1 on Sonoma and on WSL Ubuntu. 
- A compiled binary of raylib for Mac is in the ```mac``` folder.<br>
- It was developed and tested on Windows 11 using MSVC cl compiler, not mingw's gcc.<br><br>
This was just for me to have fun so don't expect this to be organized or even optimized in any way .. <br>
The codebase is a mess, I know it, I simply didn't bother. Any advice is welcome tho.
# Compilation
## Windows
Simply call the build.bat file after invoking vcvarsall.bat:

    .\build.bat
## Mac & Linux
For Mac you can use the librarylib.a provided. Or use your own as long as the SVG macro is uncommented in the config.h in ```raylib/src/```.
<br>Same for Linux.

    make
# Commands

Press `r` to reset the game.<br>
`Left` click to reveal a tile, **maintain** and **drag** if you want to cancel.<br>
`Right` click to toggle a flag on a tile.<br>
`ESC` to quit.

# Known issues
- It takes quite a long time for the game to load because I simply load a lot of textures that aren't optimized at all.<br>
Same reason this repo is a bit heavy. Sorry I was kinda lazy on that part and just wanted to finish the game somehow.<br>
- It's a god damn memory hog, I malloc once but the struct is full of crap .. ( around 200 mb ram and yes this is not electron but C ..)
- A game never ends; you have to manually press `r` to reset it, even if you flagged every possible bomb<br>
# Licences
tobedone
