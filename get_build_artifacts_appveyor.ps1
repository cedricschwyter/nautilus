$apiUrl = 'https://ci.appveyor.com/api'
$token = '9ou7lloef1iiwqiuma58'
$headers = @{}
$headers['Authorization'] = "Bearer $token"
$headers["Content-type"] = "application/json"
$accountName = 'D3PSI'
$projectSlug = 'nautilus'
$downloadLocation = 'C:\projects\nautilus'
$project = Invoke-RestMethod -Method Get -Uri "$apiUrl/projects/$accountName/$projectSlug" -Headers $headers
$jobId = $project.build.jobs[0].jobId
$artifacts = Invoke-RestMethod -Method Get -Uri "$apiUrl/buildjobs/$jobId/artifacts" -Headers $headers
$artifactFileName = $artifacts[0].fileName
$version_appveyor = $env:APPVEYOR_BUILD_VERSION
$localArtifactPath = "$downloadLocation\nautilus-linux-rolling-$version_appveyor.zip"
Invoke-RestMethod -Method Get -Uri "$apiUrl/buildjobs/$jobId/artifacts/$artifactFileName" `
-OutFile $localArtifactPath -Headers @{ "Authorization" = "Bearer $token" }

$jobId = $project.build.jobs[1].jobId
$artifacts = Invoke-RestMethod -Method Get -Uri "$apiUrl/buildjobs/$jobId/artifacts" -Headers $headers
$artifactFileName = $artifacts[0].fileName
$version_appveyor = $env:APPVEYOR_BUILD_VERSION
$localArtifactPath = "$downloadLocation\nautilus-macos-rolling-$version_appveyor.zip"
Invoke-RestMethod -Method Get -Uri "$apiUrl/buildjobs/$jobId/artifacts/$artifactFileName" `
-OutFile $localArtifactPath -Headers @{ "Authorization" = "Bearer $token" }