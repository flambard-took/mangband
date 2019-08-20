#!/bin/sh

CLIENT_D=mangclient-debug.apk
CLIENT_R=mangclient-release-unsigned.apk

cat <<"HTML"
<html>
<title>MAngband Android builds</title>
<head><meta charset="utf-8"/></head>
<body>
HTML
echo "<p><a href='${CLIENT_D}'>${CLIENT_D}</a></p>"
echo "<p><a href='${CLIENT_R}'>${CLIENT_R}</a></p>"
echo Built on $(date)
cat <<"HTML"
</body>
</html>
HTML
