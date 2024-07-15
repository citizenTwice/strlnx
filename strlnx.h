/*

MIT License

Copyright (c) 2024 Luigi Galli

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*

strlncat and strlncpy 
For most platform/targets

*/

#ifndef STRLNX_H
#define STRLNX_H

#if defined(_UNICODE)

#define strlnx_char_t wchar_t
#if defined(__WATCOMC__)
#define __STDC_WANT_LIB_EXT1__  1
#define strlnx_strlen wcsnlen_s
#else
#define strlnx_strlen wcsnlen
#endif
#include <string.h>
#include <wchar.h>
#define STRLNX_STR(x) L##x

#else  // not Unicode

#define strlnx_char_t char
#if defined(__WATCOMC__)
#define __STDC_WANT_LIB_EXT1__  1
#define strlnx_strlen strnlen_s
#else
#define strlnx_strlen strnlen
#endif
#include <string.h>
#define STRLNX_STR(x) x
#endif

/*
Concatenates up to max_copy chars of src to dst, respecting the size limit of dst.
[ dst always gets zero-terminated unless its size is zero ]
 -> dst      = pointer to destination buffer
 -> dst_size = size *in characters* of dst
 -> src      = pointer to source string
 -> max_copy = max number of characters to copy
 -> return value = srclen(dst) + min(srclen(s), max_copy)
*/
static size_t strlncat(strlnx_char_t *dst, const strlnx_char_t *src, size_t dst_size, size_t max_copy) {
 
    size_t dst_len = strlnx_strlen(dst, dst_size);
    size_t src_len = strlnx_strlen(src, max_copy);
    size_t would_copy = (src_len < max_copy) ? src_len : max_copy;
    size_t space_left = dst_size - dst_len - 1;
    size_t to_copy = would_copy;
        
    if (dst_size <= dst_len + 1) {
        return dst_len + would_copy;
    }
    
    if (to_copy > space_left) {
        to_copy = space_left;
    }
    
    memmove(dst + dst_len, src, to_copy * sizeof(strlnx_char_t));
    dst[dst_len + to_copy] = 0;
    
    return dst_len + would_copy;
}

/*
Copies up to max_copy chars of src to dst, respecting the size limit of dst.
[ dst always gets zero-terminated unless its size is zero ]
 -> dst      = pointer to destination buffer
 -> dst_size = size *in characters* of dst
 -> src      = pointer to source string
 -> max_copy = max number of characters to copy
 -> return value = min(srclen(s), max_copy)
*/
static size_t strlncpy(strlnx_char_t *dst, const strlnx_char_t *src, size_t dst_size, size_t max_copy) {
  
    size_t src_len = strlnx_strlen(src, max_copy);
    size_t would_copy = (src_len < max_copy) ? src_len : max_copy;
    size_t to_copy = would_copy;      
    
    if (dst_size == 0) {
      return would_copy;
    } else if (dst_size < (to_copy + 1)) {
        to_copy = dst_size - 1;
    }

    memmove(dst, src, to_copy * sizeof(strlnx_char_t));
    dst[to_copy] = 0;
        
    return would_copy;
}

#endif
