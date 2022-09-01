Get-ChildItem -Path "." | Where-Object {$_.Name -match "(.*)\.c"} | ForEach-Object {
	Start-Process -FilePath "gcc.exe" -ArgumentList @("-Wall", "-ansi", "-pedantic", "-c", "-g", "-o", "out\$($_.BaseName).o", "$($_.FullName)") -NoNewWindow -Wait
}