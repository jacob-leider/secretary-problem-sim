# secretary-problem-sim
This simple program simulates the secretary problem (https://en.wikipedia.org/wiki/Secretary_problem) and compares different stopping rules.

# Description
The most basic form of the secretary problem poses the following scenario: Given a random permutation of an ordered sequence `nums`, a _strategy_ is an algorithm that selects an element of `nums`, but may only read elements in the given order, and can only select the current element. 

The problem then follows: Which strategy maximizes the probability of selecting the maximum element?

This program studies a class of algorithms characterized by a "stopping ratio" `r`. An algorithm in this class rejects the first $\lfloor$ `r * n` $\rfloor$ elements, and stops at the next index containing the largest element seen so far. As it turns out, this class of strategies contains the optimal strategy as defined by the secretary problem, and the optimal stopping ratio `r` is equal to $1/e$.

# Use
This program simulates strategies for a sequence of evenly spaced stopping ratios. The strategies are evaluated over a number of random input sequences, and their success rate is reported. Parameters such as the number of trials, the length of a given input sequence, the bounds for stopping ratios, and the number of stopping ratio can be set in the main method before compilation (I see no need to overcomplicate things since this program is very concise).
