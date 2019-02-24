void DSP_autocor_c(short * r, const short * x, int nx, int nr)
{
    int i,k,sum;
    for (i = 0; i < nr; i++)
    {
        sum = 0;
        for (k = nr; k < nx+nr; k++)
            sum += x[k] * x[k-i];
        r[i] = (sum >> 15);
    }
}

