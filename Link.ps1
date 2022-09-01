$ObjectFiles = ""
Get-ChildItem -Path "out" | Where-Object {$_.Name -match "(.*)\.o"} | ForEach-Object {
	$ObjectFiles = "$($_.Fullname) $ObjectFiles"
}
$ObjectFiles = $ObjectFiles.TrimEnd()
Write-Host -Object "Linking files $ObjectFiles together."
Start-Process -FilePath "gcc.exe" -ArgumentList @("-g", "-o", "out\main.exe", "$ObjectFiles", "-lole32") -NoNewWindow -Wait
