**Explicit Instantiation**

- Allows to hide the definition, i.e., definition can be moved out of header
- If we include definition in header, every compilation unit that includes that
header will implicitly instantiate the template arguments whenever they are used.
This results in increasing compile and link time.

**Compiling and running the code**
```
cmake -S . -B build
cd build
./app.exe
```
