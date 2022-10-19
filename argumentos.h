#include <string.h>
#include <stdlib.h>

#define log //if require no logs, delete this define

#define BOOL_VAR 0 //1 if exist in args, 0 if no
#define INT_VAR  1 //int from the next arg after flag
#define STR_VAR  2 //string from the next arg after flag
#define FLT_VAR  3 //float from the next arg after flag 

#define parser(argc, argv, list)\
    struct argumentos args = {argc, argv, &list};/*create struct with list of flag and all cmd args*/\
    int argumentos_exit_code = parse(&args, sizeof(list)/sizeof(*list));
//if need check exit code of the parser, call argumentos_exit_code as int

struct argum{
    char *short_flag; //short flag (-f, -r, -o, etc)
    char *full_flag;  //full flag (--help, --debug, etc)
    short type;       //type of the variable (BOOL_VAR, INT_VAR, FLT_VAR or STR_VAR)
    void *var_ptr;    //ptr to the memory for seting from argument
};

struct argumentos{
    int args_count; //count of the cmd args
    char **args;    //array of the args
    struct argum *arguments; //ptr to the array of the params to check
};

short parse(struct argumentos *data, int argc){
    if(!argc){ //check is flags count != 0
        #ifdef log
        printf("Fatal argumentos error! "
        "Add minimum one flag!\n\n");
        #endif
        return -1;
 }
 int count = data->args_count; //count of the cmd arguments
 char **params = data->args;   //double ptr to array with cmd args
 struct argum *flags = data->arguments; //ptr to struct, where all flags are stored
 
 for(int _=0;_<argc;_++){ //check is all types of variables is valid
     short type = flags[_].type;
     if(type>3 || type<0){
     #ifdef log
     printf("Fatal argumentos error! "
            "Unsupported variable type!"
            "\n\n");
     #endif
     return -2;
    }
 }
 
 for(int loop_a=1;loop_a<count;loop_a++){
  for(int loop_f=0;loop_f<argc;loop_f++){
   
   if(!strcmp(*(params+loop_a),  //cmp
    flags[loop_f].short_flag) || //flags
      !strcmp(*(params+loop_a),  //and
      flags[loop_f].full_flag)){ //args
     
     switch(flags[loop_f].type){
      case BOOL_VAR: //parse bool
        *(int*)flags[loop_f].var_ptr = 1;
      break;
      
      case INT_VAR: //parse intager using atoi
        loop_a++;
        *(int*)flags[loop_f].var_ptr = atoi(*(params+loop_a));
      break;
      
      case FLT_VAR: //parse float using atof
        loop_a++;
        *(float*)flags[loop_f].var_ptr = atof(*(params+loop_a));
      break;
      
      case STR_VAR: //parse char*(string) using strcpy
          loop_a++;
          strcpy((char*)(flags[loop_f].var_ptr), params[loop_a]);
      break;
     }
    }
   }
 }
    return 0;
}
