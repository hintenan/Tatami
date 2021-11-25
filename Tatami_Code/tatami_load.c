#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "tatami.h"

int main(int argc, char **argv)
{
    void *handle;
    char *error;

    struct Node_Var* __builtins__ = NULL;
    struct Node_Var** ptoptr = &__builtins__;
    void (*bi)(struct Node_Var** ptoptr);
    //double (*cosine)(double);


   handle = dlopen("./Modules/builtins/libbuiltins.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

   dlerror();    /* Clear any existing error */

   /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
       would seem more natural, but the C99 standard leaves
       casting from "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical
       Corrigendum 1) workaround; see the Rationale for the
       POSIX specification of dlsym(). */


   bi = dlsym(handle, "builtins");
   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
   }

   struct Node_Input* input = NULL;
    struct Node_Input** inputp = &input;
    (*bi)(ptoptr);
    __builtins__ = *ptoptr;
    printf("%s\n", __builtins__->datap.class->next->next->next->variable);
    printf("%s\n", __builtins__->variable);
    (*__builtins__->datap.class->next->next->next->call.func_void)(inputp);
    dlclose(handle);
    exit(EXIT_SUCCESS);
}