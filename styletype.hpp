#ifndef STYLETYPE_HPP
#define STYLETYPE_HPP
#include <string>

const std::string std_tab               = "    ";

const std::string if_default_part1      = "if(    )\n";
const std::string if_default_part2      = "{\n\n";
const std::string if_knr                = "if(    ){\n\n";
const std::string if_one_line           = "if(    ) ;\n\n";
const std::string end_if	            = "}\n\n";
const std::string else_if_default_part1 = "else if(    )\n";
const std::string else_if_default_part2 = "{\n\n";
const std::string else_if_knr           = "else if(    ){\n\n";
const std::string else_if_one_line      = "else if(    ) ;\n\n";
const std::string else_default          = "else\n{\n    ";
const std::string else_knr              = "else{\n   ";
const std::string else_one_line         = "else ;\n\n";

const std::string void_main_default     = "int main(void)\n{\n    return 0;\n}\n\n";
const std::string void_main_knr         = "int main(void){\n    return 0;\n}\n\n";
const std::string type_void             = "void ";
const std::string type_int              = "int ";
const std::string type_char             = "char ";
const std::string type_float            = "float ";
const std::string type_double           = "char ";
const std::string type_mod_long         = "long ";
const std::string type_mod_short        = "short ";

const std::string func_ident		    = "function";
const std::string begin_func_default    = "\n{\n\n";
const std::string begin_func_knr        = "{\n\n";
const std::string end_func              = "}\n\n";
const std::string arg_main_default      = "int main(int argc, char*argv[])\n{\n    return 0;\n}\n\n";
const std::string arg_main_knr          = "int main(int argc, char*argv[]){\n     return 0\n}\n\n";
const std::string def_include           = "#include <stdio.h>\n\n";         

#endif 
