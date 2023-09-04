# CxxWin

![Win-Msys2-UCRT64](https://github.com/StoneyDSP/CxxWin/actions/workflows/MSYS_UCRT64.yml/badge.svg)
![Win-Msys2-MINGW64](https://github.com/StoneyDSP/CxxWin/actions/workflows/MSYS_MINGW64.yml/badge.svg)
![Win-Msys2-CLANG64](https://github.com/StoneyDSP/CxxWin/actions/workflows/MSYS_CLANG64.yml/badge.svg)
![Win-Msys2-MINGW32](https://github.com/StoneyDSP/CxxWin/actions/workflows/MSYS_MINGW32.yml/badge.svg)
![Win-Msys2-CLANG32](https://github.com/StoneyDSP/CxxWin/actions/workflows/MSYS_CLANG32.yml/badge.svg)

## Win32 API with C++ and Direct2D.

A quick one-and-done Win32 API project implementing a simple COM application window for Windows platforms in C++.

![Screenshot](https://raw.githubusercontent.com/StoneyDSP/CxxWin/main/share/doc/CxxWin/screenshot_installer_example.png)

This simple application draws three semi-transparent circles within a main window, given a shared set of co-ordinates for their (relative) position and size. The main window itself is fully resizeable; the rendered circles will automatically re-calculate their own properties in relation to the resizing of the main window, while maintaining the shared position and size co-ordinates. In cases where two circles overlap, their alpha channels shall blend (the background fill is also factored into this), causing a pleasing overlapping effect.

![Screenshot](https://raw.githubusercontent.com/StoneyDSP/CxxWin/main/share/doc/CxxWin/screenshot_circles_example.png)

While none of the above makes for a particularly interesting nor useful application on it's own, the codebase is written in C++ using the Win32 API, using Direct2D and Microsoft's COM (Component Object
Model) class inheritance model, of which C++ is a first class language. The resulting application makes use of the most recent advances in C++ language standards and compiler features, is buildable on and for systems pre-dating Windows 7, and uses a logical, modular, object-based approach for portability, reusability, and maintainability.

See <a href="https://learn.microsoft.com/en-us/windows/win32/learnwin32/introduction-to-windows-programming-in-c--">the MSDN documentation for more</a>.

## Modernized, modularized, hardened...

The examples given in the MSDN documentation have here been both modernized, and hardened; the codebase aims to make use of C++20's 'modules' fucntionality for re-usability and to further highlight the Object-Oriented Programming approach that is the core of COM, the Win32 API, and of course C++ itself. The resulting windowed GUI application has been developed, built, and tested using a wide variety of modern C++ compiler toolchains, including popular Unix-like subsystems supporting GNU, Clang, and cross-compiling scenarios.

The codebase automatically calls on the correct charset (think "ANSI" or "Unicode") for the build environment, pulls in the required header sets, and links itself to the required system libraries, thanks to modern compiler feature detection macros.

Additionally, a 'high DPI aware manifest' is embedded into the application definition file, along with further compiler-level specifications to embed the application with some backwards compatibility for pre- Windows 7 environments. Modern compiler and language features automatically link the codebase with it's required system libraries and headers based on system platform, architecture, and other environmental features. Many portability and reusability features are coded in, meaning a lower dependency on buildsystems and less complex "configure/compile/build/link" runs. Some common build scripts are included to demonstrate this

## How it works

In principle, the codebase is structured such that the Win32-based code is layered into subsets of modules, primarily containing headers that define classes and helper functions that your project should inherit (using OOP and COM - see the docs linked above) in a local project-level set of files.

For this purposes of this demo project, the "local project" files are located at the root of the '/include/(projectName)/' directory, and are as follows:

- MainComponent.hpp, MainComponent.cpp

    These two files declare and define (respectively) your project's 'main window' and it's functionality, it's contents, and it's behaviour. The class is named 'MainComponent', and inherits from both the 'MainWindow' and, in turn, the 'BaseWindow' classes. The 'DPIScale' class is also utilized here; a pair of static members of 'DPIScale' are initialized and utilized as co-ordinates for our 'main window'. A 'SmartPointer' class (plus some helpers) is also used to handle the critical safe allocation and de-allocation of our handles on system-level memory resources, such as keyboard and mouse input.

    This part of the codebase will typically be compiled into a binary library file, such as a '.dll'. Other binaries can then link to it, providing access to it's contents to the linkee.

- WinMain.hpp, WinMain.cpp

    These two files declare and define (respectively) your project's 'runtime entry point' - this code is essentially the interface for the resulting '*.exe' file itself and what happens when you launch that file. As you might expect, it *includes* the 'MainComponent' files (the code for the main window) using the usual preprocessor include directive. However, all of the main window's behaviour shall remain in it's own files. The primary task of the 'WinMain' function is to handle "messages" in response to a well-defined set of user inputs, run a quick sanity check on the message, and either pass it to our 'MainComponent' for further processing (see the 'HandleMessage()' and 'WindowProc()' Window object functions), or safely resume it's current state. It is *critical* that all memory resources are free when this function ends (such as when the program is closed), which requires the use of 'SmartPointer' - type classes and functionality (such as 'std::unique_ptr' and friends provide for raw data types).

    This part of the codebase will typically, but not always, be compiled into a binary executable file, such as a '.exe'. Remember that it *includes* the 'MainComponent.hpp' file using a single-line preprocessor directive, which makes *every symbol declaration and inlined function* in 'MainComponent.hpp' - *and* in it's own "include"s of other files - accessible to 'WinMain()'. In this scenario, any compiled library binaries associated with included header(s) will need to be linked with at the end of the building process, making the actual *definitions* of those included declarations also accessible (any definition that gets used by our application *needs* to be defined, somewhere, in order to be compiled into a translation unit for the linker to eventually link with).

Any further additional functionality added to the project should likewise be declared and defined in it's own set of files, and included similarly - usually, you will probably just leave this pair of 'WinMain' files alone for the most part, and new files containing new functionality will probably find themeselves included elsewhere in your program, eventually reaching the 'WinMain' files via the already-defined inclusion of 'MainComponent'.

Inside of the '/include/CxxWin' directory is another sub-directory named '/modules', which in this instance models itself on a very small subset of the <a href="https://github.com/juce-framework/JUCE.git">JUCE Framework</a>'s take on C++20 module support. There is just enough code here to support the MSDN docs Win32 API examples, and hopefully to point forward an interesting way to continue to integrate more functionality and features from the <a href="https://github.com/microsoft/Windows-classic-samples.git">many other examples to be found in the wild</a>, using the most modern C++ functionality.

BONUS: check '/.vscode/tasks.json' for instructions on how to build on Windows with each of the <a href="https://www.msys2.org/docs/environments/">Msys64 subsystems</a>. Note that to build using the "MSYS2" sub-system from within VSCode, you must launch VSCode from the Msys64 MSYS2 environment command line. All of the others should build natively. All resulting '.exe' binaries run natively on Windows.

BONUS 2: Additional support for CMake builds, making the configure/build process as easy as two console commands. If attempting to build Win32 API apps with CMake using Msys64/MinGW toolchains, check <a href="https://github.com/StoneyDSP/msys2-toolchain.git">my MSYS2 toolchain helper</a> project.

## Thanks for reading!

### References:

- <a href="https://learn.microsoft.com/en-us/windows/win32/learnwin32/introduction-to-windows-programming-in-c--">MSDN documentation: Win32 API in C</a>

- <a href="https://github.com/microsoft/Windows-classic-samples.git">Classic Windows programming samples</a>

- <a href="https://github.com/juce-framework/JUCE.git">JUCE Framework</a>

- <a href="https://www.msys2.org/docs/environments/">Msys64 subsystems</a>
