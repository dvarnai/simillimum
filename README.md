Simillimum is a fork of SourceMod. Right now it serves as a playground for those who would like to
contribute to a more open repository. It's not meant to be as a competitor, Simillimum may not be in a
usable state (although we aim to only accept tested changes to the core) and it uses experimental code.
Anyone interested in becoming a contributor should get in touch with Zephyrus. Simillimum will always
maintain ABI compatibility with SourceMod.

Changelog:

2013.05.23:
-Forked SourceMod
-Changed all SourceMod references to Simillimum while keeping ABI compatibility
-New signature scanning algorithm using a version of the Boyer-Moore-Horspool algorithm
-Introduced a new gamedata type for POSIX platforms to prevent offset breaks in case of updates
-Converted the sdktools/game.cstrike.txt gamedata to use Dynamic Offsets
-Added option to core.cfg to enable/disable listing of extensions and plugins
-Updated SQLite libraries to the latest version so we can benefit from its smaller memory footprint
 and better performance thanks to memory mapped i/o