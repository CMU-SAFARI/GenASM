# GenASM: Approximate String Matching (ASM) Acceleration Framework for Genome Sequence Analysis
GenASM is an approximate string matching (ASM) acceleration framework for genome sequence analysis. GenASM is a fast, efficient, and flexible framework for both short and long reads, which can be used to accelerate multiple steps of the genome sequence analysis pipeline. We base GenASM upon the Bitap algorithm. Bitap uses only fast and simple bitwise operations to perform approximate string matching. To our knowledge, GenASM is the first work that enhances and accelerates Bitap.

To use Bitap for GenASM, we make two key algorithmic modifications that allow us to overcome key limitations that prevent the original Bitap algorithm from being efficient for genome sequence analysis. First, to improve Bitap’s applicability to different sequencing technologies and its performance, we (1) modify the algorithm to support long reads (in addition to already supported short reads), and (2) eliminate loop-carried data dependencies so that we can parallelize a single string matching operation. Second, we develop a novel Bitap-compatible algorithm for traceback. The original Bitap algorithm is not capable of performing traceback.

## GenASM-DC Algorithm

Bitap is an ASM algorithm, which tackles the problem of computing the minimum edit distance between a reference text (e.g., reference genome) and a query pattern (e.g., read) with a maximum of k many errors. When k is 0, the algorithm finds the exact matches. 

We modify the baseline Bitap algorithm to (1) enable efficient alignment of long reads, (2) remove the data dependency between the iterations, and (3) provide parallelism for the large number of iterations.

**Long Read Support.** The GenASM-DC algorithm overcomes the word-length limit of Bitap by storing the bitvectors in multiple words when the query is longer than the word size. Although this modification leads to additional computation when performing shifts, it helps GenASM to support both short and long reads. When shifting word i of a multi-word bitvector, the bit shifted out (MSB) of word i – 1 needs to be stored separately before performing the shift on word i – 1. Then, that saved bit needs to be loaded as the least significant bit (LSB) of word i when the shift occurs. 

**Loop Dependency Removal.** In order to solve the two-level data dependency limitation of the baseline Bitap algorithm, GenASM-DC performs loop unrolling and enables computing non-neighbor (i.e., independent) bitvectors in parallel. Please note that current CPU implementation of GenASM-DC does not reflect this modification, but we will update our release with this remaining modification soon.

**Text-Level Parallelism.** In addition to the parallelism enabled by removing the loop dependencies, we enable GenASM-DC algorithm to exploit text-level parallelism. This parallelism is enabled by dividing the text into overlapping sub-texts and searching the query in each of these sub-texts in parallel. The overlap ensures that we do not miss any possible match that may fall around the edges of a sub-text. To guarantee this, the overlap needs to be of length m + k, where m is the query length and k is the edit distance threshold.

## GenASM-TB Algorithm

After finding the matching location of the text and the edit distance with GenASM-DC, our new traceback algorithm, GenASM-TB, finds the sequence of matches, substitutions, insertions and deletions, along with their positions (i.e., CIGAR string) for the matched region (i.e., the text region that starts from the location reported by GenASM-DC and has a length of m + k), and reports the optimal alignment. Traceback execution (1) starts from the first character of the matched region between the reference text and query pattern, (2) examines each character and decides which of the four operations should be picked in each iteration, and (3) ends when we reach the last character of the matched region. 

GenASM-TB uses the intermediate bitvectors generated and saved in each iteration of the GenASM-DC algorithm (i.e., match, substitution, deletion and insertion bitvectors). After a value 0 is found at the MSB of one of the R[d] bitvectors (i.e., a string match is found with d errors), GenASM-TB walks through the bitvectors back to the LSB, following a chain of 0s (which indicate matches at each location) and reverting the bitwise operations. At each position, based on which of the four bitvectors holds a value 0 in each iteration (starting with an MSB with a 0 and ending with an LSB with a 0), the sequence of matches, substitutions, insertions and deletions (i.e., traceback output) is found for each position of the corresponding alignment found by GenASM-DC. Unlike GenASM-DC, GenASM-TB has an irregular control flow within the stored intermediate bitvectors, which depends on the text and the pattern.

