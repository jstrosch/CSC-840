## Hooking vTables

This project focused on hooking vtables in a sample C++ program.  I have three reasons for performing this research:

* Dissertation research is focused on reverse engineering and security vulnerability discovery
* Understand how to better secure software
* More advanced understanding of dynamic and static tools as well as Windows API

Three main ideas for this project:

* It is difficult to defend applications when an attacker has the program
** Even when it’s just binary data
* Windows API allows for a tremendous amount of flexibility and can be leveraged directly
* Indirect calls can lead to security vulnerabilities/exploitation


# Current Status

The current status of this work is that the code is able to successfully hook the vtable in the sample program when run under a debugger, but fails (crashes) when run without.

# Future Work

*Understand further mitigations that would prevent vTable hooking such as Control Flow Guard in Windows 10 and 8.1
*Accomplishing vTable hooking through DLL injection on a running process
*Accomplish vTable hooking by DLL injection at load time
*Explore new mitigation techniques


# Environment

I compiled the program using Visual Studio 2015 Command Line Tools

```
  C:\> cl tester.cpp
```

# Demo

[YouTube](http://www.youtube.com/watch?v=rImRS-6JGEw)

