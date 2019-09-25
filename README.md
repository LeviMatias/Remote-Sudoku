# TP1-Remote-Sudoku
Console app

Task: 
Create a remote sudoku with a single server and a single client.
The server is in charge of managing and sending to the client all the data and visualizations pertaining the sudoku
while the client must use a predefined set of commands to request data from the server

Commands:
GET // returns the board
PUT <X> in <L>,<C> // puts x in line L and column C
VERIFY // returns if the current state of the board is correct
EXIT // end

Main objective:
Implement the whole program using RAII
Manage the use of a std::stocket

Overall design structure
![alt text](https://github.com/LeviMatias/TP1-Remote-Sudoku/blob/master/diagram.png)
