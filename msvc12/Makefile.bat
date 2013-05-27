@echo off

rm -r -f "../Release"

mkdir "../Release/addons/simillimum/bin"
mkdir "../Release/addons/simillimum/data/sqlite"
mkdir "../Release/addons/simillimum/extensions"
mkdir "../Release/addons/simillimum/logs"
mkdir "../Release/addons/metamod"

cp -r -f "../translations" "../Release/addons/simillimum/translations"
cp -r -f "../configs" "../Release/addons/simillimum/configs"
cp -r -f "../gamedata" "../Release/addons/simillimum/gamedata"
cp -r -f "../plugins" "../Release/addons/simillimum/scripting"
cp -r -f "../plugins_lua" "../Release/addons/simillimum/plugins_lua"
cp -r -f "../configs/cfg" "../Release"
cp -f "../simillimum.vdf" "../Release/addons/metamod/simillimum.vdf"

rm -r -f "../Release/addons/simillimum/configs/cfg"


cd "../plugins/"

compile.exe
rm -f "compile.dat"
mv -f "compiled" "../Release/addons/simillimum/plugins"

cd "../msvc12"


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



mv -f "../loader/msvc12/Release/"*.dll "../Release/addons/simillimum/bin/"
mv -f "../core/logic/msvc12/Release/"*.dll "../Release/addons/simillimum/bin/"
mv -f "../sourcepawn/jit/msvc12/Release/"*.dll "../Release/addons/simillimum/bin/"
mv -f "../lua/msvc12/Release/"*.dll "../Release/addons/simillimum/bin/"
mv -f "../core/msvc12/"Release*/*.dll "../Release/addons/simillimum/bin/"
mv -f "../extensions/"*"/msvc12/"Release*/*.dll "../Release/addons/simillimum/extensions/"

rm -f -r "../extensions/"*"/msvc12/"Release*
rm -f -r "../core/msvc12/"Release*
rm -f -r "../loader/msvc12/Release"
rm -f -r "../core/logic/msvc12/Release"
rm -f -r "../sourcepawn/jit/msvc12/Release"
rm -f -r "../lua/msvc12/Release"

pause