const char HTML_STATUS[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Status</title>
</head>
<body>
    <h1>Status</h1>
    <div>
        <h2>Current Network</h2>
        <p><strong>SSID:</strong> {{SSID}}</p>
        <p><strong>Signal Strength:</strong> {{RSSI}} ({{RSSI_PERCENT}})</p>
        <p><strong>IP:</strong> {{IP}}</p>
        <p><strong>Time:</strong> {{TIME}}</p>
    </div>

    <div>
        <a href="/">Back to Dashboard</a>
    </div>
</body>
</html>
)rawliteral";
