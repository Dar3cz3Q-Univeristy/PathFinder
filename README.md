# PathFinding

Program that searches for a path between 2 points in a maze.

## Available algorithms:
- Dijkstra,
- A*
	1. Euclidean distance,
	1. Manhattan distance,
	1. Taxi distance,
- DFS
- BFS

## Maze
The maze to be solved should be in the file. The character definition is as follows.

| Symbol | Definition  |
|:------:|------------ |
|        | Empty space |
|x       | Wall        |
|A       | Start       |
|B       | Finish      |

Program converts **maze** to **weighted undirected graph** and then runs path finding algorithms on the graph.

Results are saved to file which name is ```resolved.{given file name}```

## Example
### Maze file
```
A xxxxxxxxxxxxxxxxxxx
    x     x   x     x
x x x xxx xxx x x xxx
x x   x         x   x
xxxxxxxxxxx xxxxx xxx
x x             x   x
x x xxxxxxx x xxxx xx
x     x     x x     x
x xxx x x x x xxx xxx
x x   x x x x   x   x
x x xxx xxx x xxxxx x
x x x   x x x x x   x
x x x x x xxx x   xxx
x   x x   x     x   x
x x xxx x xxxxx x xxx
x x     x x         x
x xxxxxxx x xxx xxx x
x x   x       x x   x
x x xxxxxxx x x xxxxx
x           x x      
xxxxxxxxxxxxxxxxxxx B
```
### Console output
```
Provide a file name: labirynt_v3.txt
Choose a metric up to A*
1. Euclidean distance
2. Manhattan distance
3. Taxi distance
Choice: 2
Initializing maze
Maze initialized
A xxxxxxxxxxxxxxxxxxx
    x     x   x     x
x x x xxx xxx x x xxx
x x   x         x   x
xxxxxxxxxxx xxxxx xxx
x x             x   x
x x xxxxxxx x xxxx xx
x     x     x x     x
x xxx x x x x xxx xxx
x x   x x x x   x   x
x x xxx xxx x xxxxx x
x x x   x x x x x   x
x x x x x xxx x   xxx
x   x x   x     x   x
x x xxx x xxxxx x xxx
x x     x x         x
x xxxxxxx x xxx xxx x
x x   x       x x   x
x x xxxxxxx x x xxxxx
x           x x
xxxxxxxxxxxxxxxxxxx B

Analyzing maze
Vertexes added

A.xxxxxxxxxxxxxxxxxxx
.. .x.   .x. .x. . .x
x x x xxx xxx x x xxx
x.x. .x. . . . .x. .x
xxxxxxxxxxx xxxxx xxx
x.x.       . . .x...x
x x xxxxxxx x xxxx xx
x. . .x. . .x x. ...x
x xxx x x x x xxx xxx
x x. .x x.x x. .x. .x
x x xxx xxx x xxxxx x
x x x. .x.x.x x.x. .x
x x x x x xxx x. .xxx
x. .x.x. .x. . .x. .x
x x xxx x xxxxx x xxx
x x.   .x x.   . . .x
x xxxxxxx x xxx xxx x
x x. .x. . . .x x. .x
x x xxxxxxx x x xxxxx
x. .       .x.x.   ..
xxxxxxxxxxxxxxxxxxx.B


Finding path
BFS done. Time saved to: time.log
Dijkstra done. Time saved to: time.log
A* done. Time saved to: time.log
DFS done. Time saved to: time.log
Results saved to: resolved.labirynt_v3.txt
```
### Results file
```
Path found by: BFS algorithm.
0.0 -> 1.1 -> 1.3 -> 3.3 -> 3.5 -> 1.5 -> 1.9 -> 3.9 -> 3.11 -> 5.11 -> 5.13 -> 9.13 -> 13.13 -> 13.15 -> 15.15 -> 19.15 -> 19.19 -> 20.20
Total length: 42.8284
Total steps: 17
    
A xxxxxxxxxxxxxxxxxxx
 ###x#####x   x     x
x x#x#xxx#xxx x x xxx
x x###x  ###    x   x
xxxxxxxxxxx#xxxxx xxx
x x        ###  x   x
x x xxxxxxx x#xxxx xx
x     x     x#x     x
x xxx x x x x#xxx xxx
x x   x x x x#  x   x
x x xxx xxx x#xxxxx x
x x x   x x x#x x   x
x x x x x xxx#x   xxx
x   x x   x  ###x   x
x x xxx x xxxxx#x xxx
x x     x x    #    x
x xxxxxxx x xxx#xxx x
x x   x       x#x   x
x x xxxxxxx x x#xxxxx 
x           x x#####  
xxxxxxxxxxxxxxxxxxx B 

Path found by: Dijkstra algorithm.
0.0 -> 1.1 -> 1.3 -> 3.3 -> 3.5 -> 1.5 -> 1.9 -> 3.9 -> 3.11 -> 5.11 -> 5.13 -> 9.13 -> 13.13 -> 13.15 -> 15.15 -> 19.15 -> 19.19 -> 20.20
Total length: 42.8284
Total steps: 17

A xxxxxxxxxxxxxxxxxxx
 ###x#####x   x     x
x x#x#xxx#xxx x x xxx
x x###x  ###    x   x
xxxxxxxxxxx#xxxxx xxx
x x        ###  x   x
x x xxxxxxx x#xxxx xx
x     x     x#x     x
x xxx x x x x#xxx xxx
x x   x x x x#  x   x
x x xxx xxx x#xxxxx x
x x x   x x x#x x   x
x x x x x xxx#x   xxx
x   x x   x  ###x   x
x x xxx x xxxxx#x xxx
x x     x x    #    x
x xxxxxxx x xxx#xxx x
x x   x       x#x   x
x x xxxxxxx x x#xxxxx 
x           x x#####  
xxxxxxxxxxxxxxxxxxx B 

Path found by: A* algorithm.
0.0 -> 1.1 -> 1.3 -> 3.3 -> 3.5 -> 1.5 -> 1.9 -> 3.9 -> 3.11 -> 5.11 -> 5.13 -> 9.13 -> 13.13 -> 13.15 -> 15.15 -> 19.15 -> 19.19 -> 20.20
Total length: 42.8284
Total steps: 17

A xxxxxxxxxxxxxxxxxxx
 ###x#####x   x     x
x x#x#xxx#xxx x x xxx
x x###x  ###    x   x
xxxxxxxxxxx#xxxxx xxx
x x        ###  x   x
x x xxxxxxx x#xxxx xx
x     x     x#x     x
x xxx x x x x#xxx xxx
x x   x x x x#  x   x
x x xxx xxx x#xxxxx x
x x x   x x x#x x   x
x x x x x xxx#x   xxx
x   x x   x  ###x   x
x x xxx x xxxxx#x xxx
x x     x x    #    x
x xxxxxxx x xxx#xxx x
x x   x       x#x   x
x x xxxxxxx x x#xxxxx 
x           x x#####  
xxxxxxxxxxxxxxxxxxx B 

Path found by: DFS algorithm.
0.0 -> 1.1 -> 1.3 -> 3.3 -> 3.5 -> 1.5 -> 1.9 -> 3.9 -> 3.11 -> 3.13 -> 3.15 -> 1.15 -> 1.17 -> 3.17 -> 5.17 -> 5.18 -> 7.18 -> 7.17 -> 9.17 -> 9.19 -> 11.19 -> 11.17 -> 12.17 -> 12.15 -> 13.15 -> 13.13 -> 9.13 -> 5.13 -> 5.11 -> 5.3 -> 7.3 -> 7.1 -> 13.1 -> 13.3 -> 15.3 -> 15.7 -> 13.7 -> 13.9 -> 17.9 -> 17.11 -> 15.11 -> 15.15 -> 19.15 -> 19.19 -> 19.20 -> 20.20
Total length: 109.414
Total steps: 45

A xxxxxxxxxxxxxxxxxxx
 ###x#####x   x###  x
x x#x#xxx#xxx x#x#xxx
x x###x  #######x#  x
xxxxxxxxxxx xxxxx#xxx
x x###########  x## x
x x#xxxxxxx x#xxxx#xx
x###  x     x#x  ## x
x#xxx x x x x#xxx#xxx
x#x   x x x x#  x###x
x#x xxx xxx x#xxxxx#x
x#x x   x x x#x x###x
x#x x x x xxx#x###xxx
x###x x###x  ###x   x
x x#xxx#x#xxxxx x xxx
x x#####x#x#####    x
x xxxxxxx#x#xxx#xxx x
x x   x  ###  x#x   x
x x xxxxxxx x x#xxxxx 
x           x x###### 
xxxxxxxxxxxxxxxxxxx B 
```

## Running program
### Visual Studio
Download repository and just run **Local Windows Debugger**. Program will ask for file location etc.

## Resources
* https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
* https://en.wikipedia.org/wiki/A*_search_algorithm
* https://en.wikipedia.org/wiki/Depth-first_search
* https://en.wikipedia.org/wiki/Breadth-first_search
