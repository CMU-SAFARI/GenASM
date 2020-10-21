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

## Installing and Running GenASM

### Read Alignment (DC+TB)

### Pre-Alignment Filtering (DC only)

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
