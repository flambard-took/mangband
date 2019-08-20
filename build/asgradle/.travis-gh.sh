#!/bin/sh

CLIENT_D=build/asgradle/mangclient/build/outputs/debug/mangclient-debug.apk
CLIENT_R=build/asgradle/mangclient/build/outputs/release/mangclient-release-unsigned.apk

CLIENT_D_NAME=$(basename ${CLIENT_D})
CLIENT_R_NAME=$(basename ${CLIENT_R})

cat <<"HTML"
<html>
<title>MAngband Android builds</title>
<head><meta charset="utf-8"/></head>
<body>
HTML
echo "<p><a href='${CLIENT_D}'>${CLIENT_D_NAME}</a></p>"
echo "<p><a href='${CLIENT_R}'>${CLIENT_R_NAME}</a></p>"
echo Built on $(date)
cat <<"HTML"
</body>
</html>
HTML
