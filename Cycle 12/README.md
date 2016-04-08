## DLL Injection

This project shifts gears (yet again) a little and looks into code injection, specifically injecting a DLL into another process.  This is a common technique used with malware authors and allows them to attempt to prevent detection.

Why I Care:

* Essential technique used by malware authors, understand how malware evades detection
* Builds on the foundation for more advanced malware analysis
* Explore persistence methods
* Explore Windows API

Three main ideas for this project:

* Malware uses the Windows API
* You can obtain a handle to another process and attempt to write to address space
* You can use a thread to begin execution - in this demo load a DLL

# Current Status

This code demonstrates a basic DLL injection.

# Future Work

* Process replacement
* Process hallowing
* APC Injection

# Environment

Windows 7 SP 1 x86

# Resources & Demo

Powerpoint slides are contained in this repository.

[YouTube](https://youtu.be/zh-NIh76Y-c)
