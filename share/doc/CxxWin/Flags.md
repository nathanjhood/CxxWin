A note on compiler flags.

## default libraries

For 'normal' (i.e., 'uwin') targets, the following libs are included by default:

- user32

Cygwin and MinGW toolchain users should be aware that the following libraries automatically included in all programs (even console-mode programs).

- kernel32

## '-mwindows'

For 'normal' (i.e., 'uwin') targets, the '-mwindows' option includes the libraries:

- gdi32
- comdlg32

In MinGW-land, the '-mwindows' option includes the following set of libraries:

- user32
- gdi32
- cmdlg32
- kernel32
- advapi32
- shell32

*But how to link with 'WINAPI WinMain()' instead of 'int main()'?*

When asked to link objects and libraries into an executable, LD will usually search for the common 'int main()' function signature (or a derivative thereof) among it's sources, and use that as the entry point for the application. The Win32 API has abstracted away the entry point function for applications that adhere to it, meaning that 'int main()' itself is actually specified already in one of the Microsoft/Windows SDK files that the project is linking with, where the API uses this to prepare a *new* entry point function for our code to call, which resembles the following:

- ``` int WINAPI WinMain  (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  pCmdLine, int nCmdShow) ```

This entry point provides us with parameters that use the Win32 API, in particular Microsoft's 'Component Object Model', or 'COM', which is used instead of calling 'int main()' oneself. One of the main purposes of this entry point is the usage of a 'garbage collector' routine which is built in to the 'WinMain()' function by the Microsoft team.

In very old GNUCC builds, before the '-mwindows' flag was introduced, it was possible to tell LD to link with 'WinMain()' and 'WinMainCRTStartup' by using the linker flag '-Wl,--subsystem,windows'. The '-mwindows' compiler flag is intended to select the required-by-default libraries *and* set the '\_\_subsystem\_\_' flag accordingly (to a value of '2'). Presumably, there might also be other 'under-the-hood' optional behaviours that this flag controls, when and where necessary. In the event of not having support for this flag while trying to build a Win32 API project, or for general reasons, it is helpful to be aware of how this flag corresponds to the other command line parameters; If you've been passing '-mwindows' while trying to scrub 'gdi32' from the linked libraries, for example, then this lower level of abstraction explains why you can't.

## '-municode'

Windows native applications typically use Unicode specifications (requiring the UTF-16 'wide' charset), where many other applications might use something like ANSI (the UTF-8 charset). Applications, functions, and other processes might offer hooks for using a choice of charsets;for example, command-line applications that usually specify an 'int main()' entry point function, might also offer an 'int wmain()' alternative, to provide interoperability between different runtime environments that have differing charset requirements.

The 'traditional' means of having the compiler call 'int wmain()' instead of regular 'int main()' when our executable program is linked, is by defining the pre-processor macro(s):

- 'UNICODE'
- '_UNICODE'

The presence of this definition acts as a switch - often, by user design - to using the Unicode specifications wherever applicable within the project codebase being linked.

On more recent GNU compiler versions, the '-municode' flag has been derived as a means of controlling the same specification requests as the 'UNICODE/_UNICODE' macros have done. However, 'outdated' GNU compilers are still running in the wild in several major scenarios; for example, as of writing, the current ports of the GNUCC to the Cygwin/Msys environments are not yet supporting the '-municode' compiler flag, and thus the 'UNICODE/_UNICODE' macros must still be defined in such a case.
