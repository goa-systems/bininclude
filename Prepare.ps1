if(Test-Path -Path "out"){
	Remove-Item -Path "out" -Force -Recurse
}
New-Item -Path "out" -ItemType "Directory"