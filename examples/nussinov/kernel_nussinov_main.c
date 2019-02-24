#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N_EXEC 1

typedef char base;


void kernel_nussinov(int n, base seq[ n + 0],
      int table[ n + 0][n + 0]);


static
void *
xmalloc (size_t num)
{
  void* cur = NULL;
  int ret = 0;
  #ifdef __unix__ 
	  ret = posix_memalign (&cur, 32, num);
  #elif defined(_WIN32) || defined(WIN32) 
	  cur = _aligned_malloc(num, 32);
	  printf("cur windows: %p", cur);
  #endif
  
  if (! cur || ret)
  {
     fprintf (stderr, "[PolyBench] posix_memalign/_aligned_malloc: cannot allocate memory");
     exit (1);
  }


  return cur;
}


void* polybench_alloc_data(unsigned long long int n, int elt_size)
{
  /// FIXME: detect overflow!
  size_t val = n;
  val *= elt_size;
  void* ret = xmalloc (val);

  return ret;
}


static
void init_array (int n,
                 base seq[ n + 0],
   int table[ n + 0][n + 0])
{
  int i, j;


  for (i=0; i <n; i++) {
     seq[i] = (base)((i+1)%4);
  }

  for (i=0; i <n; i++)
     for (j=0; j <n; j++)
       table[i][j] = 0;
}




static
void print_array(int n,
   int table[ n + 0][n + 0])

{
  int i, j;
  int t = 0;

  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "table");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {    // for (j = i; j < n; j++) {
      if (t % 20 == 0) fprintf (stderr, "\n");
      fprintf (stderr, "%d ", table[i][j]);
      t++;
    }
  }
  fprintf(stderr, "\nend   dump: %s\n", "table");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}



int main(int argc, char** argv)
{

  int n = 1100;


  base (*seq)[n + 0]; seq = (base(*)[n + 0])polybench_alloc_data (n + 0, sizeof(base));;
  int (*table)[n + 0][n + 0]; table = (int(*)[n + 0][n + 0])polybench_alloc_data ((n + 0) * (n + 0), sizeof(int));;


  init_array (n, *seq, *table);

  #pragma monitor start

  int n_exec_i;
  for (n_exec_i=0; n_exec_i<N_EXEC; n_exec_i++) {
  kernel_nussinov (n, *seq, *table);
  }
  #pragma monitor stop


  if (argc > 42 && ! strcmp(argv[0], "")) print_array(n, *table);


  free((void*)seq);
  free((void*)table);
}
