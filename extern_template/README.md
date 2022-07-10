**Introduction**

*Extern template* 
This enables us to use explicit instantiation as well as implicit instantiation. Explicit instantiation using extern templates can save us huge compiling and linking time when we build huge number of files that use the same function or class templates. That is multiple use of explicitly instantiated function will not be instantiated each time we call it. However, implicitly instantiated function will be instantiated each time we call it thereby increasing compiling and link time.

**Compiling and running the code**
cmake -S . -B build
cd build
./app.exe