#!/usr/bin/env python3

import cgi

print("Content-Type: text/html\n")

form = cgi.FieldStorage()
num1 = form.getvalue("num1")
num2 = form.getvalue("num2")

try:
    result = int(num1) + int(num2)
except (TypeError, ValueError):
    result = "Invalid input. Please enter two numbers."

print(f"""
<html>
<head><title>Sum Result</title></head>
<body>
    <h1>Sum Result</h1>
    <p>The sum of {num1} and {num2} is: {result}</p>
    <p><a href="../index.html">Go back</a></p>
</body>
</html>
""")
