## Control Flow Guard

This project extends my work from cycle 3 and explores how Control Flow Guard (CFG) implemented in Windows 10 and Windows 8.1 Update 3 attempts to mitigate indirect-call sites.  My primary motivation for this work is as follows:

* Dissertation research is focused on reverse engineering and security vulnerability discovery
* CFG is latest efforts by Microsoft to reduce attack surface in Windows Operating System
* How effective is CFG? How can we get around it?

Three main ideas for this project:

* How does CFG work?  What is the difference between a binary using CFG and those that are not
* Is CFG effective?
** What gaps does it fill in exploit mitigation?
* Are there ways to bypass CFG?
** What gaps does it not feel or leave behind?


# Current Status

The current status of this work is that the code is able to successfully hook the vtable in the sample program when run under a debugger, but fails (crashes) when run without.  This cycle does not make any code changes to the project source code.

# Future Work

*How is the CFGBitMap created
*Explore other avenues of bypass for CFG
** Can I get ROP to work?
*What else could be created to fill “gaps” left by CFG?
*Explore new mitigation techniques


# Environment

I compiled the program using Visual Studio 2015 Command Line Tools

```
  C:\> cl /guard:cf tester.cpp /link /guard:cf
```

# Resources & Demo

Powerpoint slides are contained in this repository.

[YouTube](http://www.youtube.com/watch?v=Qhknlaor7aE)

