## Inline API Hooking

For the final cycle I will be extending my DLL injection example to explore the process of inline API Hooking.  In this demo, we will establish the foundations for inline API hooking.

Why I Care:

* Common technique used by malware in both user-mode and kernel-mode
* Allows us to understand how execution of a program can be modified
* Allows us to continue to explore Windows API

Three main ideas for this project:

* If a program has write-access to a process' address space, it can overwrite memory to subvert the flow of a program
* Hooks can be installed through code or DLL injection
* Hooks are often used by banking trojans to steal banking information - credentials submitted through the browser before it is encrypted
* This is just a demo and there are likely additional considerations when tryign to do this outside of a debugger (see SeDebugPrivilege)
* If this interests you, read Practical Malware Analysis

# Current Status

This code demonstrates the foundations for inline API hooking

# Future Work

* Implement the long jump to the hooked function
* Clean-up from the hooked function and return to the originally called function
* Test in real-world environments
* Contrast and compare to minHook

# Environment

Windows 7 SP 1 x86

# Resources & Demo

Powerpoint slides are contained in this repository.

[YouTube]()
