#ifdef __unix__ 
	#include <omp.h>
#endif	

#include <math.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

typedef char base;


void kernel_nussinov(int n, base seq[ n + 0],
      int table[ n + 0][n + 0])
{
  int i, j, k;

/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
  int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
/* Start of CLooG code */
if (n >= 2) {
  for (t2=max(-1,ceild(-n-29,32));t2<=floord(n-1,32);t2++) {
    lbp=max(0,t2);
    ubp=min(floord(n-1,32),floord(32*t2+n+29,32));
#ifdef __unix__ 
	#pragma omp parallel for private(lbv,ubv,t5,t6,t7,t8,t9,t10)
#endif	
    for (t4=lbp;t4<=ubp;t4++) {
      if ((t2 <= floord(32*t4-n+2,32)) && (t4 >= ceild(n-31,32))) {
        table[(n-2)][(n-1)] = ((table[(n-2)][(n-1)] >= table[(n-2)][(n-1)-1]) ? table[(n-2)][(n-1)] : table[(n-2)][(n-1)-1]);;
        table[(n-2)][(n-1)] = ((table[(n-2)][(n-1)] >= table[(n-2)+1][(n-1)]) ? table[(n-2)][(n-1)] : table[(n-2)+1][(n-1)]);;
        table[(n-2)][(n-1)] = ((table[(n-2)][(n-1)] >= table[(n-2)+1][(n-1)-1]) ? table[(n-2)][(n-1)] : table[(n-2)+1][(n-1)-1]);;
      }
      if ((t2 == -1) && (t4 <= floord(n-32,32))) {
        table[(32*t4+30)][(32*t4+31)] = ((table[(32*t4+30)][(32*t4+31)] >= table[(32*t4+30)][(32*t4+31)-1]) ? table[(32*t4+30)][(32*t4+31)] : table[(32*t4+30)][(32*t4+31)-1]);;
        table[(32*t4+30)][(32*t4+31)] = ((table[(32*t4+30)][(32*t4+31)] >= table[(32*t4+30)+1][(32*t4+31)]) ? table[(32*t4+30)][(32*t4+31)] : table[(32*t4+30)+1][(32*t4+31)]);;
        table[(32*t4+30)][(32*t4+31)] = ((table[(32*t4+30)][(32*t4+31)] >= table[(32*t4+30)+1][(32*t4+31)-1]) ? table[(32*t4+30)][(32*t4+31)] : table[(32*t4+30)+1][(32*t4+31)-1]);;
      }
      for (t5=max(max(-n+3,32*t2-32*t4),-32*t4-29);t5<=min(min(0,-32*t4+1),32*t2-32*t4+31);t5++) {
        table[-t5][(-t5+1)] = ((table[-t5][(-t5+1)] >= table[-t5][(-t5+1)-1]) ? table[-t5][(-t5+1)] : table[-t5][(-t5+1)-1]);;
        table[-t5][(-t5+1)] = ((table[-t5][(-t5+1)] >= table[-t5+1][(-t5+1)]) ? table[-t5][(-t5+1)] : table[-t5+1][(-t5+1)]);;
        table[-t5][(-t5+1)] = ((table[-t5][(-t5+1)] >= table[-t5+1][(-t5+1)-1]) ? table[-t5][(-t5+1)] : table[-t5+1][(-t5+1)-1]);;
        for (t7=-t5+2;t7<=min(n-1,32*t4+31);t7++) {
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5][t7-1]) ? table[-t5][t7] : table[-t5][t7-1]);;
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5+1][t7]) ? table[-t5][t7] : table[-t5+1][t7]);;
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5+1][t7-1]+(((seq[-t5])+(seq[t7])) == 3 ? 1 : 0)) ? table[-t5][t7] : table[-t5+1][t7-1]+(((seq[-t5])+(seq[t7])) == 3 ? 1 : 0));;
          for (t9=-t5+1;t9<=t7-1;t9++) {
            table[-t5][t7] = ((table[-t5][t7] >= table[-t5][t9] + table[t9+1][t7]) ? table[-t5][t7] : table[-t5][t9] + table[t9+1][t7]);;
          }
        }
      }
      for (t5=max(32*t2-32*t4,-32*t4+2);t5<=min(0,32*t2-32*t4+31);t5++) {
        for (t7=32*t4;t7<=min(n-1,32*t4+31);t7++) {
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5][t7-1]) ? table[-t5][t7] : table[-t5][t7-1]);;
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5+1][t7]) ? table[-t5][t7] : table[-t5+1][t7]);;
          table[-t5][t7] = ((table[-t5][t7] >= table[-t5+1][t7-1]+(((seq[-t5])+(seq[t7])) == 3 ? 1 : 0)) ? table[-t5][t7] : table[-t5+1][t7-1]+(((seq[-t5])+(seq[t7])) == 3 ? 1 : 0));;
          for (t9=-t5+1;t9<=t7-1;t9++) {
            table[-t5][t7] = ((table[-t5][t7] >= table[-t5][t9] + table[t9+1][t7]) ? table[-t5][t7] : table[-t5][t9] + table[t9+1][t7]);;
          }
        }
      }
    }
  }
}
/* End of CLooG code */

}
