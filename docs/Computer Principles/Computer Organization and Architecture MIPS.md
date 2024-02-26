
---
Organization vs. Architecture
计算机组成表示其体系结构的具体实现。

A computer's *organization* represents the *implementation* of its *architecture*.

We are interested in *what* a computer does rather than *how* it works.

--- 

机器字长：计算机能直接处理的二进制数据的位数，机器字长一般等于内部寄存器的大小，它决定了计算机的运算精度。

存储字长：一个存储单元存储的二进制代码的长度。

指令字长：一条指令字中包含的二进制代码的位数。


# Chapter 2. Instructions: Language of the Computer
> `instruction set` The vocabulary of commands understood by a given architecture.

The words of a computer's language are called `instructions`, and its vocabulary is called an `instruction set`.

## 2.1 What is the ISA?

### 2.1.1 Concept




有了指令集架构，便可以使用不同的处理器硬件实现方案来设计不同性能的处理器。指令集架构可以理解为一个抽象层，构成处理器底层硬件与运行于其上的软件之间的桥梁与接口，是软/硬件的交界面，屏蔽硬件实现细节，简化程序员的使用。

ISA 才是区分不同 CPU 的主要标准。

指令集架构风格主要分为复杂指令集（Complex Instruction Set Computer，CISC）和精简指令集（Reduced Instruction Set Computer，RISC）。除了 CISC 与 RISC 之分，处理器指令集架构的位数也被分为 8 位、16 位、32 位和 64 位。

CISC 和 RISC 比较：

位数是指通用寄存器的宽度，其决定了寻址范围的大小、数据运算能力的强弱。譬如 32 位架构的处理器，其通用寄存器的的宽度为 32 位，能够寻址的范围为 2^32，即 4GB 的寻址空间，运算指令可以操作的操作数为 32 位。处理器指令集架构的宽度和指令的编码长度无任何关系。

理论上来讲：
- 通用寄存器宽度，即指令集架构的位数越多越好，因为这样可以嗲来更大的寻址范围和更强的运算能力。
- 指令编码的长度越短越好，因为这样可以更加节省代码的存储空间。



常用指令集架构：
| ISA | Types | Company|
| :--: | :--: | :--: |
| MIPS (Microprocessor without Interlocked Piped Stages Architecture) <br/> | RISC | MIPS |
| x86 | CISC | Intel、AMD |
| ARM | RISC | ARM |

MIPS, ARM and x86-64 are three popular instruction sets for microprocessor.

**Instruction Set Architecture (ISA)** describes the programmer's abstract view of the computer and defines its assembly language and programming model.


### 2.1.2 The Componenets of an ISA

The three elements of an ISA: its register set, its addressing modes, and its instruction formats.

#### 1. Registers

MIPS has a classic 32-bit load-and-store ISA and 32 general-purpose registers.


MIPS Register Naming Convertions
| Name | MIPS Name | Assembly Name | Use |
| :--: | :--:| :--: | :--: |
| r0 | $0 | $zero | Constant 0 |
| r1 | $1 | $at | Reserved for assembler |
| r2 | $2 | $v0 | Expression evaluation and results of a function |
| r3 | $3 | $v1 | Expression evaluation and results of a function |
| r4 | $4 | $a0 | Argument 1 |
| r5 | $5 | $a1 | Argument 2 |
| r6 | $6 | $a2 | Argument 3 |
| r7 | $7 | $a3 | Argument 4 |
| r8 | $8 | $t0 | Temporary (not preserved across call) |
| r9 | $9 | $t1 | Temporary (not preserved across call) |
| r10 | $10 | $t2 | Temporary (not preserved across call) |
| r11 | $11 | $t3 | Temporary (not preserved across call) |
| r12 | $12 | $t4 | Temporary (not preserved across call) |
| r13 | $13 | $t5 | Temporary (not preserved across call) |
| r14 | $14 | $t6 | Temporary (not preserved across call) |
| r15 | $15 | $t7 | Temporary (not preserved across call) |
| r16 | $16 | $s0 | Saved temporary (preserved across call) |
| r17 | $17 | $s1 | Saved temporary (preserved across call) |
| r18 | $18 | $s2 | Saved temporary (preserved across call) |
| r19 | $19 | $s3 | Saved temporary (preserved across call) |
| r20 | $20 | $s4 | Saved temporary (preserved across call) |
| r21 | $21 | $s5 | Saved temporary (preserved across call) |
| r22 | $22 | $s6 | Saved temporary (preserved across call) |
| r23 | $23 | $s7 | Saved temporary (preserved across call) |
| r24 | $24 | $t8 | Temporary (not preserved across call) |
| r25 | $25 | $t9 | Temporary (not preserved across call) |
| r26 | $26 | $k0 | Reserved for OS kernel |
| r27 | $27 | $k1 | Reserved for OS kernel |
| r28 | $28 | $gp | Pointer to global area |
| r29 | $29 | $sp | Stack pointer |
| r30 | $30 | $fp | Frame pointer |
| r31 | $31 | $ra | Return adress (used by function call) |



#### 2. Instruction Formats

指令的数字形式称为机器语言


#### 3. Addressing Modes - an Overview






---
指令集体系结构包括：数据类型（每个字的位数以及各个位的含义），用来保存临时结果的寄存器，指令的类型和格式，以及寻址方式（表示数据在存储器中存放位置的方法）。

***An instruction set architecture includes data types (the number of bits per word and the interpretation of the bits), the registers used to hold temporary data, the type of instructions and their formats, and the addressing modes (ways of expressing the location of data in memory).***

---





Giving a sneak preview of the instruction set covered in this chapter (including operands and assembly language):
![MIPS assembly language](../images/MIPS%20operands%20and%20assembly%20language.png)

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



---

Four underlying principles of hardware design:

Hardware for a variable number of operands is more complicated than hardware for a fixed number.\
*Design Principle 1*: Simplicity favors regularity.

硬件设计四条基本原则：
1. 简单源于规整（操作数个数可变将给硬件设计带来更大的复杂性）
2. 越少越快（大量的寄存器可能会使时钟周期变长，因为需要更远的电信号传输距离）