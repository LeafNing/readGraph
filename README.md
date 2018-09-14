# readGraph
Deal with the dataset we've got from the network

##Command:
readGraph.exe [option] [dataset filename]

###Options:
1. -u  generate graph with uniform weights and labeled ties
2. -node loading nodes information
3. -rv reverse original graph
4. -find find maximum node id
5. -tie add a label(strong or weak) of every edge in the graph

###Example:
readGraph.exe -u lastFM_tag.txt
