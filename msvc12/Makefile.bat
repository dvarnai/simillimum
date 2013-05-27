@echo off

"%NETFRAME%\MSBuild" ../core/logic/msvc12/logic.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../loader/msvc12/loader.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../sourcepawn/jit/msvc12/jit-x86.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../lua/msvc12/lua-jit-x86.vcxproj /p:configuration=Release

"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - CSS"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - CS GO"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - Orange Box"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - Orange Box Valve"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - Old Metamod"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - Left 4 Dead"
"%NETFRAME%\MSBuild"  ../core/msvc12/sourcemod_mm.vcxproj /p:configuration="Release - Left 4 Dead 2"


"%NETFRAME%\MSBuild" ../extensions/curl/msvc12/curl.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/bintools/msvc12/bintools.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/clientprefs/msvc12/clientprefs.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/geoip/msvc12/geoip.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/mysql/msvc12/sm_mysql.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/regex/msvc12/regex.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/sqlite/msvc12/sm_sqlite.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/topmenus/msvc12/topmenus.vcxproj /p:configuration=Release
"%NETFRAME%\MSBuild" ../extensions/updater/msvc12/updater.vcxproj /p:configuration=Release

"%NETFRAME%\MSBuild" ../extensions/tf2/msvc12/tf2.vcxproj /p:configuration="Release - Orange Box Valve"
"%NETFRAME%\MSBuild" ../extensions/cstrike/msvc12/cstrike.vcxproj /p:configuration="Release - CSS"
"%NETFRAME%\MSBuild" ../extensions/cstrike/msvc12/cstrike.vcxproj /p:configuration="Release - CS GO"

"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - CSS"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - CS GO"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - Orange Box"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - Orange Box Valve"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - Old Metamod"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - Left 4 Dead"
"%NETFRAME%\MSBuild"  ../extensions/sdkhooks/msvc12/sdkhooks.vcxproj /p:configuration="Release - Left 4 Dead 2"

"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - CSS"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - CS GO"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - Orange Box"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - Orange Box Valve"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - Old Metamod"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - Left 4 Dead"
"%NETFRAME%\MSBuild"  ../extensions/sdktools/msvc12/sdktools.vcxproj /p:configuration="Release - Left 4 Dead 2"

pause