# Social Network Graph Engine in C

Coursework project developed for Data Structures and Algorithms.

## Overview
This console application models a simplified social network using undirected graphs in C. Users and friendship relations are loaded from input files into a dynamically allocated adjacency matrix, allowing real-time relationship management and graph traversal.

## Core Features
* Direct Friendship Verification: Checks immediate connections between two user IDs via the adjacency matrix.
* Degree Centrality Count: Computes the total number of friends for any selected user.
* Isolated Nodes Detection: Identifies inactive or disconnected users with zero friends across the network.
* Transitive Closure via Roy-Warshall: Determines whether an indirect path exists between two users through mutual acquaintances.
* Dynamic Edge Management: Adds or removes friendships in memory and automatically persists updates back to the network file.
* Breadth-First Search Post Diffusion: Simulates how a post spreads level by level across connected users using a custom FIFO queue and a visited array.
* Safe Dynamic Memory Management: Allocates 2D arrays and structs dynamically on startup and frees all heap allocations on exit.

## Repository Contents
* Grafuriprietenie.c: Main C source code implementing graph algorithms, queue operations, and the CLI menu.
* retea.txt: Graph edge list defining the initial nodes and connections.
* utilizatori.txt: Mapping of user IDs to individual names.
* Tema_Grafuri.docx: Test run documentation detailing scenario executions and terminal outputs.

## How to Compile and Run

### On Linux or WSL via GCC:
```bash
gcc Grafuriprietenie.c -o social_network
./social_network
