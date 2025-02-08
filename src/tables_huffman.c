#include <tables_huffman.h>
// #include "../include/tables_huffman.h"

//Table DC_Y

/*
0 : 00 
1 : 010 
2 : 011 
3 : 100 
4 : 101 
5 : 110 
6 : 1110 
7 : 11110 
8 : 111110 
9 : 1111110 
a : 11111110 
b : 111111110 
*/


uint16_t code_huffman_DC_Y[] = {
0b00, 	0b010, 	0b011, 	0b100, 	0b101, 	0b110, 	0b1110, 	0b11110, 	0b111110, 	0b1111110, 	0b11111110, 	0b111111110 
};

//Table DC_Cb_Cr

/*
0 : 00 
1 : 01 
2 : 10 
3 : 110 
4 : 1110 
5 : 11110 
6 : 111110 
7 : 1111110 
8 : 11111110 
9 : 111111110 
a : 1111111110 
b : 11111111110 
*/

uint16_t code_huffman_DC_CbCr[] = {
0b00, 	0b01, 	0b10, 	0b110, 	0b1110, 	0b11110, 	0b111110, 	0b1111110, 	0b11111110, 	0b111111110, 	0b1111111110, 	0b11111111110
};

//Table AC_Y

// 1 : 00 
// 2 : 01 
// 3 : 100 
// 0 : 1010 
// 4 : 1011 
// 11 : 1100 
// 5 : 11010 
// 12 : 11011 
// 21 : 11100 
// 31 : 111010 
// 41 : 111011 
// 6 : 1111000 
// 13 : 1111001 
// 51 : 1111010 
// 61 : 1111011 
// 7 : 11111000 
// 22 : 11111001 
// 71 : 11111010
// 14 : 111110110 
// 32 : 111110111 
// 81 : 111111000 
// 91 : 111111001 
// a1 : 111111010 
// 8 : 1111110110 
// 23 : 1111110111 
// 42 : 1111111000 
// b1 : 1111111001 
// c1 : 1111111010 
// 15 : 11111110110 
// 52 : 11111110111 
// d1 : 11111111000 
// f0 : 11111111001 
// 24 : 111111110100 
// 33 : 111111110101 
// 62 : 111111110110 
// 72 : 111111110111 
// 82 : 111111111000000 
// 9 : 1111111110000010 
// a : 1111111110000011 
// 16 : 1111111110000100 
// 17 : 1111111110000101 
// 18 : 1111111110000110 
// 19 : 1111111110000111 
// 1a : 1111111110001000 
// 25 : 1111111110001001 
// 26 : 1111111110001010 
// 27 : 1111111110001011 
// 28 : 1111111110001100 
// 29 : 1111111110001101 
// 2a : 1111111110001110 
// 34 : 1111111110001111 
// 35 : 1111111110010000 
// 36 : 1111111110010001 
// 37 : 1111111110010010 
// 38 : 1111111110010011 
// 39 : 1111111110010100 
// 3a : 1111111110010101 
// 43 : 1111111110010110 
// 44 : 1111111110010111 
// 45 : 1111111110011000 
// 46 : 1111111110011001 
// 47 : 1111111110011010 
// 48 : 1111111110011011 
// 49 : 1111111110011100 
// 4a : 1111111110011101 
// 53 : 1111111110011110 
// 54 : 1111111110011111 
// 55 : 1111111110100000 
// 56 : 1111111110100001 
// 57 : 1111111110100010 
// 58 : 1111111110100011 
// 59 : 1111111110100100 
// 5a : 1111111110100101 
// 63 : 1111111110100110 
// 64 : 1111111110100111 
// 65 : 1111111110101000 
// 66 : 1111111110101001 
// 67 : 1111111110101010 
// 68 : 1111111110101011 
// 69 : 1111111110101100 
// 6a : 1111111110101101 
// 73 : 1111111110101110 
// 74 : 1111111110101111 
// 75 : 1111111110110000 
// 76 : 1111111110110001 
// 77 : 1111111110110010 
// 78 : 1111111110110011 
// 79 : 1111111110110100 
// 7a : 1111111110110101 
// 83 : 1111111110110110 
// 84 : 1111111110110111 
// 85 : 1111111110111000 
// 86 : 1111111110111001 
// 87 : 1111111110111010 
// 88 : 1111111110111011 
// 89 : 1111111110111100 
// 8a : 1111111110111101 
// 92 : 1111111110111110 
// 93 : 1111111110111111 
// 94 : 1111111111000000 
// 95 : 1111111111000001 
// 96 : 1111111111000010 
// 97 : 1111111111000011 
// 98 : 1111111111000100 
// 99 : 1111111111000101 
// 9a : 1111111111000110 
// a2 : 1111111111000111 
// a3 : 1111111111001000 
// a4 : 1111111111001001 
// a5 : 1111111111001010 
// a6 : 1111111111001011 
// a7 : 1111111111001100 
// a8 : 1111111111001101 
// a9 : 1111111111001110 
// aa : 1111111111001111 
// b2 : 1111111111010000 
// b3 : 1111111111010001 
// b4 : 1111111111010010 
// b5 : 1111111111010011 
// b6 : 1111111111010100 
// b7 : 1111111111010101 
// b8 : 1111111111010110 
// b9 : 1111111111010111 
// ba : 1111111111011000 
// c2 : 1111111111011001 
// c3 : 1111111111011010 
// c4 : 1111111111011011 
// c5 : 1111111111011100 
// c6 : 1111111111011101 
// c7 : 1111111111011110 
// c8 : 1111111111011111 
// c9 : 1111111111100000 
// ca : 1111111111100001 
// d2 : 1111111111100010 
// d3 : 1111111111100011 
// d4 : 1111111111100100 
// d5 : 1111111111100101 
// d6 : 1111111111100110 
// d7 : 1111111111100111 
// d8 : 1111111111101000 
// d9 : 1111111111101001 
// da : 1111111111101010 
// e1 : 1111111111101011 
// e2 : 1111111111101100 
// e3 : 1111111111101101 
// e4 : 1111111111101110 
// e5 : 1111111111101111 
// e6 : 1111111111110000 
// e7 : 1111111111110001 
// e8 : 1111111111110010 
// e9 : 1111111111110011 
// ea : 1111111111110100 
// f1 : 1111111111110101 
// f2 : 1111111111110110 
// f3 : 1111111111110111 
// f4 : 1111111111111000 
// f5 : 1111111111111001 
// f6 : 1111111111111010 
// f7 : 1111111111111011 
// f8 : 1111111111111100 
// f9 : 1111111111111101 
// fa : 1111111111111110

