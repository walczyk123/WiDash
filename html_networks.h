const char HTML_NETWORKS[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Networks</title>
</head>
<body>
    <h1>Available Networks</h1>
    <div>
        <ul>
            {{NETWORK_LIST}}
        </ul>
    </div>

    <div>
        <a href="/">Back to Dashboard</a>
    </div>
</body>
</html>
)rawliteral";
