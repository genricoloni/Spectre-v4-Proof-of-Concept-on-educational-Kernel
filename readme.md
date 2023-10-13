# Read Me!

Some important things to know before look at the code and read the thesis.

## The kernel

The kernel I used for my thesis was been developed by Giuseppe Lettieri, who was aldo my supervisor for this work. You can find the full code at [this link](https://calcolatori.iet.unipi.it/) (search for "Nucleo a 64 bit"): unfortunately instructions are available only in italian. Kernel is used for a course called "Calcolatori Elettronici", which is in the program of the Bachelor degree in Computer Engineering at University of Pisa, and also for some thesis such this one. 

## Proof of Concpet

I use a PoC found in [this](https://github.com/mmxsrup/CVE-2018-3639) repo, I changed some details in order to let the code work in this kernel.

## The thesis

Unfortunately, also this document is available in italian only. Briefly, it contains an overview on **memory hierarchy** on modern computers, a summary about Spectre vulnerability, then it goes deep on Spectre v4 and the behavior of the PoC inside the Kernel, with some analysis about the output of the code. In the bibliography you can find some resources that I used as reference the understand Spectre v4, the memory disambiguation on Intel CPUs and some other details on CPU architecture.