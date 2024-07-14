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

#if !defined(_UNICODE)
#define _UNICODE
#endif

#include  "../strlnx.h"
#include  "../strlnx.h" // include guard test
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TEST(name) static void test_##name()
#define DO_TEST(name) printf("Starting %s...\n", #name); test_##name(); printf("...%s passed\n\n", #name)

TEST(strlncat_normal_concatenation) {
    strlnx_char_t dest[20] = STRLNX_STR("Hello, ");
    size_t result = strlncat(dest, STRLNX_STR("world!"), 20, 10);
    assert(wcscmp(dest, STRLNX_STR("Hello, world!")) == 0);
    assert(result == 13);
}

TEST(strlncat_limited_copy) {
    strlnx_char_t dest[20] = STRLNX_STR("Hello, ");
    size_t result = strlncat(dest, STRLNX_STR("world!"), 20, 3);
    assert(wcscmp(dest, STRLNX_STR("Hello, wor")) == 0);
    assert(result == 10);
}

TEST(strlncat_truncation) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello, ");
    // wchar_t *p = dest;
    size_t result = strlncat(dest, STRLNX_STR("world!"), 10, 10);
    // p[1] = L'e';
    assert(wcscmp(dest, STRLNX_STR("Hello, wo")) == 0);
    assert(result == 13);
}

TEST(strlncat_empty_destination) {
    strlnx_char_t dest[10] = STRLNX_STR("");
    size_t result = strlncat(dest, STRLNX_STR("Hello"), 10, 5);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 5);
}

TEST(strlncat_empty_source) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello");
    size_t result = strlncat(dest, STRLNX_STR(""), 10, 5);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 5);
}

TEST(strlncat_zero_maxcopy) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello");
    size_t result = strlncat(dest, STRLNX_STR("world"), 10, 0);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 5);
}

TEST(strlncat_full_buffer) {
    strlnx_char_t dest[6] = STRLNX_STR("Hello");
    size_t result = strlncat(dest, STRLNX_STR("world"), 6, 5);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 10);
}


TEST(strlncpy_normal_copy) {
    strlnx_char_t dest[20];
    size_t result = strlncpy(dest, STRLNX_STR("Hello, world!"), 20, 20);
    assert(wcscmp(dest, STRLNX_STR("Hello, world!")) == 0);
    assert(result == 13);
}

TEST(strlncpy_limited_copy) {
    strlnx_char_t dest[20];
    size_t result = strlncpy(dest, STRLNX_STR("Hello, world!"), 20, 5);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 5);
}

TEST(strlncpy_truncation) {
    strlnx_char_t dest[10];
    size_t result = strlncpy(dest, STRLNX_STR("Hello, world!"), 10, 20);
    assert(wcscmp(dest, STRLNX_STR("Hello, wo")) == 0);
    assert(result == 13);
}

TEST(strlncpy_empty_source) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello");
    size_t result = strlncpy(dest, STRLNX_STR(""), 10, 5);
    assert(wcscmp(dest, STRLNX_STR("")) == 0);
    assert(result == 0);
}

TEST(strlncpy_zero_maxcopy) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello");
    size_t result = strlncpy(dest, STRLNX_STR("world"), 10, 0);
    assert(wcscmp(dest, STRLNX_STR("")) == 0);
    assert(result == 0);
}

TEST(strlncpy_zero_dstsize) {
    strlnx_char_t dest[10] = STRLNX_STR("Hello");
    size_t result = strlncpy(dest, STRLNX_STR("world"), 0, 5);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);  // dest should remain unchanged
    assert(result == 5);
}

TEST(strlncpy_maxcopy_larger_than_src) {
    strlnx_char_t dest[20];
    size_t result = strlncpy(dest, STRLNX_STR("Hello"), 20, 10);
    assert(wcscmp(dest, STRLNX_STR("Hello")) == 0);
    assert(result == 5);
}

void run_wchar_tests() {
    printf("Testing strlncat with 'wchar_t'\n");
    DO_TEST(strlncat_normal_concatenation);
    DO_TEST(strlncat_limited_copy);
    DO_TEST(strlncat_truncation);
    DO_TEST(strlncat_empty_destination);
    DO_TEST(strlncat_empty_source);
    DO_TEST(strlncat_zero_maxcopy);
    DO_TEST(strlncat_full_buffer);
    printf("Testing strlncpy with 'wchar_t'\n");
    DO_TEST(strlncpy_normal_copy);
    DO_TEST(strlncpy_limited_copy);
    DO_TEST(strlncpy_truncation);
    DO_TEST(strlncpy_empty_source);
    DO_TEST(strlncpy_zero_maxcopy);
    DO_TEST(strlncpy_zero_dstsize);
    DO_TEST(strlncpy_maxcopy_larger_than_src);
    printf("Tests completed\n");
}

int main() {
  run_wchar_tests();
  return 0;
}
