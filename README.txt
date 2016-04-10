Bao Nguyen (btn2105)
Alice Rottersman (arr2174)
COMS W4112-Project 2 (Part 1)


This program creates a pointer free tree index and for a set of probes,the index is probed
using binary search for each node. The range identifier for each probe is found and printed out.

To run:
  Compile the program with command: make all
  Once compiled, run the code with: ./build K P <fanouts>
  Example of usage: "./build 100 4 5 9 5 " will build a three-level tree with fanouts 5,9, and 5
  and have 100 unique keys inserted into it. It will then generate P random probes, and the
  corresponding range identifier for each will be found and outputted.
