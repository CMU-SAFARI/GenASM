# GenASM - Coming up soon!
GenASM is an approximate string matching (ASM) acceleration framework for genome sequence analysis. GenASM is a fast, efficient, and flexible framework for both short and long reads, which can be used to accelerate multiple steps of the genome sequence analysis pipeline. We base GenASM upon the Bitap algorithm. Bitap uses only fast and simple bitwise operations to perform approximate string matching. To our knowledge, GenASM is the first work that enhances and accelerates Bitap.

To use Bitap for GenASM, we make two key algorithmic modifications that allow us to overcome key limitations that prevent the original Bitap algorithm from being efficient for genome sequence analysis. First, to improve Bitap’s applicability to different sequencing technologies and its performance, we (1) modify the algorithm to support long reads (in addition to already supported short reads), and (2) eliminate loop-carried data dependencies so that we can parallelize a single string matching operation. Second, we develop a novel Bitap-compatible algorithm for traceback. The original Bitap algorithm is not capable of performing traceback.

## Citation
>Damla Senol Cali, Gurpreet S. Kalsi, Zülal Bingöl, Can Firtina, Lavanya Subramanian, Jeremie S. Kim, Rachata Ausavarungnirun, Mohammed Alser, Juan Gomez-Luna, Amirali Boroumand, Anant Nori, Allison Scibisz, Sreenivas Subramoney, Can Alkan, Saugata Ghose, and Onur Mutlu.
[**"GenASM: A High-Performance, Low-Power Approximate String Matching Acceleration Framework for Genome Sequence Analysis."**](https://people.inf.ethz.ch/omutlu/pub/GenASM-approximate-string-matching-framework-for-genome-analysis_micro20.pdf)
To appear in _Proceedings of the 53rd International Symposium on Microarchitecture (MICRO),_ Virtual, October 2020.

## Talks
[ARM Research Summit Talk Video (21 minutes)] 
[ARM Research Summit Short Talk Video (15 minutes)] 
[ARM Research Summit Short Talk Video and Q&A (31 minutes)] 
[ARM Research Summit Talk Slides (pptx) (pdf)] 
[ARM Research Summit Short Talk Slides (pptx) (pdf)]

## Contact
Damla Senol Cali (dsenol@andrew.cmu.edu)
