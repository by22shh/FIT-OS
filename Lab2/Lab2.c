#include <sys/types.h>
 #include <stdio.h>
 #include <time.h>
 #include <stdlib.h>

 extern char *tzname[];
 
 int main() {
    const char *name = "TZ";
    const char *value = "America/Tijuana";

    time_t now;
    /*Time structure, contains values of date and time in separate fields(9 fields).*/
    struct tm *sp;
    
    /*adds the variable name to the environment with
       the value value, if name does not already exist.  If name does exist
       in the environment, then its value is changed to value if overwrite
       is nonzero.*/
    setenv(name, value, 1);

    /*The time () function reads the current clock CLOCK_REALTIME (system clock) in seconds. 
      The value of the system clock is the time in seconds since 0:00 on January 1, 1970.
      The current time read is returned by the function and placed at the address specified in the argument.*/
    time(&now);

    /*ctime converts a value of type time_t to a C-string that contains the date and time in a human-readable format.*/
    printf("%s", ctime(&now));

    sp = localtime(&now);

    /*The year output is 119, the number of years past 1900.*/
    printf("%d/%d/%02d %d:%02d %s\n", sp->tm_mon + 1, sp->tm_mday, sp->tm_year, sp->tm_hour,
                                                                sp->tm_min, tzname[sp->tm_isdst]);
    return 0;
 }
