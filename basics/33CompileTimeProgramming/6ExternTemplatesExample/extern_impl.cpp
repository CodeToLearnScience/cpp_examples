#include "extern_template.h"
#include <ostream>

// non-extern instantiation of the template
// Here we have the implementation file, where the instantiation is done
// explicitly. So this will be where the template is instantiated, and this will
// contain the only copy of the source code for the template body
template std::ostream &print(std::ostream &os, const std::string &str);
