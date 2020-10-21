#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>

unsigned long long *generatePatternBitmasks(char* pattern, int m)
{
    int count = ceil(m/64.0);
    
    int len = CHAR_MAX * count;
    
    unsigned long long *patternBitmasks = (unsigned long long *) malloc(len * sizeof(unsigned long long));
    
    unsigned long long max = ULLONG_MAX;

    // Initialize the pattern bitmasks
    for (int i=0; i < len; i++)
    {
       patternBitmasks[i] = max;
    }

    // Update the pattern bitmasks
    int index;
    for (int i=0; i < m; i++)
    {
       index = count - ((m-i-1) / 64) - 1;
       patternBitmasks[pattern[i]*count + index] &= ~(1ULL << ((m-i-1) % 64));
    }
    
    return patternBitmasks;
}

unsigned long long *generatePatternBitmasksACGT(char* pattern, int m)
{
    int count = ceil(m/64.0);
        
    int len = 4*count; // A,C,G,T
        
    unsigned long long *patternBitmasks = (unsigned long long *) malloc(len * sizeof(unsigned long long));
        
    unsigned long long max = ULLONG_MAX;

    // Initialize the pattern bitmasks
    for (int i=0; i < len; i++)
    {
        patternBitmasks[i] = max;
    }

    // Update the pattern bitmasks
    int index;
    for (int i=0; i < m; i++)
    {
        index = count - ((m-i-1) / 64) - 1;
        if ((pattern[i] == 'A') || (pattern[i] == 'a'))
        {
            patternBitmasks[0*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'C') || (pattern[i] == 'c'))
        {
            patternBitmasks[1*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'G') || (pattern[i] == 'g'))
        {
            patternBitmasks[2*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'T') || (pattern[i] == 't'))
        {
            patternBitmasks[3*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
    }
    
    return patternBitmasks;
}

unsigned long long *generateReversePatternBitmasksACGT(char* pattern, int m)
{
    int count = ceil(m/64.0);
        
    int len = 4*count; // A,C,G,T
        
    unsigned long long *reversePatternBitmasks = (unsigned long long *) malloc(len * sizeof(unsigned long long));
        
    unsigned long long max = ULLONG_MAX;

    // Initialize the pattern bitmasks
    for (int i=0; i < len; i++)
    {
        reversePatternBitmasks[i] = max;
    }

    // Update the pattern bitmasks
    int index;
    for (int i=0; i < m; i++)
    {
        index = count - (i/64) - 1;
        if ((pattern[i] == 'A') || (pattern[i] == 'a'))
        {
            reversePatternBitmasks[0*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'C') || (pattern[i] == 'c'))
        {
            reversePatternBitmasks[1*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'G') || (pattern[i] == 'g'))
        {
            reversePatternBitmasks[2*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'T') || (pattern[i] == 't'))
        {
            reversePatternBitmasks[3*count + index] &= ~(1ULL << (i%64));
        }
    }
    
    return reversePatternBitmasks;
}

unsigned long long *generatePatternBitmasksACGTN(char* pattern, int m)
{
    int count = ceil(m/64.0);
        
    int len = 4*count; // A,C,G,T,N
        
    unsigned long long *patternBitmasks = (unsigned long long *) malloc(len * sizeof(unsigned long long));
        
    unsigned long long max = ULLONG_MAX;

    // Initialize the pattern bitmasks
    for (int i=0; i < len; i++)
    {
        patternBitmasks[i] = max;
    }

    // Update the pattern bitmasks
    int index;
    for (int i=0; i < m; i++)
    {
        index = count - ((m-i-1) / 64) - 1;
        if ((pattern[i] == 'A') || (pattern[i] == 'a'))
        {
            patternBitmasks[0*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'C') || (pattern[i] == 'c'))
        {
            patternBitmasks[1*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'G') || (pattern[i] == 'g'))
        {
            patternBitmasks[2*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'T') || (pattern[i] == 't'))
        {
            patternBitmasks[3*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
        else if ((pattern[i] == 'N') || (pattern[i] == 'n'))
        {
            patternBitmasks[0*count + index] &= ~(1ULL << ((m-i-1) % 64));
            patternBitmasks[1*count + index] &= ~(1ULL << ((m-i-1) % 64));
            patternBitmasks[2*count + index] &= ~(1ULL << ((m-i-1) % 64));
            patternBitmasks[3*count + index] &= ~(1ULL << ((m-i-1) % 64));
        }
    }
    
//    printf("%s", printBinary(patternBitmasks[0*count], 64));
//    printf("%s\n", printBinary(patternBitmasks[0*count+1], 64));
//    printf("%s", printBinary(patternBitmasks[1*count], 64));
//    printf("%s\n", printBinary(patternBitmasks[1*count+1], 64));
//    printf("%s", printBinary(patternBitmasks[2*count], 64));
//    printf("%s\n", printBinary(patternBitmasks[2*count+1], 64));
//    printf("%s", printBinary(patternBitmasks[3*count], 64));
//    printf("%s\n", printBinary(patternBitmasks[3*count+1], 64));
    
    return patternBitmasks;
}

unsigned long long *generateReversePatternBitmasksACGTN(char* pattern, int m)
{
    int count = ceil(m/64.0);
        
    int len = 4*count; // A,C,G,T,N
        
    unsigned long long *reversePatternBitmasks = (unsigned long long *) malloc(len * sizeof(unsigned long long));
        
    unsigned long long max = ULLONG_MAX;

    // Initialize the pattern bitmasks
    for (int i=0; i < len; i++)
    {
        reversePatternBitmasks[i] = max;
    }

    // Update the pattern bitmasks
    int index;
    for (int i=0; i < m; i++)
    {
        index = count - (i/64) - 1;
        if ((pattern[i] == 'A') || (pattern[i] == 'a'))
        {
            reversePatternBitmasks[0*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'C') || (pattern[i] == 'c'))
        {
            reversePatternBitmasks[1*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'G') || (pattern[i] == 'g'))
        {
            reversePatternBitmasks[2*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'T') || (pattern[i] == 't'))
        {
            reversePatternBitmasks[3*count + index] &= ~(1ULL << (i%64));
        }
        else if ((pattern[i] == 'N') || (pattern[i] == 'n'))
        {
            reversePatternBitmasks[0*count + index] &= ~(1ULL << (i%64));
            reversePatternBitmasks[1*count + index] &= ~(1ULL << (i%64));
            reversePatternBitmasks[2*count + index] &= ~(1ULL << (i%64));
            reversePatternBitmasks[3*count + index] &= ~(1ULL << (i%64));
        }
    }
    
    return reversePatternBitmasks;
}

int genasmDC(char *text, char *pattern, int k)
{
    int m = strlen(pattern);
    int n = strlen(text);
    
    unsigned long long max = ULLONG_MAX;

    int count = ceil(m/64.0);
    
    unsigned long long *patternBitmasks = generatePatternBitmasksACGTN(pattern, m);
    
    // Initialize the bit arrays R
    int len1 = (k+1) * count;
    unsigned long long R[len1];
    
    for (int i=0; i < len1; i++)
    {
       R[i] = max;  
    }

    for (int x=1; x < (k+1); x++)
    {
        if ((x % 64) == 0)
        {
            int ind = count - (x/64);
            for (int y = (count-1); y >= ind; y--)
            {
                R[x*count+y] = 0ULL;
            }
        }
        else
        {
            int ind = count - 1 - (x/64);
            for (int y = (count-1); y > ind; y--)
            {
                R[x*count+y] = 0ULL;
            }
            R[x*count + ind] = max << (x%64);
        }
    }
        
    unsigned long long oldR[len1];

    unsigned long long substitution[count], insertion[count], match[count];
    unsigned long long deletion[count], curBitmask[count];

    int rem = m % 64;

    unsigned long long max1;
    if (rem == 0)
    {
        max1 = 1ULL << 63;
    }
    else
    {
        max1 = 1ULL << (rem-1);
    }

    for (int i=n-1; i >= 0; i--)
    {
        char c = text[i];
        
        if ((c == 'A') || (c == 'a') || (c == 'C') || (c == 'c') || (c == 'G') || (c == 'g') || (c == 'T') || (c == 't'))
        {
            // copy the content of R to oldR
            for (int itR=0; itR<len1; itR++)
            {
                oldR[itR] = R[itR];
            }

            if ((c == 'A') || (c == 'a'))
            {
                for (int a=0; a<count; a++)
                {
                    curBitmask[a] = patternBitmasks[0*count + a];
                }
            }
            else if ((c == 'C') || (c == 'c'))
            {
                for (int a=0; a<count; a++)
                {
                    curBitmask[a] = patternBitmasks[1*count + a];
                }
            }
            else if ((c == 'G') || (c == 'g'))
            {
                for (int a=0; a<count; a++)
                {
                    curBitmask[a] = patternBitmasks[2*count + a];
                }
            }
            else if ((c == 'T') || (c == 't'))
            {
                for (int a=0; a<count; a++)
                {
                    curBitmask[a] = patternBitmasks[3*count + a];
                }
            }

            // update R[0] by first shifting oldR[0] and then ORing with pattern bitmask
            R[0] = oldR[0] << 1;
            for (int a=1; a<count; a++)
            {
                R[a-1] |= (oldR[a] >> 63);
                R[a] = oldR[a] << 1;
            }
            for (int a=0; a<count; a++)
            {
                R[a] |= curBitmask[a];
            }
           
            for (int d=1; d <= k; d++)
            {
                int index = (d-1) * count;
                
                for (int a=0; a<count; a++)
                {
                    deletion[a] = oldR[index + a];
                }
                
                //deletion = &oldR[index];

                substitution[0] = deletion[0] << 1;
                for (int a=1; a<count; a++)
                {
                    substitution[a-1] |= (deletion[a] >> 63);
                    substitution[a] = deletion[a] << 1;
                }

                insertion[0] = R[index] << 1;
                for (int a=1; a<count; a++)
                {
                    insertion[a-1] |= (R[index+a] >> 63);
                    insertion[a] = R[index+a] << 1;
                }

                index += count;
                
                match[0] = oldR[index] << 1;
                for (int a=1; a<count; a++)
                {
                    match[a-1] |= (oldR[index+a] >> 63);
                    match[a] = oldR[index+a] << 1;
                }
                
                for (int a=0; a<count; a++)
                {
                    match[a] |= curBitmask[a];
                }
                
                for (int a=0; a<count; a++)
                {
                    R[index+a] = deletion[a] & substitution[a] & insertion[a] & match[a];
                }
            }
        }
    }
    
    int minError = -1;
    unsigned long long mask = max1;
    
    for (int t=0; t <= k; t++)
    {
        if ((R[t*count] & mask) == 0)
        {
            minError = t;
            break;
        }
    }

    free(patternBitmasks);

    //fprintf(stdout, "%d\n", minError);

    return minError;
}

int genasm(char *text, char *pattern, int k)
{
    int minError = genasmDC(text, pattern, k);
    if (minError == -1)
    {
        printf("0\n");
        return 0;
    }
    else
    {
        printf("%d\n",minError);
        return 1;
    }
}

int main(int argc, char * argv[])
{
    genasm("AAAGAAAAGAATTTTCAACCCAGAATTTCATATCCAGCCAAACTACGCTTCATAAGTGAAGGAGAAATAAAATCCTTTACAGACAAGCAAATGCTGAGAG", "AAAGAAAAGAATTTTCAACCCAGAATTTCATATCCAGCCAAACAAAGCTTCATAAGTGAAGGAGAAATAAATCCTTTACAGAGAAGCAAATGCTGAGAGA", 6);
    return 0;
}
