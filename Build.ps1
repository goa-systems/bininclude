Get-ChildItem -Path "src" | Where-Object {$_.Name -match "(.*)\.c"} | ForEach-Object {
	
	$Source = "$($_.FullName)"
	$Destination = "out\$($_.BaseName).o"

	Write-Host -Object "Building ${Source} into ${Destination}"
	Start-Process -FilePath "gcc.exe" -ArgumentList @("-Wall", "-ansi", "-pedantic", "-c", "-g", "-o", "${Destination}", "${Source}") -NoNewWindow -Wait
}