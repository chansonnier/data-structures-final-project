# CSCI 2270: Data Structures - Final Project
## Project Summary
The goal of this project was to compare a set of data structures to find the one that strikes the best balance in run-time performance in a fictitious contagion tracking application. The candidate data structures were doubly-linked lists and three variants of hash table. The three hash tables vary in their means of collision resolution: a hash table with a linear probing open addressing scheme for collision resolution, another with a quadratic probing open addressing scheme, and another using linked-list chaining for collision resolution.

Two data sets were provided, both of which had to be run through our implementations of the requested data structures. The instructions were to 1) implement each of the data structures, 2) plot the data structures' insert and search performance against each other (in addition to insert collision performance and search collision performance for the hash table variants), and 3) write a report to analyze their performance, summarize the findings, and give a recommendation for an optimal data structure for the contagion tracking application's handling of patient ID numbers. 

We were allowed to choose any plotting tool or library, so I used matplotlib with NumPy in iPython Notebooks/Jupyter Notebooks to create the plots required for the project. The `finalpaper.pdf` above was my final submission. 


## Directory structure
- [`source-cpp/`](./source-cpp) contains C++ implementations of each data structure. Those implementations operated on the provided data sets in:
- [`data-sets/`](./data-sets) to generate the CSV output files in: 
- [`performance-results-output-files/`](./performance-results-output-files), which were finally used by my iPython Notebooks, in: 
- [`jupyter-notebooks/`](./jupyter-notebooks) to create the performance plots required for the analysis.

[`Finalpaper.pdf`](./finalpaper.pdf) was the end result and my final submission (along with all the C++ implementations and driver files).
