 CS 225 Data Structures
## Project Proposal (annaik2-zubairl2-ravyus2-adithya9)

1. **Leading Question** Can we utilize file dependencies in order to create a dependency graph that allows for easier control flow management? 
2. **Dataset Acquistion and Processing** The dataset we are using really isn't a dataset, but a repository instead. To trace file dependencies, we will specifically be checking *#include* header guards, using our very own text parser in C++. We will be using Dirent to navigate through directories and get the necessary files to start up the dependency graph.
3. **Graph Algorithms** For our graph traversal, we propose to implement a Depth First Search (DFS). We expect the input to the actual graph constructor to be the file we wish to start at, upon where we will begin to search for the dependencies that said file contains. 
For one of our algorithms, we will be implementing Layered Graph Drawing to visualize all the file nodes. To actually go forward with said algorithm, we will be using the GraphViz graphics library to actually draw the graph. Our layered graph drawing will consist of:

   - Our very own drawing algorithm that decides where to place nodes in the image
   - Node coloring that allows for easier visualization of cycles in the dependency graph

   For our final algorithm, we are planning to use a watered-down version of Tarjan's cycle detection algorithm with DFS. Using this, we can identify cyclical dependencies by using a DFS search through visited nodes to find strongly connected components.
1. **Timeline**    
   April 9 - submit project proposal and team contract
   
   April 11 - set up initial repository and Makefile and decide what testing repositories to use
   
   April 13 - finalize code breakdown (classes that we need, methods that we use)

   April 15 - try to set GraphViz up
   
   April 18 - implement text parser
   
   April 20 - implement file explorer with Dirent
   
   April 25 - write up Tarjan's cycle detection
   
   May 5 - write Layered Graph Drawing
   
   May 7 - finish up testing

   May 9 - write up documentation and results of project
   
   May 11 - record, edit and submit presentation