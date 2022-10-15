//
// Created by ivanbrekman on 06.10.2021.
//

#include <ctime>
#include <cctype>
#include <cmath>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "baselib.hpp"

//! Function checks validity of pointer
//! \param  ptr checking pointer
//! \return     0 if all is good, else != 0
int isbadreadptr(const void* ptr) {
    int nullfd = open("/dev/random", O_WRONLY);

    int old_errno = errno;
    errno = 0;
    
    int res = write(nullfd, ptr, 1);
    close(nullfd);

    int result = errno;
    errno = old_errno;

    return result;
}

//! Function execute safe calloc call
//! \param __nmemb amount of elements
//! \param __size  size of 1 element
//! \return        void* ptr to dynamic memory
//! \note if calloc return invalid ptr function will throw Assertion error,
//!       or if NDEBUG defined print warning and return NULL
void* calloc_s(size_t __nmemb, size_t __size) {
    void* ptr = calloc(__nmemb, __size);

    ASSERT_IF(VALID_PTR(ptr), "Cant allocate memory", NULL);

    return ptr;
}

//! Function opens file
//! \param filename path to file to open (absolute or relative)
//! \param mode     mode with which open file
//! \return         pointer to opened file (FILE*)
//! \note call assert if function cannot open file on the path filename
FILE* openFile(const char* filename, const char mode[]) {
    ASSERT_IF(VALID_PTR(filename), "Invalid filename ptr", NULL);

    FILE* file = fopen(filename, mode);

    ASSERT_IF(VALID_PTR(file), "Can`t open file (not valid ptr)", NULL);

    return file;
}

//! Function defines size of file
//! \param filename path to file (absolute or relative)
//! \return         size of file (in bytes)
int sizeFile(const char* filename) {
    ASSERT_IF(VALID_PTR(filename), "Invalid filename ptr", -1);

    struct stat buff = {};
    stat(filename, &buff);

    return (int)buff.st_size;
}

//! Function closes file
//! \param file ptr to FILE object
//! \return     0 if success, else EOF
int closeFile(FILE* file) {
    ASSERT_IF(VALID_PTR(file), "Invalid file ptr", EOF);

    int result = fclose(file);

    return result;
}

//! Function gets raw text from file
//! \param filename path to file to open (absolute or relative)
//! \return         ptr to readed string
char* get_raw_text(const char* filename) {
    ASSERT_IF(VALID_PTR(filename), "Invalid filename ptr", NULL);

    FILE* file = openFile(filename, "r");
    int f_size = sizeFile(filename);

    char* data = NEW_PTR(char, f_size + 1);
    int  bytes = (int)fread(data, sizeof(char), f_size, file);

    ASSERT_IF(bytes == f_size, "Error in reading file", NULL);

    closeFile(file);
    return data;
}


//! Function clears string from space symbols
//! \param string ptr to string
//! \return       ptr to cleared string (same with string)
char* deleteSpaces(char* string) {
    ASSERT_IF(VALID_PTR(string), "Invalid string ptr", NULL);

    char* new_ptr = &string[0];
    char* old_ptr = &string[0];

    while (*old_ptr != '\0') {
        if (!isspace(*old_ptr)) {
            *new_ptr = *old_ptr;
            new_ptr++;
        }
        old_ptr++;
    }
    *new_ptr = '\0';

    return string;
}

//! Function writes current date and time to calendar_date
//! \param calendar_date ptr to string, where current date and time will bw written
//! \return              ptr to calendar_date
char* datetime(char* calendar_date) {
    ASSERT_IF(VALID_PTR(calendar_date), "Invalid calendar_date ptr", NULL);

    const time_t timer = time(NULL);
    tm* calendar = localtime(&timer);
    ASSERT_IF(VALID_PTR(calendar), "Invalid calendar ptr", NULL);

    strftime(calendar_date, MAX_FILEPATH_SIZE, "%d.%m.%Y %H:%M:%S, %A", calendar);

    return calendar_date;
}

//! Function compare 2 double numbers
//! \param number1 - first number
//! \param number2 - second number
//! \return        - (number1 <  number2) -> negative number
//!                  (number1 == number2) -> 0
//!                  (number1 >  number2) -> positive number
int cmpDouble(double number1, double number2) {
    if (fabs(number1 - number2) < FLOAT_COMPARE_PRESICION) return  0;
    if ((number1 - number2) >  FLOAT_COMPARE_PRESICION)    return  1;
    if ((number1 - number2) < -FLOAT_COMPARE_PRESICION)    return -1;

    ASSERT_IF(0, "num1 !< num2, num1 !> num2, num1 != num2. WTF?", -15);
}

//! Function checks double number for integer
//! \param number checking number
//! \return       1 if number % 1 == 0, else 0
int isInteger(double number) {
    return (number - (int)number) < FLOAT_COMPARE_PRESICION;
}

//! Function count digits in number in radix number system
//! \param number number
//! \param radix  number system (default 10)
//! \return       number of digits
int digitsNumber(int number, int radix) {
    ASSERT_IF(radix > 1, "Incorrect radix value", -1);

    if (number == 0) return 1;

    int digits = number < 0;
        number = abs(number);
    while (number > 0) {
        number /= radix;
        digits++;
    }

    return digits;
}

//! Function extracts bit from number
//! \param number number
//! \param bit    number of bit
//! \return       bit-th bit of number
int extractBit(int number, int bit) {
    ASSERT_IF(bit >= 0, "Incorrect bit number", -1);

    return (number >> bit) & 1;
}

//! Function checks if string can be int
//! \param string checking string
//! \return       1 if string can be int, else 0
int isNumber(char* string) {
    ASSERT_IF(VALID_PTR(string), "Invalid string ptr", 1);

    int res = atoi(string);

    if (res == 0) {
        return string[0] == '0' && string[1] == '\0';
    }
    return 1;
}

//! Function convert 4-bytes number to bin view
//! \param number converting number
//! \return       converted to bin view number as string
char* bin4(int number) {
    char* bits = NEW_PTR(char, 4 * 8);
    int real_bits = 0;

    while (number > 0) {
        bits[real_bits++] = (char)('0' + (number % 2));
        number /= 2;
    }

    for (int i = 0; i < real_bits / 2; i++) {
        char tmp = bits[i];
        bits[i] = bits[real_bits - 1 - i];
        bits[real_bits - 1 - i] = tmp;
    }

    bits[real_bits] = '\0';
    return bits;
}

//! Function convert number to string
//! \param number converting number
//! \return       converted number
char* toString(int number) {
    if (number == 0) {
        char* str_num = NEW_PTR(char, 1 + 1);
        str_num[0] = '0';
        str_num[1] = '\0';
        return str_num;
    }

    int shift = 0;
    if (number < 0) {
        shift = 1;
        number = -number;
    }

    int d_num = digitsNumber(number, 10);
    char* str_num = NEW_PTR(char, d_num + shift + 1);

    for (int i = d_num - 1; number > 0; i--) {
        str_num[i + shift] = (char)('0' + (number % 10));
        number /= 10;
    }
    if (shift) str_num[0] = '-';
    str_num[d_num + shift] = '\0';

    return str_num;
}
