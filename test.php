<!DOCTYPE html>
<html>
<head>
	<title>Simple PHP Code Example</title>
</head>
<body>
	<form method="POST">
		<label>Enter your name:</label>
		<input type="text" name="name">
		<input type="submit" value="Submit">
	</form>

	<?php
		// Check if the form has been submitted
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			// Get the value of the input field with name="name"
			$name = $_POST["name"];

			// Display a message with the user's name
			echo "Hello, $name!";
		}
	?>
</body>
</html>