<!---
**Divide-and-Conquer Approach.** Since GenASM-DC stores all of the intermediate bitvectors, in the worst case, the length of the text region that the query pattern maps to can be m + k, assuming all of the errors are deletions from the pattern. Since we need to store all of the bitvectors for m + k characters, and compute 4 × k many bitvectors within each text iteration (each m bits long), the memory requirement is ((m + k) × 4 × k × m) bits.
In order to decrease the memory footprint of the algorithm, we apply a divide-and-conquer approach. Instead of storing all of the bitvectors for m + k text characters, we divide the text and pattern into overlapping windows (i.e., sub-text and sub-pattern) and perform the traceback computation for each window. After all of the windows’ partial traceback outputs are generated, we merge them to find the complete traceback output. This approach helps us to to (W × 4 × W × W) bits, where W is the window size.
-->

## Running GenASM

### Read Alignment (DC+TB)

Call the following function in genasm_aligner.c file in your C code or update the existing main() in genasm_aligner.c file:

```bash
genasm_aligner(<reference sequence>, <query sequence>, <edit distance threshold>, <match score>, <substitution penalty>, <gap-opening penalty>, <gap-extension penalty>)
```
For example:

```bash
genasm_aligner("AATGTCC", "ATCTCGC", 3, 3, 4, 5, 1);
```

### Pre-Alignment Filtering (DC only)

Call the following function in genasm_filter.c file in your code or update the existing main() in genasm_filter.c file:

```bash
genasm_filter(<reference sequence>, <query sequence>, <edit distance threshold>)
```
For example:

```bash
genasm_filter("ACTACGCTTGAAATCCACAAGCATGCTGAG", "ACAAAGCTTGAATCCAGAAGCATGCTAGAG", 6);
```

## Citation
>Damla Senol Cali, Gurpreet S. Kalsi, Zülal Bingöl, Can Firtina, Lavanya Subramanian, Jeremie S. Kim, Rachata Ausavarungnirun, Mohammed Alser, Juan Gomez-Luna, Amirali Boroumand, Anant Nori, Allison Scibisz, Sreenivas Subramoney, Can Alkan, Saugata Ghose, and Onur Mutlu.
[**"GenASM: A High-Performance, Low-Power Approximate String Matching Acceleration Framework for Genome Sequence Analysis."**](https://people.inf.ethz.ch/omutlu/pub/GenASM-approximate-string-matching-framework-for-genome-analysis_micro20.pdf)
In _Proceedings of the 53rd International Symposium on Microarchitecture (MICRO),_ Virtual, October 2020.

## Talks
The presentations of the paper are available on YouTube:

* [ARM Research Summit Talk Video (21 minutes)](https://www.youtube.com/watch?v=oKYqVo1UTdE)

* [ARM Research Summit Short Talk Video (15 minutes)](https://www.youtube.com/watch?v=omqCTHlnMA0)

* [ARM Research Summit Short Talk Video and Q&A (31 minutes)](https://www.youtube.com/watch?v=y1S6gtGz2bo) 

* [MICRO 2020 Full Talk Video (18 minutes)](https://www.youtube.com/watch?v=srQVqPJFqjo&t=5s)
  * [Slides (PDF)](https://people.inf.ethz.ch/omutlu/pub/GenASM-approximate-string-matching-framework-for-genome-analysis_micro20-talk.pdf)

* [MICRO 2020 Lightning Talk Video (1.5 minutes)](https://www.youtube.com/watch?v=nJs3RRnvk_k&t=2s) 
  * [Slides (PDF)](https://people.inf.ethz.ch/omutlu/pub/GenASM-approximate-string-matching-framework-for-genome-analysis_micro20-lightning-talk.pdf)

## Contact
Damla Senol Cali (dsenol@andrew.cmu.edu)
