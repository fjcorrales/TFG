#ifdef __cplusplus
extern "C"
{
#endif

    struct vector3_transfer
    {
        float x, y, z;
    };
    typedef struct vector3_transfer vector3_transfer;

    void *start();

    int update(vector3_transfer *, void *);
    
    int dummy(int num);

    void end();
#ifdef __cplusplus
}
#endif
