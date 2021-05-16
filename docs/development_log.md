## Development Log

### Week 1

This week, we worked on overall setup of the project. We held meetings to talk about the structure of the code, and split up into subgroups that would be focusing on different tasks. It was ultimately decided that Ravyu would be working on setting up the GraphViz library, Atharva would begin to implement the graph interface, and Zubair and Adi would start looking into parsing the text for include statements, and using Dirent to move through the directiories. 

### Week 2

This is the week where the actual coding began. Whereas we just set up our classes last week, we started to actually split into teams and write code this week. Atharva implemented a Graph class, while Ravyu started looking into setting up GraphViz. Meanwhile, text parsing and file exploring is done, with just tests needed. After this the plan is to write tests, merge the individual branches, and link the graph interface into the text parsing portion of the code, and actually create the graph.

### Week 3

This week, we worked on integrating the graph interface into the text parsing portion of the code. We are now able to draw a basic dependency graph onto the screen. We are also working on implementing a DFS iterator for said dependency graph. After that, we will be splitting up into teams again in order to implement the actual algorithms (cycle detection and layered graph drawing). 

### Week 4

This week was more focused on the finishing touches to be put on the project. After being able to generate a basic graph on-screen, we worked on cycle detection and layered graph drawing. For this task, Adi worked on the cycle detection algorithm, while Zubair and Ravyu looked at performing layered graph drawing, using our own algorithm for GraphViz to use. Ravyu also worked on node coloring, where we would color nodes depending on if it is in a cycle or not. Meanwhile, Atharva worked on testing all the classes that we have implemented, and running the graph generator on [Cinder](https://github.com/cinder/Cinder) using a submodule. Currently, all that remains to be done are documentation, the RESULTS.md file, and the actual presentation itself.