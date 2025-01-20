#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "quickselect.h"
#include <time.h>


static double
clockdiff(struct timespec* start, struct timespec * finish)
{
    double elapsed = (finish->tv_sec - start->tv_sec);
    elapsed += (finish->tv_nsec - start->tv_nsec) / 1000000000.0;
    return elapsed;
}


#ifdef QUICKSELECT_F32
typedef float etype;
#else
typedef double etype;
#endif

int cmp_etype(const void * _a, const void * _b)
{
    etype * a = (etype *) _a;
    etype * b = (etype *) _b;
    if(*a == *b)
    { return 0; }
    if(*a < *b)
    { return -1; }
    return 1;
}

int main(int argc, char ** argv)
{
#ifdef QUICKSELECT_F32
    printf("Floats are 32-bit\n");
#else
    printf("Floats are 64-bit\n");
#endif

    size_t N = 10;

    if(argc > 1)
    {
        N = atol(argv[1]);
    }

    assert(N > 0);

    printf("Number of items in array: N=%zu\n", N);
    etype * X = calloc(N, sizeof(etype));
    assert(X != NULL);
    struct timespec t0, t1;

    printf("Testing on constant array\n");

    etype s = 0;
#ifdef QUICKSELECT_F32
     s+= qselect_f32(X, N, 0);
     s+= qselect_f32(X, N, (N-1)/2);
     s+= qselect_f32(X, N, N-1);
#else
     s+= qselect_f64(X, N, 0);
     s+= qselect_f64(X, N, (N-1)/2);
     s+= qselect_f64(X, N, N-1);
#endif
     if(s != 0)
     {
         assert(s == 0);
         printf("An unexpected result on line %d in %s\n", __LINE__, __FILE__);
     }


    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t kk = 0 ; kk<N; kk++)
    {
        X[kk] = (etype) rand() / (etype) RAND_MAX;
        if(kk < 10)
        {
            printf("Input %zu = %f\n", kk, X[kk]);
        }
    }
    clock_gettime(CLOCK_REALTIME, &t1);

    printf("data generation took %f s\n",
           clockdiff(&t0, &t1));

    etype * S = calloc(N, sizeof(etype));
    assert(S != NULL);
    memcpy(S, X, N*sizeof(etype));

    clock_gettime(CLOCK_REALTIME, &t0);
    qsort(S, N, sizeof(etype), cmp_etype);
    clock_gettime(CLOCK_REALTIME, &t1);
    etype t_qsort = clockdiff(&t0, &t1);
    printf("qsort took %f s\n",
           t_qsort);

    clock_gettime(CLOCK_REALTIME, &t0);
    size_t Ntest = N;

    N > 1000 ? Ntest = 1000 : 0;
    Ntest = 10/t_qsort;
    Ntest < 1 ? Ntest = 1 : 0;
    Ntest > N ? Ntest = N : 0;
    printf("selecting %zu numbers\n", Ntest);
    size_t pos = 0;
    Ntest == 1 ? pos = N/2 : 0;
    for(size_t kk = 0; kk<Ntest; kk++)
    {
#ifdef QUICKSELECT_F32
        etype s = qselect_f32(X, N, pos);
#else
        etype s = qselect_f64(X, N, pos);
#endif

        if(kk < 10)
        {
            printf("#%zu = %f\n",pos, s);
        }
        if( S[pos] != s)
        {
            printf("Error!\n");
            exit(EXIT_FAILURE);
        }
        pos += N/Ntest;
        fflush(stdout);
    }
    clock_gettime(CLOCK_REALTIME, &t1);
    printf("All tests passed.\n");
    printf("quickselect took in average %f s\n",
           clockdiff(&t0, &t1)/(etype) Ntest);
    free(S);
    free(X);
    return EXIT_SUCCESS;
}
