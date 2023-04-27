#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
    void *handle;
    int (*dummy)(int num);
    int resultado;

    handle = dlopen("../ros2_test/src/cpp_pubsub/build/cpp_pubsub/liblistenerlib.so", RTLD_LAZY);

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./dlopen num1\n");
        return 1;
    }

    if (!handle)
    {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    *(void **)(&dummy) = dlsym(handle, "dummy");

    if (!dummy)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    int result = dummy(atoi(argv[1]));
    printf(" El número retornado por dummy es: %d\n", result);
    dlclose(handle);

    return 0;
}