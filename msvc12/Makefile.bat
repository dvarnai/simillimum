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

pause