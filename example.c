#include <stdio.h>

#include "argumentos.h"

int main(int argc, char **argv){
    int hlp = 0, ver = 0; //creating
    char txt[20];         //variables
    float flt = 0.0;      //for parsing
    struct argum list[] = {
        {"-b","--bool",  BOOL_VAR, &hlp}, //structure
        {"-i","--int",   INT_VAR,  &ver}, //for all
        {"-t","--txt",   STR_VAR,  &txt}, //arguments
        {"-f","--float", FLT_VAR,  &flt}  //for parsing
    };
 
    parser(argc, argv, list); //parse arguments
   
    strcpy(txt, strlen(txt)?txt:"void"); //if txt is null paste 'void'
    
    printf("Bool:  %i\n" //output
        "Int:   %i\n"    //result
        "Char:  %s\n"    //of
        "Float: %f\n\n"  //parsing
        "Exit code: %i",hlp,ver,txt,flt, //and
    argumentos_exit_code);               //exit code
}
