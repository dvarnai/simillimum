Simillimum is a fork of SourceMod. Right now it serves as a playground for those who would like to
contribute to a more open repository. It's not meant to be as a competitor, Simillimum may not be in a
usable state (although we aim to only accept tested changes to the core) and it uses experimental code.
Anyone interested in becoming a contributor should get in touch with Zephyrus. Simillimum will always
maintain ABI compatibility with SourceMod.

Changelog:

2013.05.23:<br/>
-Forked SourceMod<br/>
-Changed all SourceMod references to Simillimum while keeping ABI compatibility<br/>
-New signature scanning algorithm using a version of the Boyer-Moore-Horspool algorithm<br/>
-Introduced a new gamedata type for POSIX platforms to prevent offset breaks in case of updates<br/>
-Converted the sdktools/game.cstrike.txt gamedata to use Dynamic Offsets<br/>
-Added option to core.cfg to enable/disable listing of extensions and plugins<br/>
-Updated SQLite libraries to the latest version so we can benefit from its smaller memory footprint<br/>
 and better performance thanks to memory mapped I/O<br/>
<br/>
2013.05.24:<br/>
.Updated cURL libraries<br/>
<br/>
 TODO:<br/>
<br/>
-Major cleanup<br/>
-Expose cURL functions to plugins<br/>
-Implement a Socket extension without Boost dependencies<br/>
-Use the Boyer-Moore-Horspool algorithm for strstr/stristr<br/>
-Swap the MySQL connector to the connector of MariaDB<br/>
-Convert more gamedata to use dynamic offsets<br/>
-Expose Trie iteration to plugins<br/>
-Major improvements to the default plugins<br/>