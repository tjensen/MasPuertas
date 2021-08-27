$ModName = "MasPuertas"

$ErrorActionPreference = "Stop"

if (Test-Path "P:\@${ModName}") { Remove-Item -Recurse "P:\@${ModName}" }

New-Item -Type Directory "P:\@${ModName}" | Out-Null
New-Item -Type Directory "P:\@${ModName}\Addons" | Out-Null
New-Item -Type Directory "P:\@${ModName}\Keys" | Out-Null

& "$((Get-ItemProperty -Path "HKCU:\Software\bohemia interactive\Dayz Tools").path)\Bin\AddonBuilder\AddonBuilder.exe" "P:\${ModName}" "P:\@${ModName}\Addons" "-clear" "-project=P:\${ModName}" "-sign=$env:BIPRIVATEKEY_PATH" "-binarizeFullLogs" "-packonly" "-include=include.lst"
$buildcode = $lastexitcode
$builderror = $errorMessage

if ($buildcode -ne 0) { throw ("Exec: " + $builderror) }

Copy-Item $env:BIKEY_PATH -Destination "P:\@${ModName}\Keys"
