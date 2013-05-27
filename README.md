# Simillimum

**Simillimum** is a fork of SourceMod.  
Right now it serves as a playground for those who would like to contribute to a more open repository.  
It's not meant to be as a competitor, Simillimum may not be in a usable state (although we aim to only accept tested changes to the core) and it uses experimental code.  
Anyone interested in becoming a contributor should get in touch with Zephyrus.  
Simillimum will always maintain ABI compatibility with SourceMod.  


## Changelog

**2013.05.23**
  * Forked SourceMod
  * Changed all SourceMod references to Simillimum while keeping ABI compatibility
  * New signature scanning algorithm using a version of the Boyer-Moore-Horspool algorithm
  * Introduced a new gamedata type for POSIX platforms to prevent offset breaks in case of updates
  * Converted the sdktools/game.cstrike.txt gamedata to use Dynamic Offsets
  * Added option to core.cfg to enable/disable listing of extensions and plugins
  * Updated SQLite libraries to the latest version so we can benefit from its smaller memory footprint  
 and better performance thanks to memory mapped I/O


**13.05.24**
  * Updated cURL libraries
  * Minor cleanup
  * Swapped the MySQL connector to the connector of MariaDB
  * Added native HandleError:GetHandleStatus(Handle:hndl)
  * Updated SDKHooks gamedata for CStrike to utilise Dynamic Offsets
  * Add support for CSS to the ExtinguishEntity function
 

**2013.05.25**
  * Updated makefiles and msvc solutions
  * Refactored and merged a few patches by **Afronanny**:
  * Using @aim while specatating someone will select the spectated player now
  * Added AwardClientAchievement native
  * Fixed a crash with Precache natives if they are supplied a bogus string

**2013.05.26**
  * Added initial LUA support, considered highly experimental, stuff:
    * http://i.imgur.com/5Mi7Kdi.png
    * http://pastebin.com/aMcTVLQQ
  * More cleansing

**2013.05.27**
  * A lot of LUA improvements
  * Finished updating makefiles so we can remove ambuild completely

## TODO

  * Major cleanup
  * Expose cURL functions to plugins
  * Implement a Socket extension without Boost dependencies
  * Use the Boyer-Moore-Horspool algorithm for strstr/stristr
  * Review all string handling functions and use a faster algorithm where possible
  * Convert more gamedata to use dynamic offsets
  * Expose Trie iteration to plugins
    * Write a trie iterator that doesn't actually suck......
  * Major improvements to the default plugins
  * Add a universal way to change the players' name
  * Implement color code formatting to PrintToChat and PrintToChatAll
  * Add full LUA support:
    * Add plugin hash support for plugin blacklist
    * Begin exposing natives to LUA
    * Rewrite all stock plugins in LUA
    * Add an exception handler to log all errors
    * Modify ExecuteString to use formatting