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

int calculateScore(int countM, int countS, int countOpen, int countExtend, int scoreM, int scoreS, int scoreOpen, int scoreExtend)
{
    return (countM * scoreM) + (countS * scoreS) + (countOpen * (scoreOpen+scoreExtend)) + (countExtend * scoreExtend);
}

void genasmTB(int n, int k, int count, unsigned long long tracebackMatrix[n][k+1][4][count], int m, int minError, int *ed, unsigned long long mask, char *lastChar, char *lastChar2, char *lastChar3, int *charCount, int *charCount2, int *charCount3,  char *CIGARstr, char *CIGARstr2, char *MD, char *text, int *countM, int *countS, int *countD, int *countI, int *countOpen, int *countExtend, bool *isFirst, int scoreS, int scoreOpen, int scoreExtend)
{
    int ind;
    
    int curPattern = m-1;
    int curText = 0;
    int curError = minError;
    
    while ((curPattern >= 0) && (curError >= 0))
    {
        ind = count - (curPattern / 64) - 1;

        // affine-insertion
        if (*lastChar=='I' && ((tracebackMatrix[curText][curError][2][ind] & mask) == 0))
        {
            curPattern -= 1;
            curError -= 1;
            mask = 1ULL << (curPattern % 64);
            if (*lastChar == 'I')
            {
                *charCount += 1;
                *countExtend += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'I';
                *countOpen += 1;
            }
            if (*lastChar2 == 'I')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'I';
            }
            *countI += 1;
            *ed += 1;
        }
        // affine-deletion
        else if (*lastChar=='D' && ((tracebackMatrix[curText][curError][3][ind] & mask) == 0))
        {
            curText += 1;
            curError -= 1;
            if (*lastChar == 'D')
            {
                *charCount += 1;
                *countExtend += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'D';
                *countOpen += 1;
            }
            if (*lastChar2 == 'D')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'D';
            }
            if (*lastChar3 == 'M')
            {
                sprintf(MD, "%s%d^%c", MD, *charCount3, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            else if (*lastChar3 == 'D')
            {
                sprintf(MD, "%s%c", MD, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            else
            {
                sprintf(MD, "%s^%c", MD, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            *countD += 1;
            *ed += 1;
        }
        // match
        else if ((tracebackMatrix[curText][curError][0][ind] & mask) == 0)
        {
            curText += 1;
            curPattern -= 1;
            mask = 1ULL << (curPattern % 64);
            if (*lastChar == 'M')
            {
                *charCount += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'M';
            }
            if (*lastChar2 == 'M')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'M';
            }
            if (*lastChar3 == 'M')
            {
                *charCount3 += 1;
            }
            else
            {
                *charCount3 = 1;
                *lastChar3 = 'M';
            }
            *countM += 1;
        }
        // substitution
        else if ((tracebackMatrix[curText][curError][1][ind] & mask) == 0)
        {
            curText += 1;
            curPattern -= 1;
            curError -= 1;
            mask = 1ULL << (curPattern % 64);
            if (*lastChar == 'S')
            {
                *charCount += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'S';
            }
            if (*lastChar2 == 'M')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'M';
            }
            if (*lastChar3 == 'M')
            {
                sprintf(MD, "%s%d%c", MD, *charCount3, text[curText-1]);
                *lastChar3 = 'S';
                *charCount3 = 0;
            }
            else
            {
                sprintf(MD, "%s%c", MD, text[curText-1]);
                *lastChar3 = 'S';
                *charCount3 = 0;
            }
            *countS += 1;
            *ed += 1;
        }
        // deletion
        else if ((tracebackMatrix[curText][curError][3][ind] & mask) == 0)
        {
            curText += 1;
            curError -= 1;
            if (*lastChar == 'D')
            {
                *charCount += 1;
                *countExtend += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'D';
                *countOpen += 1;
            }
            if (*lastChar2 == 'D')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'D';
            }
            if (*lastChar3 == 'M')
            {
                sprintf(MD, "%s%d^%c", MD, *charCount3, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            else if (*lastChar3 == 'D')
            {
                sprintf(MD, "%s%c", MD, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            else
            {
                sprintf(MD, "%s^%c", MD, text[curText-1]);
                *lastChar3 = 'D';
                *charCount3 = 0;
            }
            *countD += 1;
            *ed += 1;
        }
        // insertion
        else if ((tracebackMatrix[curText][curError][2][ind] & mask) == 0)
        {
            curPattern -= 1;
            curError -= 1;
            mask = 1ULL << (curPattern % 64);
            if (*lastChar == 'I')
            {
                *charCount += 1;
                *countExtend += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr, "%s%d", CIGARstr, *charCount);
                    sprintf(CIGARstr, "%s%c", CIGARstr, *lastChar);
                }
                *charCount = 1;
                *lastChar = 'I';
                *countOpen += 1;
            }
            if (*lastChar2 == 'I')
            {
                *charCount2 += 1;
            }
            else
            {
                if (!*isFirst)
                {
                    sprintf(CIGARstr2, "%s%d", CIGARstr2, *charCount2);
                    sprintf(CIGARstr2, "%s%c", CIGARstr2, *lastChar2);
                }
                *charCount2 = 1;
                *lastChar2 = 'I';
            }
            *countI += 1;
            *ed += 1;
        }

        *isFirst = false;
    }
}

void genasmDC(char *text, char *pattern, int k, int scoreM, int scoreS, int scoreOpen, int scoreExtend)
{
    int m = strlen(pattern);
    int n = strlen(text);
    
    unsigned long long max = ULLONG_MAX;
    
    int ed = 0;
    char CIGARstr[m+k];
    strcpy(CIGARstr, "");
    char CIGARstr2[m+k];
    strcpy(CIGARstr2, "");
    char MD[m+k];
    strcpy(MD, "");
    int charCount = 0;
    int charCount2 = 0;
    int charCount3 = 0;
    char lastChar = '0';
    char lastChar2 = '0';
    char lastChar3 = '0';
    
    bool isFirst = true;
    
    int countM = 0;
    int countS = 0;
    int countI = 0;
    int countD = 0;
    int countOpen = 0;
    int countExtend = 0;
  
    unsigned long long *patternBitmasks = generatePatternBitmasksACGT(pattern, m);
           
    int count = ceil(m/64.0);
    int rem = m % 64;

    unsigned long long max1;
    if (rem == 0)
    {
        //max1 = MSB_MASK;
        max1 = 1ULL << 63;
    }
    else
    {
        max1 = 1ULL << (rem-1);
    }

    // Initialize the bit arrays R
    int len1 = (k+1) * count;
    unsigned long long R[len1];
    
    for (int i=0; i < len1; i++)
    {
       R[i] = max;
    }
    
    unsigned long long tracebackMatrix[n][k+1][4][count];
    
    unsigned long long oldR[len1];

    unsigned long long substitution[count], insertion[count], match[count], deletion[count], curBitmask[count];

    // now traverse the text in opposite direction (i.e., forward), generate partial tracebacks at each checkpoint
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
           
            for (int a=0; a<count; a++)
            {
                tracebackMatrix[i][0][0][a] = R[a];
                tracebackMatrix[i][0][1][a] = max;
                tracebackMatrix[i][0][2][a] = max;
                tracebackMatrix[i][0][3][a] = max;
            }

            for (int d=1; d <= k; d++)
            {
                int index = (d-1) * count;
                
                for (int a=0; a<count; a++)
                {
                    deletion[a] = oldR[index + a];
                }

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
                
                for (int a=0; a<count; a++)
                {
                    tracebackMatrix[i][d][0][a] = match[a];
                    tracebackMatrix[i][d][1][a] = substitution[a];
                    tracebackMatrix[i][d][2][a] = insertion[a];
                    tracebackMatrix[i][d][3][a] = deletion[a];
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

    if (minError == -1)
    {
        printf("No alignment found!\t");

        free(patternBitmasks);
        return;
    }
    
    genasmTB(n, k, count, tracebackMatrix, m, minError, &ed, mask, &lastChar, &lastChar2, &lastChar3, &charCount, &charCount2, &charCount3, CIGARstr, CIGARstr2, MD, text, &countM, &countS, &countD, &countI, &countOpen, &countExtend, &isFirst, scoreS, scoreOpen, scoreExtend);
    
    free(patternBitmasks);
    
    sprintf(CIGARstr, "%s%d", CIGARstr, charCount);
    sprintf(CIGARstr, "%s%c", CIGARstr, lastChar);
    
    sprintf(CIGARstr2, "%s%d", CIGARstr2, charCount2);
    sprintf(CIGARstr2, "%s%c", CIGARstr2, lastChar2);
    
    if (lastChar3 == 'M')
    {
        sprintf(MD, "%s%d", MD, charCount3);
    }
    
    int bitmacScore = countM*scoreM-countS*scoreS-countOpen*(scoreOpen+scoreExtend)-countExtend*scoreExtend;
    
    printf("ED:%d\tAS:%d\t%s\t%s\t%s\n", ed, bitmacScore, CIGARstr, CIGARstr2, MD);
}

void genasm_aligner(char *text, char *pattern, int k, int scoreM, int scoreS, int scoreOpen, int scoreExtend)
{
    genasmDC(text, pattern, k, scoreM, scoreS, scoreOpen, scoreExtend);
}


int main(int argc, char * argv[])
{
    genasm_aligner("AATGTCC", "ATCTCGC", 3, 0, 0, 0, 0);
}
