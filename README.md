# strlnx.h
Ready-to-use strlncat &amp; strlncpy header lib with Unicode/wchar_t support.
Feel free to grab these.

### Example
```
  {
    char buf[32] = "abc or perhaps ";
    strlncat(buf, "xyzXYZ", 32, 3);
    assert(strcmp(buf,"abc or perhaps xyz") == 0);
  }
  {
    char buf[10] = "b";
    strlncat(buf, "zzzzzzzzzzzzzzzzzzzz", 10, 12);
    assert(strcmp(buf,"bzzzzzzzz") == 0);
  }
```


#### License
MIT License

#### Feedback
Bugs/Suggestions/Comments/Feedback to:
Email: feedback@THLG.NL
