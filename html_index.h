const char HTML_INDEX[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiDash Dashboard</title>
</head>
<body>
    <h1>WiDash Dashboard</h1>
    <div>
        <h2>Current Network</h2>
        <p><strong>SSID:</strong> {{SSID}}</p>
        <p><strong>Signal Strength:</strong> {{RSSI}} ({{RSSI_PERCENT}})</p>
        <p><strong>Time:</strong> {{TIME}}</p>
    </div>

    <div>
        <h2>Available Networks</h2>
        <p>{{NETWORK_LIST}}</p>
    </div>

    <div>
        <h2>Available Pages</h2>
        <ul>
            <li><a href="/sensors">Sensors</a></li>
            <li><a href="/networks">Networks</a></li>
            <li><a href="/status">Status</a></li>
        </ul>
    </div>
</body>
</html>
)rawliteral";
