
## Chapter 2. Instructions: Language of the Computer
> `instruction set` The vocabulary of commands understood by a given architecture.

The words of a computer's language are called `instructions`, and its vocabulary is called an `instruction set`.

MIPS, ARM and x86-64 are three popular instruction sets for microprocessor.

Giving a sneak preview of the instruction set covered in this chapter (including operands and assembly language):
![MIPS assembly language](./images/MIPS%20operands%20and%20assembly%20language.png)

The natural number of operands for an operation like addition is three: the two numbers being added together and a place to put the sum.


---

f = (g + h) - (i + j)

add t0 g, h \
add t1, i, j \
sub f, t0, t1

=> \
add $t0, $s1, $s2 \
add $t1, $s3, $s4 \
sub $s0, $t0, $t1

---


> `word` The natural unit of access in a computer, usually a group of 32 bits; corresponds to the size of a register in the MIPS architecture.

The size of a register in the MIPS acchitecture is 32 bits; groups of 32 bits occur so frequently that they are given the name `word` tin the MIPS architecture.

The MIPS convertion is to use two-character names following a dollar sign to represent a register.


It is compiler's job to associate program variables with registers.

MIPS uses byte addressing.

lw $t0, 32($s3) \
add $t0, $s2, $t0 \
sw $t0, 48($t3)