#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Import the necessary modules
import cgi

# Create an instance of the FieldStorage class to handle input from the form
form = cgi.FieldStorage()

# Get the value of the 'name' parameter from the form
name = form.getvalue('name')

# Print the Content-Type header
print("Content-Type: text/html\n")

# Start the HTML response
print("<html>")
print("<head>")
print("<title>Simple CGI Example</title>")
print("</head>")
print("<body>")
print("<h1>Hello, {}!</h1>".format(name if name else "World"))
print("</body>")
print("</html>")

