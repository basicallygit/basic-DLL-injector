# C++ DLL injector

## Compilation
```bash
$ g++ injector/main.cpp -o injector.exe
$ g++ -c exampleDLL/dllmain.cpp -o dllmain.o
$ g++ -shared dllmain.o -o main.dll
$ injector
```