uint16_t code_huffman_AC_Y[] = {
0b00, 	0b01, 	0b100, 	0b1010, 	0b1011, 	0b1100, 	0b11010, 	0b11011, 	0b11100, 	0b111010, 	0b111011, 	0b1111000, 	0b1111001, 	
0b1111010, 	0b1111011, 	0b11111000, 	0b11111001, 	0b11111010, 	0b111110110, 	0b111110111, 	0b111111000, 	0b111111001, 	0b111111010, 	
0b1111110110, 	0b1111110111, 	0b1111111000, 	0b1111111001, 	0b1111111010, 	0b11111110110, 	0b11111110111, 	0b11111111000, 	0b11111111001, 	0b111111110100, 	
0b111111110101, 	0b111111110110, 	0b111111110111, 	0b111111111000000, 	0b1111111110000010, 	0b1111111110000011, 	0b1111111110000100, 	
0b1111111110000101, 	0b1111111110000110, 	0b1111111110000111, 	0b1111111110001000, 	0b1111111110001001, 	0b1111111110001010, 	0b1111111110001011, 	
0b1111111110001100, 	0b1111111110001101, 	0b1111111110001110, 	0b1111111110001111, 	0b1111111110010000, 	0b1111111110010001, 	0b1111111110010010, 	
0b1111111110010011, 	0b1111111110010100, 	0b1111111110010101, 	0b1111111110010110, 	0b1111111110010111, 	0b1111111110011000, 	0b1111111110011001, 	
0b1111111110011010, 	0b1111111110011011, 	0b1111111110011100, 	0b1111111110011101, 	0b1111111110011110, 	0b1111111110011111, 	0b1111111110100000, 	
0b1111111110100001, 	0b1111111110100010, 	0b1111111110100011, 	0b1111111110100100, 	0b1111111110100101, 	0b1111111110100110, 	0b1111111110100111, 	
0b1111111110101000, 	0b1111111110101001, 	0b1111111110101010, 	0b1111111110101011, 	0b1111111110101100, 	0b1111111110101101, 	0b1111111110101110, 	
0b1111111110101111, 	0b1111111110110000, 	0b1111111110110001, 	0b1111111110110010, 	0b1111111110110011, 	0b1111111110110100, 	0b1111111110110101, 	
0b1111111110110110, 	0b1111111110110111, 	0b1111111110111000, 	0b1111111110111001, 	0b1111111110111010, 	0b1111111110111011, 	0b1111111110111100, 	
0b1111111110111101, 	0b1111111110111110, 	0b1111111110111111, 	0b1111111111000000, 	0b1111111111000001, 	0b1111111111000010, 	0b1111111111000011, 	
0b1111111111000100, 	0b1111111111000101, 	0b1111111111000110, 	0b1111111111000111, 	0b1111111111001000, 	0b1111111111001001, 	0b1111111111001010, 	
0b1111111111001011, 	0b1111111111001100, 	0b1111111111001101, 	0b1111111111001110, 	0b1111111111001111, 	0b1111111111010000, 	0b1111111111010001, 	
0b1111111111010010, 	0b1111111111010011, 	0b1111111111010100, 	0b1111111111010101, 	0b1111111111010110, 	0b1111111111010111, 	0b1111111111011000, 	
0b1111111111011001, 	0b1111111111011010, 	0b1111111111011011, 	0b1111111111011100, 	0b1111111111011101, 	0b1111111111011110, 	0b1111111111011111, 	
0b1111111111100000, 	0b1111111111100001, 	0b1111111111100010, 	0b1111111111100011, 	0b1111111111100100, 	0b1111111111100101, 	0b1111111111100110, 	
0b1111111111100111, 	0b1111111111101000, 	0b1111111111101001, 	0b1111111111101010, 	0b1111111111101011, 	0b1111111111101100, 	0b1111111111101101, 	
0b1111111111101110, 	0b1111111111101111, 	0b1111111111110000, 	0b1111111111110001, 	0b1111111111110010, 	0b1111111111110011, 	0b1111111111110100, 	
0b1111111111110101, 	0b1111111111110110, 	0b1111111111110111, 	0b1111111111111000, 	0b1111111111111001, 	0b1111111111111010, 	0b1111111111111011, 	
0b1111111111111100, 	0b1111111111111101, 	0b1111111111111110
};

