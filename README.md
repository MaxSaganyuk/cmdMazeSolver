# cmdMazeSolver
Simple command line maze solver

## _How to use_

In command line enter

```
cmdMazeSolver.exe x y give_true
```
- x - amount of 0/1 in x axis
- y - amount of 0/1 in y axis
- give_true - if 1, force random maze creatiion loop to be solvable by creating mazes until it is solvable

Example below:

<img src="readMeImages\1.png"></img>

If give_true = 1:

<img src="readMeImages\2.png"></img>

For give_true 1 - maximum optimal size is 29, 30 or more might take time to properly generate 

<img src="readMeImages\3.png"></img>

But the algorithm itself works for larger mazes. You can input the maze from txt the file of any size supported. Like this:

<img src="readMeImages\4.png"></img>

To input from file, file must be named matrix.txt and write

```
cmdMazeSolver.exe -1
```
If file was created properly, program will determine the size of the matrix automatically 
