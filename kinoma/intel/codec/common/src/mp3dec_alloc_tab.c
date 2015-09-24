/*//////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2003-2006 Intel Corporation. All Rights Reserved.
//
*/

#include "mp3dec_own.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Table 3-B.2a Possible quantization per subband

Fs = 48 kHz Bit rates per channel = 56, 64, 80, 96, 112, 128, 160, 192 kbits/s,
and free format
Fs = 44.1 kHz Bit rates per channel = 56, 64, 80 kbits/s
Fs = 32 kHz Bit rates per channel = 56, 64, 80 kbits/s
*/
const unsigned char mp3dec_alloc_table1[] =  {
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int mp3dec_nbal_alloc_table1[32] =  {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0, 0, 0, 0
};

/*
Table 3-B.2b. Possible quantization per subband

Fs = 48 kHz -------------- not relevant --------------
Fs = 44.1 kHz Bitrates per channel = 96, 112, 128, 160, 192 kbits/s
and free format
Fs = 32 kHz Bitrates per channel = 96, 112, 128, 160, 192 kbits/s
and free format
*/

const unsigned char mp3dec_alloc_table2[] =  {
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  2,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 16,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5, 16,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int mp3dec_nbal_alloc_table2[32] =  {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 0, 0
};

/*
Table 3-B.2c. Possible quantization per subband


Fs = 48 kHz Bitrates per channel = 32, 48 kbits/s
Fs = 44.1 kHz Bitrates per channel = 32, 48 kbits/s
Fs = 32 kHz -------- not relevant --------
*/
const unsigned char mp3dec_alloc_table3[] =  {
    0,  0,  1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0,  0,  1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0
};

const int mp3dec_nbal_alloc_table3[32] =  {
    4, 4, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/*
Table 3-B.2d. Possible quantization per subband


Fs = 48 kHz  ------- not relevant -------
Fs = 44.1kHz  ------- not relevant -------
Fs = 32 kHz  Bitrates per channel = 32, 48 kbits/s
*/

const unsigned char mp3dec_alloc_table4[] =  {
    0,  0,  1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0,  0,  1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0
};

const int mp3dec_nbal_alloc_table4[32] =  {
    4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
Table B-1 (MPEG 2). Possible quantization per subband

Fs = 16, 22.05, 24 kHz
*/

const unsigned char mp3dec_alloc_table5[] =  {
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  4,  5,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int mp3dec_nbal_alloc_table5[32] =  {
    4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0
};

const int mp3dec_cls_quant[17] = {
    -5, -7, 3, -10, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

const int mp3dec_numbits[17] = {
    2, 3, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

const int mp3dec_sblimit_table[] = {
    27, 30, 8, 12, 30
};

const static short mp3dec_degroup_9[] = {
    0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700,
    0x0800, 0x0010, 0x0110, 0x0210, 0x0310, 0x0410, 0x0510, 0x0610,
    0x0710, 0x0810, 0x0020, 0x0120, 0x0220, 0x0320, 0x0420, 0x0520,
    0x0620, 0x0720, 0x0820, 0x0030, 0x0130, 0x0230, 0x0330, 0x0430,
    0x0530, 0x0630, 0x0730, 0x0830, 0x0040, 0x0140, 0x0240, 0x0340,
    0x0440, 0x0540, 0x0640, 0x0740, 0x0840, 0x0050, 0x0150, 0x0250,
    0x0350, 0x0450, 0x0550, 0x0650, 0x0750, 0x0850, 0x0060, 0x0160,
    0x0260, 0x0360, 0x0460, 0x0560, 0x0660, 0x0760, 0x0860, 0x0070,
    0x0170, 0x0270, 0x0370, 0x0470, 0x0570, 0x0670, 0x0770, 0x0870,
    0x0080, 0x0180, 0x0280, 0x0380, 0x0480, 0x0580, 0x0680, 0x0780,
    0x0880, 0x0001, 0x0101, 0x0201, 0x0301, 0x0401, 0x0501, 0x0601,
    0x0701, 0x0801, 0x0011, 0x0111, 0x0211, 0x0311, 0x0411, 0x0511,
    0x0611, 0x0711, 0x0811, 0x0021, 0x0121, 0x0221, 0x0321, 0x0421,
    0x0521, 0x0621, 0x0721, 0x0821, 0x0031, 0x0131, 0x0231, 0x0331,
    0x0431, 0x0531, 0x0631, 0x0731, 0x0831, 0x0041, 0x0141, 0x0241,
    0x0341, 0x0441, 0x0541, 0x0641, 0x0741, 0x0841, 0x0051, 0x0151,
    0x0251, 0x0351, 0x0451, 0x0551, 0x0651, 0x0751, 0x0851, 0x0061,
    0x0161, 0x0261, 0x0361, 0x0461, 0x0561, 0x0661, 0x0761, 0x0861,
    0x0071, 0x0171, 0x0271, 0x0371, 0x0471, 0x0571, 0x0671, 0x0771,
    0x0871, 0x0081, 0x0181, 0x0281, 0x0381, 0x0481, 0x0581, 0x0681,
    0x0781, 0x0881, 0x0002, 0x0102, 0x0202, 0x0302, 0x0402, 0x0502,
    0x0602, 0x0702, 0x0802, 0x0012, 0x0112, 0x0212, 0x0312, 0x0412,
    0x0512, 0x0612, 0x0712, 0x0812, 0x0022, 0x0122, 0x0222, 0x0322,
    0x0422, 0x0522, 0x0622, 0x0722, 0x0822, 0x0032, 0x0132, 0x0232,
    0x0332, 0x0432, 0x0532, 0x0632, 0x0732, 0x0832, 0x0042, 0x0142,
    0x0242, 0x0342, 0x0442, 0x0542, 0x0642, 0x0742, 0x0842, 0x0052,
    0x0152, 0x0252, 0x0352, 0x0452, 0x0552, 0x0652, 0x0752, 0x0852,
    0x0062, 0x0162, 0x0262, 0x0362, 0x0462, 0x0562, 0x0662, 0x0762,
    0x0862, 0x0072, 0x0172, 0x0272, 0x0372, 0x0472, 0x0572, 0x0672,
    0x0772, 0x0872, 0x0082, 0x0182, 0x0282, 0x0382, 0x0482, 0x0582,
    0x0682, 0x0782, 0x0882, 0x0003, 0x0103, 0x0203, 0x0303, 0x0403,
    0x0503, 0x0603, 0x0703, 0x0803, 0x0013, 0x0113, 0x0213, 0x0313,
    0x0413, 0x0513, 0x0613, 0x0713, 0x0813, 0x0023, 0x0123, 0x0223,
    0x0323, 0x0423, 0x0523, 0x0623, 0x0723, 0x0823, 0x0033, 0x0133,
    0x0233, 0x0333, 0x0433, 0x0533, 0x0633, 0x0733, 0x0833, 0x0043,
    0x0143, 0x0243, 0x0343, 0x0443, 0x0543, 0x0643, 0x0743, 0x0843,
    0x0053, 0x0153, 0x0253, 0x0353, 0x0453, 0x0553, 0x0653, 0x0753,
    0x0853, 0x0063, 0x0163, 0x0263, 0x0363, 0x0463, 0x0563, 0x0663,
    0x0763, 0x0863, 0x0073, 0x0173, 0x0273, 0x0373, 0x0473, 0x0573,
    0x0673, 0x0773, 0x0873, 0x0083, 0x0183, 0x0283, 0x0383, 0x0483,
    0x0583, 0x0683, 0x0783, 0x0883, 0x0004, 0x0104, 0x0204, 0x0304,
    0x0404, 0x0504, 0x0604, 0x0704, 0x0804, 0x0014, 0x0114, 0x0214,
    0x0314, 0x0414, 0x0514, 0x0614, 0x0714, 0x0814, 0x0024, 0x0124,
    0x0224, 0x0324, 0x0424, 0x0524, 0x0624, 0x0724, 0x0824, 0x0034,
    0x0134, 0x0234, 0x0334, 0x0434, 0x0534, 0x0634, 0x0734, 0x0834,
    0x0044, 0x0144, 0x0244, 0x0344, 0x0444, 0x0544, 0x0644, 0x0744,
    0x0844, 0x0054, 0x0154, 0x0254, 0x0354, 0x0454, 0x0554, 0x0654,
    0x0754, 0x0854, 0x0064, 0x0164, 0x0264, 0x0364, 0x0464, 0x0564,
    0x0664, 0x0764, 0x0864, 0x0074, 0x0174, 0x0274, 0x0374, 0x0474,
    0x0574, 0x0674, 0x0774, 0x0874, 0x0084, 0x0184, 0x0284, 0x0384,
    0x0484, 0x0584, 0x0684, 0x0784, 0x0884, 0x0005, 0x0105, 0x0205,
    0x0305, 0x0405, 0x0505, 0x0605, 0x0705, 0x0805, 0x0015, 0x0115,
    0x0215, 0x0315, 0x0415, 0x0515, 0x0615, 0x0715, 0x0815, 0x0025,
    0x0125, 0x0225, 0x0325, 0x0425, 0x0525, 0x0625, 0x0725, 0x0825,
    0x0035, 0x0135, 0x0235, 0x0335, 0x0435, 0x0535, 0x0635, 0x0735,
    0x0835, 0x0045, 0x0145, 0x0245, 0x0345, 0x0445, 0x0545, 0x0645,
    0x0745, 0x0845, 0x0055, 0x0155, 0x0255, 0x0355, 0x0455, 0x0555,
    0x0655, 0x0755, 0x0855, 0x0065, 0x0165, 0x0265, 0x0365, 0x0465,
    0x0565, 0x0665, 0x0765, 0x0865, 0x0075, 0x0175, 0x0275, 0x0375,
    0x0475, 0x0575, 0x0675, 0x0775, 0x0875, 0x0085, 0x0185, 0x0285,
    0x0385, 0x0485, 0x0585, 0x0685, 0x0785, 0x0885, 0x0006, 0x0106,
    0x0206, 0x0306, 0x0406, 0x0506, 0x0606, 0x0706, 0x0806, 0x0016,
    0x0116, 0x0216, 0x0316, 0x0416, 0x0516, 0x0616, 0x0716, 0x0816,
    0x0026, 0x0126, 0x0226, 0x0326, 0x0426, 0x0526, 0x0626, 0x0726,
    0x0826, 0x0036, 0x0136, 0x0236, 0x0336, 0x0436, 0x0536, 0x0636,
    0x0736, 0x0836, 0x0046, 0x0146, 0x0246, 0x0346, 0x0446, 0x0546,
    0x0646, 0x0746, 0x0846, 0x0056, 0x0156, 0x0256, 0x0356, 0x0456,
    0x0556, 0x0656, 0x0756, 0x0856, 0x0066, 0x0166, 0x0266, 0x0366,
    0x0466, 0x0566, 0x0666, 0x0766, 0x0866, 0x0076, 0x0176, 0x0276,
    0x0376, 0x0476, 0x0576, 0x0676, 0x0776, 0x0876, 0x0086, 0x0186,
    0x0286, 0x0386, 0x0486, 0x0586, 0x0686, 0x0786, 0x0886, 0x0007,
    0x0107, 0x0207, 0x0307, 0x0407, 0x0507, 0x0607, 0x0707, 0x0807,
    0x0017, 0x0117, 0x0217, 0x0317, 0x0417, 0x0517, 0x0617, 0x0717,
    0x0817, 0x0027, 0x0127, 0x0227, 0x0327, 0x0427, 0x0527, 0x0627,
    0x0727, 0x0827, 0x0037, 0x0137, 0x0237, 0x0337, 0x0437, 0x0537,
    0x0637, 0x0737, 0x0837, 0x0047, 0x0147, 0x0247, 0x0347, 0x0447,
    0x0547, 0x0647, 0x0747, 0x0847, 0x0057, 0x0157, 0x0257, 0x0357,
    0x0457, 0x0557, 0x0657, 0x0757, 0x0857, 0x0067, 0x0167, 0x0267,
    0x0367, 0x0467, 0x0567, 0x0667, 0x0767, 0x0867, 0x0077, 0x0177,
    0x0277, 0x0377, 0x0477, 0x0577, 0x0677, 0x0777, 0x0877, 0x0087,
    0x0187, 0x0287, 0x0387, 0x0487, 0x0587, 0x0687, 0x0787, 0x0887,
    0x0008, 0x0108, 0x0208, 0x0308, 0x0408, 0x0508, 0x0608, 0x0708,
    0x0808, 0x0018, 0x0118, 0x0218, 0x0318, 0x0418, 0x0518, 0x0618,
    0x0718, 0x0818, 0x0028, 0x0128, 0x0228, 0x0328, 0x0428, 0x0528,
    0x0628, 0x0728, 0x0828, 0x0038, 0x0138, 0x0238, 0x0338, 0x0438,
    0x0538, 0x0638, 0x0738, 0x0838, 0x0048, 0x0148, 0x0248, 0x0348,
    0x0448, 0x0548, 0x0648, 0x0748, 0x0848, 0x0058, 0x0158, 0x0258,
    0x0358, 0x0458, 0x0558, 0x0658, 0x0758, 0x0858, 0x0068, 0x0168,
    0x0268, 0x0368, 0x0468, 0x0568, 0x0668, 0x0768, 0x0868, 0x0078,
    0x0178, 0x0278, 0x0378, 0x0478, 0x0578, 0x0678, 0x0778, 0x0878,
    0x0088, 0x0188, 0x0288, 0x0388, 0x0488, 0x0588, 0x0688, 0x0788,
    0x0888, 0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600,
    0x0700, 0x0800, 0x0010, 0x0110, 0x0210, 0x0310, 0x0410, 0x0510,
    0x0610, 0x0710, 0x0810, 0x0020, 0x0120, 0x0220, 0x0320, 0x0420,
    0x0520, 0x0620, 0x0720, 0x0820, 0x0030, 0x0130, 0x0230, 0x0330,
    0x0430, 0x0530, 0x0630, 0x0730, 0x0830, 0x0040, 0x0140, 0x0240,
    0x0340, 0x0440, 0x0540, 0x0640, 0x0740, 0x0840, 0x0050, 0x0150,
    0x0250, 0x0350, 0x0450, 0x0550, 0x0650, 0x0750, 0x0850, 0x0060,
    0x0160, 0x0260, 0x0360, 0x0460, 0x0560, 0x0660, 0x0760, 0x0860,
    0x0070, 0x0170, 0x0270, 0x0370, 0x0470, 0x0570, 0x0670, 0x0770,
    0x0870, 0x0080, 0x0180, 0x0280, 0x0380, 0x0480, 0x0580, 0x0680,
    0x0780, 0x0880, 0x0001, 0x0101, 0x0201, 0x0301, 0x0401, 0x0501,
    0x0601, 0x0701, 0x0801, 0x0011, 0x0111, 0x0211, 0x0311, 0x0411,
    0x0511, 0x0611, 0x0711, 0x0811, 0x0021, 0x0121, 0x0221, 0x0321,
    0x0421, 0x0521, 0x0621, 0x0721, 0x0821, 0x0031, 0x0131, 0x0231,
    0x0331, 0x0431, 0x0531, 0x0631, 0x0731, 0x0831, 0x0041, 0x0141,
    0x0241, 0x0341, 0x0441, 0x0541, 0x0641, 0x0741, 0x0841, 0x0051,
    0x0151, 0x0251, 0x0351, 0x0451, 0x0551, 0x0651, 0x0751, 0x0851,
    0x0061, 0x0161, 0x0261, 0x0361, 0x0461, 0x0561, 0x0661, 0x0761,
    0x0861, 0x0071, 0x0171, 0x0271, 0x0371, 0x0471, 0x0571, 0x0671,
    0x0771, 0x0871, 0x0081, 0x0181, 0x0281, 0x0381, 0x0481, 0x0581,
    0x0681, 0x0781, 0x0881, 0x0002, 0x0102, 0x0202, 0x0302, 0x0402,
    0x0502, 0x0602, 0x0702, 0x0802, 0x0012, 0x0112, 0x0212, 0x0312,
    0x0412, 0x0512, 0x0612, 0x0712, 0x0812, 0x0022, 0x0122, 0x0222,
    0x0322, 0x0422, 0x0522, 0x0622, 0x0722, 0x0822, 0x0032, 0x0132,
    0x0232, 0x0332, 0x0432, 0x0532, 0x0632, 0x0732, 0x0832, 0x0042,
    0x0142, 0x0242, 0x0342, 0x0442, 0x0542, 0x0642, 0x0742, 0x0842,
    0x0052, 0x0152, 0x0252, 0x0352, 0x0452, 0x0552, 0x0652, 0x0752,
    0x0852, 0x0062, 0x0162, 0x0262, 0x0362, 0x0462, 0x0562, 0x0662,
    0x0762, 0x0862, 0x0072, 0x0172, 0x0272, 0x0372, 0x0472, 0x0572,
    0x0672, 0x0772, 0x0872, 0x0082, 0x0182, 0x0282, 0x0382, 0x0482,
    0x0582, 0x0682, 0x0782, 0x0882, 0x0003, 0x0103, 0x0203, 0x0303,
    0x0403, 0x0503, 0x0603, 0x0703, 0x0803, 0x0013, 0x0113, 0x0213,
    0x0313, 0x0413, 0x0513, 0x0613, 0x0713, 0x0813, 0x0023, 0x0123,
    0x0223, 0x0323, 0x0423, 0x0523, 0x0623, 0x0723, 0x0823, 0x0033,
    0x0133, 0x0233, 0x0333, 0x0433, 0x0533, 0x0633, 0x0733, 0x0833,
    0x0043, 0x0143, 0x0243, 0x0343, 0x0443, 0x0543, 0x0643, 0x0743,
    0x0843, 0x0053, 0x0153, 0x0253, 0x0353, 0x0453, 0x0553, 0x0653
};

const static short mp3dec_degroup_5[] = {
    0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0010, 0x0110, 0x0210,
    0x0310, 0x0410, 0x0020, 0x0120, 0x0220, 0x0320, 0x0420, 0x0030,
    0x0130, 0x0230, 0x0330, 0x0430, 0x0040, 0x0140, 0x0240, 0x0340,
    0x0440, 0x0001, 0x0101, 0x0201, 0x0301, 0x0401, 0x0011, 0x0111,
    0x0211, 0x0311, 0x0411, 0x0021, 0x0121, 0x0221, 0x0321, 0x0421,
    0x0031, 0x0131, 0x0231, 0x0331, 0x0431, 0x0041, 0x0141, 0x0241,
    0x0341, 0x0441, 0x0002, 0x0102, 0x0202, 0x0302, 0x0402, 0x0012,
    0x0112, 0x0212, 0x0312, 0x0412, 0x0022, 0x0122, 0x0222, 0x0322,
    0x0422, 0x0032, 0x0132, 0x0232, 0x0332, 0x0432, 0x0042, 0x0142,
    0x0242, 0x0342, 0x0442, 0x0003, 0x0103, 0x0203, 0x0303, 0x0403,
    0x0013, 0x0113, 0x0213, 0x0313, 0x0413, 0x0023, 0x0123, 0x0223,
    0x0323, 0x0423, 0x0033, 0x0133, 0x0233, 0x0333, 0x0433, 0x0043,
    0x0143, 0x0243, 0x0343, 0x0443, 0x0004, 0x0104, 0x0204, 0x0304,
    0x0404, 0x0014, 0x0114, 0x0214, 0x0314, 0x0414, 0x0024, 0x0124,
    0x0224, 0x0324, 0x0424, 0x0034, 0x0134, 0x0234, 0x0334, 0x0434,
    0x0044, 0x0144, 0x0244, 0x0344, 0x0444, 0x0000, 0x0100, 0x0200
};

const static short mp3dec_degroup_3[] = {
    0x0000, 0x0100, 0x0200, 0x0010, 0x0110, 0x0210, 0x0020, 0x0120,
    0x0220, 0x0001, 0x0101, 0x0201, 0x0011, 0x0111, 0x0211, 0x0021,
    0x0121, 0x0221, 0x0002, 0x0102, 0x0202, 0x0012, 0x0112, 0x0212,
    0x0022, 0x0122, 0x0222, 0x0000, 0x0100, 0x0200, 0x0010, 0x0110
};

const short *mp3dec_degroup[] = {
    NULL, NULL, NULL, NULL, NULL, mp3dec_degroup_3,
    NULL, mp3dec_degroup_5, NULL, NULL, mp3dec_degroup_9
};

#ifdef __cplusplus
}
#endif