// Table AC_Cb

/*
0 : 00 
1 : 01 
2 : 100 
3 : 1010 
11 : 1011 
4 : 11000 
5 : 11001 
21 : 11010 
31 : 11011 
6 : 111000 
12 : 111001 
41 : 111010 
51 : 111011 
7 : 1111000 
61 : 1111001 
71 : 1111010 
13 : 11110110 
22 : 11110111 
32 : 11111000 
81 : 11111001 
8 : 111110100 
14 : 111110101 
42 : 111110110 
91 : 111110111 
a1 : 111111000 
b1 : 111111001 
c1 : 111111010 
9 : 1111110110 
23 : 1111110111 
33 : 1111111000 
52 : 1111111001 
f0 : 1111111010 
15 : 11111110110 
62 : 11111110111 
72 : 11111111000 
d1 : 11111111001 
a : 111111110100 
16 : 111111110101 
24 : 111111110110 
34 : 111111110111 
e1 : 11111111100000 
25 : 111111111000010 
f1 : 111111111000011
17 : 1111111110001000 
18 : 1111111110001001 
19 : 1111111110001010 
1a : 1111111110001011 
26 : 1111111110001100 
27 : 1111111110001101 
28 : 1111111110001110 
29 : 1111111110001111 
2a : 1111111110010000 
35 : 1111111110010001 
36 : 1111111110010010 
37 : 1111111110010011 
38 : 1111111110010100 
39 : 1111111110010101 
3a : 1111111110010110 
43 : 1111111110010111 
44 : 1111111110011000 
45 : 1111111110011001 
46 : 1111111110011010 
47 : 1111111110011011 
48 : 1111111110011100 
49 : 1111111110011101 
4a : 1111111110011110 
53 : 1111111110011111 
54 : 1111111110100000 
55 : 1111111110100001 
56 : 1111111110100010 
57 : 1111111110100011 
58 : 1111111110100100 
59 : 1111111110100101 
5a : 1111111110100110 
63 : 1111111110100111 
64 : 1111111110101000 
65 : 1111111110101001 
66 : 1111111110101010 
67 : 1111111110101011 
68 : 1111111110101100 
69 : 1111111110101101 
6a : 1111111110101110 
73 : 1111111110101111 
74 : 1111111110110000 
75 : 1111111110110001 
76 : 1111111110110010 
77 : 1111111110110011 
78 : 1111111110110100 
79 : 1111111110110101 
7a : 1111111110110110 
82 : 1111111110110111 
83 : 1111111110111000 
84 : 1111111110111001 
85 : 1111111110111010 
86 : 1111111110111011 
87 : 1111111110111100 
88 : 1111111110111101 
89 : 1111111110111110 
8a : 1111111110111111 
92 : 1111111111000000 
93 : 1111111111000001 
94 : 1111111111000010 
95 : 1111111111000011 
96 : 1111111111000100 
97 : 1111111111000101 
98 : 1111111111000110 
99 : 1111111111000111 
9a : 1111111111001000 
a2 : 1111111111001001 
a3 : 1111111111001010 
a4 : 1111111111001011 
a5 : 1111111111001100 
a6 : 1111111111001101 
a7 : 1111111111001110 
a8 : 1111111111001111 
a9 : 1111111111010000 
aa : 1111111111010001 
b2 : 1111111111010010 
b3 : 1111111111010011 
b4 : 1111111111010100 
b5 : 1111111111010101 
b6 : 1111111111010110 
b7 : 1111111111010111 
b8 : 1111111111011000 
b9 : 1111111111011001 
ba : 1111111111011010 
c2 : 1111111111011011 
c3 : 1111111111011100 
c4 : 1111111111011101 
c5 : 1111111111011110 
c6 : 1111111111011111 
c7 : 1111111111100000 
c8 : 1111111111100001 
c9 : 1111111111100010 
ca : 1111111111100011 
d2 : 1111111111100100 
d3 : 1111111111100101 
d4 : 1111111111100110 
d5 : 1111111111100111 
d6 : 1111111111101000 
d7 : 1111111111101001 
d8 : 1111111111101010 
d9 : 1111111111101011 
da : 1111111111101100 
e2 : 1111111111101101 
e3 : 1111111111101110 
e4 : 1111111111101111 
e5 : 1111111111110000 
e6 : 1111111111110001 
e7 : 1111111111110010 
e8 : 1111111111110011 
e9 : 1111111111110100 
ea : 1111111111110101 
f2 : 1111111111110110 
f3 : 1111111111110111 
f4 : 1111111111111000 
f5 : 1111111111111001 
f6 : 1111111111111010 
f7 : 1111111111111011 
f8 : 1111111111111100 
f9 : 1111111111111101 
fa : 1111111111111110 
*/

