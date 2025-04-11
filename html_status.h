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
        <p><strong>MAC Address:</strong> {{MAC}}</p>
    </div>

    <div>
        <h2>Time and Uptime</h2>
        <p><strong>Time:</strong> {{TIME}}</p>
        <p><strong>Uptime:</strong> {{UPTIME}}</p>
    </div>

    <div>
        <h2>Power and System</h2>
        <p><strong>Free RAM:</strong> {{FREE_RAM}}</p>
        <p><strong>Max RAM:</strong> {{MAX_RAM}}</p>
        <p><strong>Flash Size:</strong> {{FLASH_SIZE}}</p>
        <p><strong>Max Flash Size:</strong> {{MAX_FLASH_SIZE}}</p>
        <p><strong>SDK Version:</strong> {{SDK_VERSION}}</p>
    </div>

    <div>
        <a href="/">Back to Dashboard</a>
    </div>
</body>
</html>
)rawliteral";
