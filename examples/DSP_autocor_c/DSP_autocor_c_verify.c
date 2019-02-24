#include <stdio.h>
#include <string.h>

void DSP_autocor_c(short * r, const short * x, int nx, int nr);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);   

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NR       (16)   
#define NX       (40)   
#define NXPNR    (56)   


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
short  r_c[NR];

short  r_c_expected[NR] = { -22040, -19216, 16373, -27069, -25058, 2875, -9504, 22922, 20111, 19741, 22590, -24859, 6560, 28846, 8505, 10088 };

const short  x[NXPNR] =
{
    -0x3C62, -0x47B4,  0x4B74,  0x41E5, -0x611A, -0x1578, -0x73C0, -0x4395,
     0x1749, -0x43BD,  0x2D2F,  0x7812,  0x4CEB,  0x017B,  0x4BB0,  0x7DEF,
     0x2A9C, -0x1883, -0x597E, -0x7CB4,  0x7084,  0x13FC,  0x3C1F,  0x2410,
     0x22A4, -0x1061, -0x0DC1,  0x4A1E,  0x7546, -0x684B, -0x2B85,  0x3E67,
     0x14E1, -0x0570, -0x65D1, -0x2B4A,  0x5AF4, -0x5CD6, -0x4B45,  0x5424,
     0x34C2,  0x78DE, -0x17D3,  0x22BB,  0x4BD5,  0x4774,  0x7F5F,  0x2CAE,
    -0x767F,  0x7762, -0x512B,  0x6892,  0x57F6,  0x23A1, -0x7246,  0x698B
};


int main(int argc, char** argv)
{

	#pragma monitor start
	DSP_autocor_c(r_c, x, NX, NR);
	#pragma monitor stop

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%hd", r_c[NR-1]);

	int i;
	for(i=0; i < NR; i++) {
		if(r_c[i] != r_c_expected[i]) {
			return 1;
		}
	}
	return 10;

}