uint16_t code_huffman_AC_CbCr[] = {
0b00, 	0b01, 	0b100, 	0b1010, 	0b1011, 	0b11000, 	0b11001, 	0b11010, 	0b11011, 	0b111000, 	0b111001, 	0b111010, 	0b111011, 	0b1111000, 	
0b1111001, 	0b1111010, 	0b11110110, 	0b11110111, 	0b11111000, 	0b11111001, 	0b111110100, 	0b111110101, 	0b111110110, 	0b111110111, 	0b111111000, 	
0b111111001, 	0b111111010, 	0b1111110110, 	0b1111110111, 	0b1111111000, 	0b1111111001, 	0b1111111010, 	0b11111110110, 	0b11111110111, 	0b11111111000, 	
0b11111111001, 	0b111111110100, 	0b111111110101, 	0b111111110110, 	0b111111110111, 0b11111111100000, 	0b111111111000010, 	0b111111111000011, 	
0b1111111110001000, 	0b1111111110001001, 	0b1111111110001010, 	0b1111111110001011, 	0b1111111110001100, 	0b1111111110001101, 	0b1111111110001110, 	
0b1111111110001111, 	0b1111111110010000, 	0b1111111110010001, 	0b1111111110010010, 	0b1111111110010011, 	0b1111111110010100, 	0b1111111110010101, 	
0b1111111110010110, 	0b1111111110010111, 	0b1111111110011000, 	0b1111111110011001, 	0b1111111110011010, 	0b1111111110011011, 	0b1111111110011100, 	
0b1111111110011101, 	0b1111111110011110, 	0b1111111110011111, 	0b1111111110100000, 	0b1111111110100001, 	0b1111111110100010, 	0b1111111110100011, 	
0b1111111110100100, 	0b1111111110100101, 	0b1111111110100110, 	0b1111111110100111, 	0b1111111110101000, 	0b1111111110101001, 	0b1111111110101010, 	
0b1111111110101011, 	0b1111111110101100, 	0b1111111110101101, 	0b1111111110101110, 	0b1111111110101111, 	0b1111111110110000, 	0b1111111110110001, 	
0b1111111110110010, 	0b1111111110110011, 	0b1111111110110100, 	0b1111111110110101, 	0b1111111110110110, 	0b1111111110110111, 	0b1111111110111000, 	
0b1111111110111001, 	0b1111111110111010, 	0b1111111110111011, 	0b1111111110111100, 	0b1111111110111101, 	0b1111111110111110, 	0b1111111110111111, 	
0b1111111111000000, 	0b1111111111000001, 	0b1111111111000010, 	0b1111111111000011, 	0b1111111111000100, 	0b1111111111000101, 	0b1111111111000110, 	
0b1111111111000111, 	0b1111111111001000, 	0b1111111111001001, 	0b1111111111001010, 	0b1111111111001011, 	0b1111111111001100, 	0b1111111111001101, 	
0b1111111111001110, 	0b1111111111001111, 	0b1111111111010000, 	0b1111111111010001, 	0b1111111111010010, 	0b1111111111010011, 	0b1111111111010100, 	
0b1111111111010101, 	0b1111111111010110, 	0b1111111111010111, 	0b1111111111011000, 	0b1111111111011001, 	0b1111111111011010, 	0b1111111111011011, 	
0b1111111111011100, 	0b1111111111011101, 	0b1111111111011110, 	0b1111111111011111, 	0b1111111111100000, 	0b1111111111100001, 	0b1111111111100010, 	
0b1111111111100011, 	0b1111111111100100, 	0b1111111111100101, 	0b1111111111100110, 	0b1111111111100111, 	0b1111111111101000, 	0b1111111111101001, 	
0b1111111111101010, 	0b1111111111101011, 	0b1111111111101100, 	0b1111111111101101, 	0b1111111111101110, 	0b1111111111101111, 	0b1111111111110000, 	
0b1111111111110001, 	0b1111111111110010, 	0b1111111111110011, 	0b1111111111110100, 	0b1111111111110101, 	0b1111111111110110, 	0b1111111111110111, 	
0b1111111111111000, 	0b1111111111111001, 	0b1111111111111010, 	0b1111111111111011, 	0b1111111111111100, 	0b1111111111111101, 	0b1111111111111110
};