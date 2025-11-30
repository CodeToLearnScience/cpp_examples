//C++ by default will copy objects unless we tell it to use reference. This is 
//called value semantics. Initialization creates entirely new object by copy. 

//For reference semantics in C++, we can have arguments pass by reference, 
//Initialization creates an alias to existing object, heap-allocated objects 
//can exist beyond the end of the scope

//Lots of languages use reference semantics like Fortran. So when an object is 
//initialized from other objects or passed to function as arguments, by default 
//reference is used. It's called reference semantics. So original object cannot 
//be destroyed until all the other objects which are using the original objects 
//are destroyed. So to keep track of all these objects and decide whether its 
//safe to destroy them, the langues use garbage collector 
