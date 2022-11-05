Readme for OS Lab2
----------------------

This lab contains two parts each of which is solved in the two folders in the zip file.

File structure: 

Zip file -----
		|
		|
		|---OSLab2_1
		|	|-convert.cpp
		|	|-count.cpp
		|	|-driver.cpp
		|	|-input.txt
		|	
		|---OSLab2_2
			|-client.c
			|-server.c
			|- msgq.txt

The first part is solved in folder OSLab2_1 : convert.c, count.c and driver.c are the code files.
	
The second part is solved in folder OSLab2_2: client.c, server.c are the code files and msgq.txt is requires for ftok() in code.


Execution Status
-----------------

Problem 1: 

	* Handling input and output files			   -- Success

	* Implementing driver function with error handling -- Success

	* Implementation of Pipes				   -- Success



Problem 2:

	* Implementation of server functionality		    -- Success
	
	* Implementation of client functionality		    -- Success

	* Implementation of Message queue			    -- Success

	* Implementation of game logic			    -- Success


Usage
------

Problem 1:

	* Compile the code files using the commands given below:
		
		g++ driver.cpp -o driver
		
		g++ count.cpp -o count

		g++ convert.cpp -o convert

	* Now create an input file with any name. In above example input file is already made for you.

	* To run the code on the input file, run the following command:
		
		./driver input.txt output.txt

	* Note that in above command you can replace the input.txt and output.txt with your filename.

Problem 2: 

	* Compile the code files using the commands given below.

		g++ client.c -o client
		
		g++ server.c -o server

	* Run the code using the following command:

		./server

	* You can then enter number of clients, and the game starts.

	* You must then enter two Min and Max integers for the range separated by space until any one clients win.
	




