## lec1: number representation

1. 

   data input: analog -> digital

   bits can represent anything

#### binary decimal hex

1. Decimal vs Hexadecimal vs Binary

   | d    | h    | b    |
   | ---- | ---- | ---- |
   | 00   | 0    | 0000 |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |
   |      |      |      |

#### number representations

1. 用来加减乘除,比较.  太大会溢出
2. ?怎么表示负数(sign and magnitude) 缺点
3. ? one's complement 以及缺点

#### two's complement & bias encoding

1. two's complement ?overflow

2. ?formula 

   1101(two) =

3. ? bias encoding

## lec2: c intro

1. ?c pre-processor.

2. ?cpp macros: a warning.

3. c int should be integer type that target processor works with most efficiently.

   only guarantee: 

   	* sizeof(long long) >= sizeof(long) >= sizeof(int) >= sizeof(short)
   	* short >= 16bits, long >= 32bits
   	* all could be 64 bits.
   	* this is why we encourang you to us intN_t and uintN-t

##  lec3: bugs, and pointers

1.  an importent note: undefined behavior(often unpredictable)

   Heisenbugs and Bohrbugs

2. ?generic pointer. ?pointers to functions.

3. ?the pointer of all 0s.

4. ?modern machines are "byte-addressable"

5. ?word alignment.

6. ```c
   char *foo() {
   char string[32]; ...;
   return string;
   } is incorrect
   ```

7. ?int ARRAY_SIZE = 10;

8.  Pitfall: An array in C does not know its own 
   length, & bounds not checked!

9. ?sefmentation faults and bus errors

10. ?pointer + n(pointer arithmetic)

11. java and c pass paremeters "by value"

















































































