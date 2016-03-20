## Heap Spray

This project shifts gears a little and looks into heap sprays. 

Why I Care:

* Heap Spray is a common technique associated withy UaF
* Heap spraying is a payload delivery technique
* Place payload in a predictable place in memory
* Provides underlying theory for more advanced exploitation techniques (bypasses)

Three main ideas for this project:

* What is the heap and how does it differ from the stack
* How to create a heap spray
* How to analyze your heap spray using a debugger - Immunity and WinDBG


# Current Status

This code demonstrates a basic heap spray - [source](https://www.corelan.be/index.php/2011/12/31/exploit-writing-tutorial-part-11-heap-spraying-demystified/).

# Future Work

* Look into DOM objects for more current attack techniques
* Extend example by looking into precise heap sprays
* Look into heap spray + UaF


# Environment

Windows XP SP3 and IE 6

# Resources & Demo

Powerpoint slides are contained in this repository.

[YouTube](https://youtu.be/kEk2HIRWjmE)

