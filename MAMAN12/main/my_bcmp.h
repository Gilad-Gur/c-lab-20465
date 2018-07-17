/*
NAME
       my_bcmp - compare memory areas

SYNOPSIS
       int my_bcmp(const void *b1, const void *b2, size_t len);

DESCRIPTION
       The  my_bcmp() function compares the first len bytes (each interpreted as
       unsigned char) of the memory areas b1 and b2.

RETURN VALUE
       The my_bcmp() function returns an integer less than, equal to, or
       greater than zero if the first n bytes of b1 is found, respectively, to
       be less than, to match, or be greater than the first n bytes of b2.

       For a nonzero return value, the sign is determined by the sign of the
       difference between the first pair of bytes (interpreted as unsigned
       char) that differ in b1 and b2.

       If len is zero, the return value is zero.
*/

int my_bcmp(const void *b1, const void *b2, size_t len);
