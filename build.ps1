$ModName = "MasPuertas"
$VersionFile = "MoreDoors\scripts\3_game\version.c"
$ModCppFile = "mod.cpp"

$ErrorActionPreference = "Stop"

$version = $(git describe --tags --dirty)
$rawVersion = $version -replace "^v",""

$originalVersion = (Get-Content -path "$VersionFile" -raw)
$originalModCpp = (Get-Content -path "$ModCppFile" -raw)

if (Test-Path "P:\@${ModName}") { Remove-Item -Recurse "P:\@${ModName}" }

New-Item -Type Directory "P:\@${ModName}" | Out-Null
New-Item -Type Directory "P:\@${ModName}\Addons" | Out-Null
New-Item -Type Directory "P:\@${ModName}\Keys" | Out-Null

$originalVersion -replace "\bdev\b","$version" | Set-Content -path "$VersionFile" -NoNewLine
$originalModCpp -replace "\bdev\b","$rawVersion" | Set-Content -path "$ModCppFile" -NoNewLine

& "$((Get-ItemProperty -Path "HKCU:\Software\bohemia interactive\Dayz Tools").path)\Bin\AddonBuilder\AddonBuilder.exe" "P:\${ModName}\MoreDoors" "P:\@${ModName}\Addons" "-clear" "-project=P:\${ModName}" "-sign=$env:BIPRIVATEKEY_PATH" "-packonly" "-include=include.lst"
$buildcode = $lastexitcode
$builderror = $errorMessage

Copy-Item "description.txt" -Destination "P:\@${ModName}\README.txt"
Copy-Item "mod.cpp" -Destination "P:\@${ModName}\mod.cpp"

Set-Content -Path "$VersionFile" -Value "$originalVersion" -NoNewLine
Set-Content -Path "$ModCppFile" -Value "$originalModCpp" -NoNewLine

if ($buildcode -ne 0) { throw ("Exec: " + $builderror) }

Copy-Item $env:BIKEY_PATH -Destination "P:\@${ModName}\Keys"
