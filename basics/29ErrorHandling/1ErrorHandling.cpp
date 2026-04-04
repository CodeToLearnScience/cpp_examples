/*
--------------------------------
Error Handling
--------------------------------
- These are the things that can go wrong at run time, when your program
interacts with the real world
- Even perfect code may suffer from errors in the real world
  * Trying to read from a file that does not work
  * Trying to send data over a network connection that is down
  * Receiving data which is incorrect or in the wrong format
- These are situations which arise at runtime when the environment does not
behave as expected
- In basic programs, we can just print out a message and exit. For serious
programs, we need to do better

--------------------
Error Communication
--------------------
- Communicate with the user
  * Tell user what the problem is and what they can do about it
  * Give opportunity to retry, resolve, or ignore as appropriate
  * If necessary, notify other concerned parties
- Avoid information which is not helpful to the user
  * "Error xxxx occured. Please consult the manual"
  * Java stack trace
- Only exit the program as last resort

-------------------------------
Where to Handle Errors
-------------------------------
- Often, errors can be handled where they occur. Quite often that is good enough
e.g. if you are asking for user input and they type in something which is in the
wrond format
- Sometimes, it is useful to handle errors in a different part of the code from
where the error occured
- e.g. if we want to display a dialogue box when there is an error in a file
download. Here if we decide to handle where they occur, it will be repetion of
lots of GUI dialogue box code to display error and which will be mixed up with
the actual logic. That may not be good. In those cases, we can handle error
separately
- We should not mix up GUI code with networking code
  * IT makes the code more complicated
  * The error Handling code is a distraction from the networking logic
  * Error Handling code is spread all over the program

-------------------------------
High Level Error Handling
-------------------------------
- A better approach is to have these errors handled at a higher level
  * If we have an error which needs to be handled with GUI code, this should go
    in the user interface part of the code
- The error needs to be passed from the place where the error occured to the
code that handles it
*/
