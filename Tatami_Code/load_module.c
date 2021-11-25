#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include "tatami.h"

 
int load_module(struct Node_Var** pool_ptoptr, struct Node_Input** ptoptr) {
    void *handle;
    char *error;

    struct Node_Input* module_name = *ptoptr;
    //struct Node_Var** ptoptr = &__builtins__;
    //add_Node_Var(module_name->text, pool_ptoptr);
    void (*bi)(struct Node_Var**);
    //double (*cosine)(double);

    /*
    handle = dlopen("./Modules/builtins/libbuiltins.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();    // Clear any existing error 
    
    //printf("importing ...\n");
    void *handle;
    char *error;
    */

    //struct Node_Input* tmp_Node = *ptoptr;
    //struct Node_Var* pool_Node = *pool_ptoptr;
    char link_path[100] = "./Modules/";

    while (module_name != NULL) {
        if (module_name->dtype == 201) {
            strcat(link_path, module_name->text);
            strcat(link_path, "/lib");
            strcat(link_path, module_name->text);
            strcat(link_path, ".so");
            //printf("%s\n", link_path);
            handle = dlopen(link_path, RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }

            dlerror();    // Clear any existing error
            /*
            void (*mod)(void);
            *(void **) (&mod) = dlsym(handle, tmp_Node->text);
            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                //exit(EXIT_FAILURE);
            }

            //printf("%d\n", (*add)(2, 3));
            //dlclose(handle);
            add_Node_Var(tmp_Node->text, pool_ptoptr);
            (*pool_ptoptr)->dtype = 301;
            (*pool_ptoptr)->datap.func = mod;
            */
            bi = dlsym(handle, module_name->text);
            if ((error = dlerror()) != NULL)  {
                    fprintf(stderr, "%s\n", error);
                    exit(EXIT_FAILURE);
            }
            (*bi)(pool_ptoptr);
    
            

        }

        module_name = module_name->next;
    
    }
    

    
    //
    //int (*arithmetic)(char, int, int);

   /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
       would seem more natural, but the C99 standard leaves
       casting from "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical
       Corrigendum 1) workaround; see the Rationale for the
       POSIX specification of dlsym(). */

   //*(void **) (&foo) = dlsym(handle, "foo");
   //*(void **) (&arithmetic) = dlsym(handle, "arithmetic");

   //if ((error = dlerror()) != NULL)  {
   //     fprintf(stderr, "%s\n", error);
   //     exit(EXIT_FAILURE);
   // }

    //(*foo)();
    
    //exit(EXIT_SUCCESS);
    return 1;
}
