/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
    /*
    &的一个作用是全为1则1，|中类似的作用是全为0则0
    所以先把x,y都取反，让全为1的地方全为0，通过|得出全为0的地方，再取反就是全为1的地方
    即得到x&y的结果
    */
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
    /*
    全为1的和全为0的都去掉就只有^的情况了
    x&y把全1的变成1，取反以后只有 1）同时包含0和1  2）全为0 为1
    ~x&~y把全0的变成0，取反以后只有 1）同时包含0和1  2）全为1 为1
    上面两种情况在取&后，只有 同时包含0和1 情况为1
    也就是^的情况
    */
}
/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) 
    {
        if (!y) 
        {
            return 1;
        }
        else return 0;
    }
    if (!y)
    {
        return 0;
    }
    return !(((x >>31)^(y>>31)));
    /*
    1）x和y最少一个为0
    都为0 返回1
    只有一个为0 返回0
    2）x和y都不为0
    int类型有符号，比较最高位是否相同就可以了
    只要用到最高位 所以右移31位
    由于^的返回的0和1与题目要求相反，所以取反就得到答案了
    */
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int x;

    x = (v >> 16) > 0;
    r = x << 4;
    v = v >> r;

    x = (v >> 8) > 0;
    x = x << 3;
    r = r | x;
    v = v >> x;

    x = (v >> 4) > 0;
    x = x << 2;
    r = r | x;
    v = v >> x;

    x = (v >> 2) > 0;
    x = x << 1;
    r = r | x;
    v = v >> x;

    x = (v >> 1) > 0;
    r = r | x;

    return r;
    /*
    全是0只有一个1
    类似二分查找的方法
    每次判断是在前一半还是后一半
    找到就通过平移1的位置加上相应的数
    每层的 (x<<k) 只算一次，先存进 x 里再复用，符号数压到 22 个（上限 25）
    */
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n1=n<<3;
    int m1=m<<3;
    int diff=((x>>n1)^(x>>m1))&0xFF;
    x=x^(diff<<n1);
    x=x^(diff<<m1);
    return x;
    /*
    三次抑或可以完成交换操作
    0和一个数据抑或还是这个数据本身

    这个题目中需要交换的数据位于不同的位置
    先移动到最后八位（位置相同）
    然后在相同的位置进行抑或操作
    再平移到需要交换的位置抑或操作，其他地方为0不会改变原来的值
    */

}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v=((v&0xAAAAAAAA)>>1)|((v&0x55555555)<<1);
    v=((v&0xCCCCCCCC)>>2)|((v&0x33333333)<<2);
    v=((v&0xF0F0F0F0)>>4)|((v&0x0F0F0F0F)<<4);
    v=((v&0xFF00FF00)>>8)|((v&0x00FF00FF)<<8);
    v=((v&0xFFFF0000)>>16)|((v&0x0000FFFF)<<16);
    return v;
    /*
    只有两个数字交换位置就得到答案
    四个时先奇偶位交换再两个两个交换
    归纳得出32位解法
    取出某位置的1按照上述方法计算
    */
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
    /*
    算术右移会把符号位补满前面，所以要造一个掩码把多出来的高位抹掉
    (1<<31)>>n 是符号位向右扩展后的样子，再<<1 就比需要抹掉的位数多一位，取反就是掩码
    这样不需要 unsigned，也能得到逻辑右移的结果
    */
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y=0;
    int t=0;
    y=!(~(x>>16));
    t+=(y<<4);
    x=x<<(y<<4);
    y=!(~(x>>24));
    t+=(y<<3);
    x=x<<(y<<3);
    y=!(~(x>>28));
    t+=(y<<2);
    x=x<<(y<<2);
    y=!(~(x>>30));
    t+=(y<<1);
    x=x<<(y<<1);
    y=!(~(x>>31));
    t+=y;
    x=x<<y;
    y=!(~(x>>31));
    t+=y;
    return t;
    /*
    要先有一个1才能通过移位来计算，所以通过！构造出1
    二分查找，先判断前16个是否全为1
    全为1左移16位，剩下16个再二分，先找前8个，4个…… 
    全为1时！得到0没有产生1不好算所以先取~
    */
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;
    unsigned u = x;
    unsigned t;
    unsigned frac = 0;
    unsigned mask;
    unsigned rem;
    unsigned half;
    unsigned r = 0;
    int e = 0;

    if (sign) {
        u = -u;
    }
    if (u == 0) {
        return 0;
    }

    t = u;
    while (t >> 1) {
        t = t >> 1;
        e = e + 1;
    }

    if (e < 24) {
        frac = (u << (23 - e)) & 0x7FFFFF;
    } else {
        mask = (1 << (e - 23)) - 1;
        frac = (u >> (e - 23)) & 0x7FFFFF;
        rem = u & mask;
        half = (mask >> 1) + 1;
        if (rem > half) {
            r = 1;
        }
        if (rem == half) {
            if (frac & 1) {
                r = 1;
            }
        }
        frac = frac + r;
        if (frac >> 23) {
            frac = 0;
            e = e + 1;
        }
    }
    return sign | ((e + 127) << 23) | frac;
    /*
    先提取首位符号
    绝对值用 while 一位一位右移，求出最高位的位置 e（比写死 5 次 if 省符号）
    位数小于 24 位时尾数直接左移补齐，用掩码保留 23 位
    位数大于等于 24 位时，先取出被截掉的低位 rem，与半个单位比较做向偶数舍入：
      大于一半进位；正好等于一半且尾数末位是 1 时进位（保证末位为偶数）
      舍入进位可能让有效数从 1.xxx 变成 2.0，这时要把尾数清 0、指数加 1
    最后符号、指数、尾数三部分 | 起来就是结果
    */
}
/*
先提取首位符号
然后求exp的值，二分查找
对于尾数小于23（24）位的直接用掩码保留
对于位数大于24位的掩码保留24位以后的部分并向偶数舍入
最后三个部分|运算得到结果
*/

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign=uf&0x80000000;
    unsigned exp=(uf>>23)&0xFF;

    if (exp == 255) {
        return uf;
    }

    if (exp == 0) {
        return sign|((uf&0x7FFFFFFF)<<1);
    }

    exp++;
    return sign|(exp<<23)|(uf&0x7FFFFF);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exp = (uf2 >> 20) & 0x7FF;
    int E;
    int hi;
    int ans;

    if (exp >= 0x7FF) {
        return 0x80000000;
    }
    if (exp <= 0) {
        return 0;
    }
    E = exp - 1023;
    if (E < 0) {
        return 0;
    }
    if (E >= 31) {
        return 0x80000000;
    }

    hi = (1 << 20) | (uf2 & 0xFFFFF);
    if (E <= 20) {
        ans = hi >> (20 - E);
    } else {
        ans = (hi << (E - 20)) | (uf1 >> (52 - E));
    }
    if (sign) {
        ans = -ans;
    }
    return ans;
    /*
    首位是符号，后面 11 位是 2 的次方（指数），再后面 52 位尾数（分成 uf2 的低 20 位和 uf1 的 32 位）
    指数全 1 是 NaN/无穷 -> 0x80000000；指数为 0 或 E<0 说明太小 -> 0；E>=31 超出 int 范围 -> 0x80000000
    把 uf2 低 20 位补上隐含的 1 得到 21 位有效数 hi
    E<=20 时整数部分全在 hi 里，直接 hi>>(20-E)
    E>20 时还要接上 uf1 的高位，所以 (hi<<(E-20))|(uf1>>(52-E))
    向 0 取整直接截断低位即可，最后按符号取负
    （没有用 64 位类型也没有强制转换，直接用两个 32 位半字拼）
    */
}
/*
首位为符号，后面11位表示2的次方
提取出尾数，按照2的次方保留位数
由于向0取整直接int转换
*/
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
if(x>=128){
return 0x7F800000;
}
if(x<-149){
return 0;
}
if(x<-126){
return 1<<(x+149);
}
return (x+127)<<23;
}
/*
128以上过大
-149以下过小
-149到-126非规格化
-126到127可以规格化
*/