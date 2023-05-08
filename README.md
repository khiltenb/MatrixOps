# MatrixOps Library

Hello! This is a repo designed to create a cpp library of matrix operations that should help others understand how different matrix operations work as well as helping me in the process. Please be patient, as this is my first attempt at building a library. I'll detail updates here.


### **Update: 05/07/2023**
Update 1! Kicking this project off, I'm only enabling Matrix addition, subtraction, and multiplication. Additionally, it will be possible to create empty matrices, define your own, or implement one using a text file. 

I'm still working on creating this as a library, and will continue to do so over the course of this summer. Updates will be provided here when they come through. At the moment, I'm holding off on creating it as a library until I can support the numerous matrix functions that I'd like to as well as making it somewhat cross-platform through the use of pre-processor directives (this is a work in progress, I don't fully understand them and will need to learn the differences in C/C++ across Mac, Windows, and Linux). In the meantime, however, we will be using the MatrixDriver.cc file as a testing ground on Mac/Linux. 

Windows will have support eventually, however, this package is more geared towards exploration of algorithms for matrix computations and linear algebra generally, and is meant more for education than anything else. Please use this to learn and explore. Have fun!

### **List of Capabilities**
* Addition
* Subtraction

* Scalar Multiplication (int, float, and double compliant)
* Equality (operator==)
* Change Dimensions
* Text File Construction

### **Contributions**
If anyone would like to contribute, please fork, branch and pull request as is standard.


### **Roadmap**
#### Next up:
* Refining the system to be more generous towards input text files.
* Code refactorization
* Support for the transpose of a matrix
* Support for matrix determinants
* Support for Multiplication (Matrix-Matrix)