#include <cstdio>
#include <cstring>
#include <string>
#include <climits>
#include <stdexcept>
#include <memory>
#include "my_printf.h"

void my_printf(const char* format, void* buffer) {
    void* p_last = buffer;

    const char* format_pos = format;
    int length = 0;

    for (int i = 0; format[i] != '\0'; ++i) {
        if (format[i] != '%') {
            ++length;
        }
        else {
           fwrite((const void*) format_pos, length, sizeof(char),  stdout);
           format_pos += length + 2;
           length = 0;

           ++i;
           
           //The following line is to deal with a pitfall: std::align would return the next pointer if the pointer is already aligned
           p_last = (char*)p_last - 1; 

           if (format[i] == '\0') {
              putchar('%');
              break;
           }
           else if (format[i] == 'd') {
              if (!__realign(p_last, int))
                 throw std::runtime_error("Buffer overloaded");    

              int num = *(int*)p_last;
              fputs(std::to_string(num).c_str(), stdout);

              p_last = (int*)p_last + 1;
           }
           else if (format[i] == 'f') {
              if (!__realign(p_last, double))
                 throw std::runtime_error("Buffer overloaded");

              double num = *(double*)p_last;
              fputs(std::to_string(num).c_str(), stdout);

              p_last = (double*)p_last + 1;
           }
           else if (format[i] == 's') {
              if (!__realign(p_last, const char*))
                 throw std::runtime_error("Buffer overloaded");
              const char* s = *(const char**)p_last;
              fputs(s, stdout);

              p_last = (char**)p_last + 1;
           }
           else if (format[i] == 'p') {
              if (!__realign(p_last, const void*))
                 throw std::runtime_error("Buffer overloaded");

              const void* p = *(const void**)p_last;
              
              long long num = (std::size_t)p;

              fputs(std::to_string(num).c_str(), stdout); 
           }
           else {
              throw std::runtime_error("Unknown format specifier");
           }
        }
    }
    fwrite(format_pos, length, sizeof(char), stdout);
    fflush(stdout);
}
