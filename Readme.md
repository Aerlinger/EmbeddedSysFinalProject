# [CS 4840 Embedded Systems] (http://www.cs.columbia.edu/~sedwards/classes/2013/4840/index.html) Final Project

---
## Team
* Anthony Erlinger (Team management, Software Design, Testing, and
low-level design)
* Arthy Padma Anandhi Sundaram (Software and ISA design)
* Yu Chen (Architecture and RTL)
* Jaebin Choi (Low-Level and RTL)   

##### [Columbia University] (www.columbia.edu) Fall 2013

## Abstract
The primary objective, and **first milestone** of this project is to build an implementation of a
MOS 6502 CPU on the Altera DE2.  Given its prominent history, there is a
wealth of data available regarding the implementation of the 6502. We
intend to reproduce the chip in VHDL by studying both its
microarchitecture and physical layout and as well as its “black box”
instruction set architecture.  

The **second milestone** will involve interfacing the 6502 with the Altera’s
network interface and processing the incoming hardware stream at a very
low level. We will also run extensive tests on our implementation to be
sure that we can process the incoming network data in a meaningful way.

Our **third milestone** is the most difficult will involve the processing
the incoming data with the 6502. Given the high bandwidth of the input,
some additional hardware may be necessary to downsample the incoming
data at a reasonable throughput for the 6502. It is also reasonable to
assume that much of the input will be pseudo-random. Therefore, we will
perform basic operations on the data to make it more “palatable” to the
human ear. Toward this end, basic instructions running within the CPU
itself will process the incoming data stream to perform basic filtering
operations (delay, modulation, volume, and so on) followed by piping the
processed data to the sound card.


### Hardware RTL Design (Stage I):
1. Retrieve raw data from network card on Altera DE2 and store in RAM.
2. Design a basic CPU architecture to process data from the sound card
code from NIOS

### Software Design (Stage II):
1. Write rigourous tests to very implementation in stage I.
2. Fetch and store data into RAM or memory-mapped IO.


### DSP and higher level applications (Stage III):
1. Running C code on 6502 see [compiler](http://www.cc65.org) in references.
3. Signal Processing: Run a closed loop running in a regular interval that:  
  a. Fetches data from RAM  
  b. Basic processing (Type)  
  c. Send data to output device (Audio or Video)  

### Deadlines
 * **Milestone I:** Apr. 2  
 * **Milestone II:** Apr. 16  
 * **Milestone III:** Apr. 30  
 

### Noteworthy Challenges:
1. C code compilation  
2. Implementing fully functional 6502 ISA  
3. Stability and synchronization/clocking  
 

### 6502 Components:

  * 17 registers (Yu Chen and Anthony):
    Data Latch, (DL) (Start with data latch)
    Accumulator, (AC) 
    X, Y registers
    A, B (ALU inputs)
    ALU Hold Register (ADD)
    Timing generation Logic
    Stack Register (S)
    Address Register (ABL, ABH)
    PCL & PCH
    Predecode Register (PD)
    Instruction Reg. (IR)
    Processor Status (P)
    Data Output (DOR)

  * Combinational Components (Jaebin and Arthy):
    Random Control Logic 
    Predecode Logic 
    Program Counter Logic 
    Decode Rom
    ALU

  * Ancillary components:
    Interrupt and Reset Control
    Ready Control
    Clock generator

### Getting started:
Read and understand the first two references listed below. It's also a
good idea to become proficent in VHDL before attempting the project as
it will likely save time down the line.

#### Project Basecamp Site: https://basecamp.com/2199038/projects/2382494-cs-4840-final

## Important References:
* 6502 Assembly Demo: http://skilldrick.github.com/easy6502/
* 6502 Programming manual: http://arlet.home.xs4all.nl/mcs6500_family_programming_manual.pdf
* Interactive Simulator: http://visual6502.org/JSSim/index.html
* MOS 6502 CPU: http://visual6502.org/
* General Resources: http://www.6502.org/
* 6502 Forums: http://forum.6502.org/
* 6502 C Compiler: http://www.cc65.org/
* Git Repo: http://www.cs.columbia.edu/~sedwards/classes/2013/4840/git-tutorial.pdf
