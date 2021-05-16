# annaik2-zubairl2-ravyus2-adithya9

# Dependency Graph

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

**Authors**:\
            Zubair Lalani - [`zubairl2@illinois.edu`](mailto:zubairl2@illinois.edu)\
            Adithya Swaminathan - [`adithya9@illinois.edu`](mailto:adithya9@illinois.edu)\
            Ravyu Sivakumaran - [`ravyus2@illinois.edu`](mailto:ravyus2@illinois.edu)\
            Atharva Naik - [`annaik2@illinois.edu`](mailto:annaik2@illinois.edu)

### Overview
 At its core, this project is meant to be a tool that will allow developers to visualize the dependencies within their projects. Often when tackling a large open source repositories, it can be difficult to understand the control flow of the project. Our project mitigates this difficulty by allowing the users to create a dependency graph.
 
 Features include:
 - DFS iteration of repository
 - Text parsing for include statements within C++ files
 - Creation of dependency graph (with the choice of using our custom made layered graph drawing algorithm or the algorithm used by graphviz)
 - Detection of cyclical dependencies within repository
 - Cyclical dependencies are represented as colored nodes

### Dependencies   
Running the application will require (note that all of these libraries are already installed on EWS):
- CMake
- Graphviz (Graph rendering library)
- Dirent (File management library)
- Catch2 (C++ testing library)

### Dataset
Our fullscale dataset is a graphics library called Cinder. The `setup.sh` file will pull the Cinder submodule using `git submodule init` and `git submodule update`, which means that no additional setup for the submodule is needed. It might take a while, however, for git to pull the entire library.

### Quickstart
1) In the outermost directory run: `. ./setup.sh` or `source ./setup.sh`
2) The setup may take a bit because it also downloads our dataset (Cinder graphics library is added as a submodule)
3) A build folder should appear (and it should automatically change your directory to the build folder). If you are not in the build folder, cd into it using `cd build`.
4) Although the setup script already should have created an out_ours.png file that contains our dependency graph in the build folder, you can rerun the project by calling the function `draw_cinder_graph`
5) There is also an out.png file that gets created that uses graphviz's built in layered graph drawing algorithm
6) Note: If for some reason the function draw_graph does not work, you can call:
   1) `make CinderGraphGen`
   2) `./CinderGraphGen`
   3) `neato -n -Tpng graph.dot -o out_ours.png`
   4) Then the `out_ours.png` file should be within the build folder
   5) You can run graphviz's built-in layered graph drawing algorithm by running `dot -Tpng graph.dot -o out.png`
7) The above instructions will create the graph for the Cinder library

### Running Tests
1) Make sure you're still in the `build` directory (see above for instructions)
2) Run `make test`
3) Run `./test`
4) There are a number of filters you can use to run specific tests
   1) `./test [f]` will run file explorer tests
   2) `./test [t]` will run test parser tests
   3) `./test [g]` will run graph generator tests
   4) `./test [c]` will run cycle detector tests

### Link to Presentation Video
You can find a short presentation explaining our process [here](https://drive.google.com/file/d/1tvbI-P81BVucdms62X9I_vqokFM5YPqN/view?usp=sharing)
