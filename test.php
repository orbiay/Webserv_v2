<?php
  // Start the session
  session_start();

  // Increment the counter variable
  $_SESSION['counter'] = $_SESSION['counter'] + 1;

  // Output the counter value
  echo "You are visitor number " . $_SESSION['counter'];
?>
