# sorting-algorithms

### Variant 3: Sorting algorithms (Team 3)

Using C++ programming language and Qt framework implement a software project that represents a graphical user interface (GUI) based sorting algorithms demonstration and performance analysis software. The software must support the following functionalities:

- it must allow the input and sort of sequences of any length of the following basic data types: integers, floating-point numbers, strings;
- the software must implement and use the following sorting algorithms: selection sort, insertion sort, bubble sort, merge sort, quick sort;
- it can visualize the stages of each algorithm step-by-step;
    - copy the algorithm and print on each step TODO
    - max size=10
    - new window
    - /tk/ will implement the base and for selection sort, which will be used as an example for the rest.
- it measures the execution time of each algorithm for various number of elements of the input sequence;
    - convert depending on size TODO + fix not-updating sequence /rr/
- it displays the execution time of each algorithm for different input length of the sequence and allows visually to compare the complexity of the algorithms.
    - visualize the graph of each algorithm with some plugin TODO /at/
    - find a plugin to draw graphs
    - max n = 1M
    - the graph is always the same
    - when above is done we can think about putting a label where the current size is /OPTIONAL/

The program must have the following features:

- GUI to input sequence or to generate a random sequence;
- GUI to read and store sequences from and to files;
- GUI to demonstrate the execution of a given algorithm step-by-step;
- GUI to show complexity of algorithms and compare them.

Initials: Rado = rr Angel = at Ivon = in Tanyo = tk
# Tasks
- **GUI** Input/Generate sequence /in/
- Implement the data structure to hold the sequence /rr/
- **GUI** Implement Read/Write in files.
  - Read /tk/
  - Write /at/
- Implement sorting algorithms:
  - selection sort + measure execution time /in/
  - insertion sort + measure execution time /at/
  - bubble sort + measure execution time /rr/
  - merge sort + measure execution time /in/
  - quick sort /rr/
- **GUI** Display the measured time of each algorithm /at/
- **GUI** Visually compare the complexity /tk/
- Validate manual input and when reading files /tk/
