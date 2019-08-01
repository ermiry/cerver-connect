#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <sys/types.h>
#include <regex.h>

#include "cengine/types/string.h"

#include "cengine/utils/utils.h"
#include "cengine/utils/log.h"

const regex_t ip_regex;
const String *ip_regex_pattern = NULL;

void print_regerror (int errcode, size_t length, regex_t *compiled) {

    char buffer[length];
    (void) regerror (errcode, compiled, buffer, length);
    cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, c_string_create ("Regex match failed: %s", buffer));

}

// get the username regex pattern from config
static int load_ip_validation (void) {

    FILE *ip_config = NULL;
    char buffer[2048];
    ip_config = fopen ("./config/ip-validation.txt", "r");
    if (ip_config) {
        fgets (buffer, 2048, ip_config);
        // printf ("\n%s\n", ip_regex_pattern);
        ip_regex_pattern = str_new (buffer);
        fclose (ip_config);

        int result = regcomp ((regex_t *) &ip_regex, ip_regex_pattern->str, REG_EXTENDED);
        if (!result) return 0;
        else {
            cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, "Failed to compile ip regex!");
            size_t length = regerror (result, (regex_t *) &ip_regex, NULL, 0);
            print_regerror (result, length, (regex_t *) &ip_regex);
        }
    }

    else cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, "Failed to open ip validation file!");

    return 1;

}

// load validation regex from files
int validation_init (void) {

    int errors = 0;

    errors = load_ip_validation ();

    return errors;

}

void validation_end (void) {

    str_delete ((String *) ip_regex_pattern);

}

// check for valid value using the regex the regex
bool validation_check_value (const regex_t regex, const char *value) {

    int result;
    bool retval = false;

    if (value) {
        result = regexec (&regex, value, 0, NULL, 0);
        if (!result) retval = true;

        else if (result == REG_NOMATCH) {
            #ifdef CERVER_DEBUG
            cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, 
                "validation_check_value () - not a valid value!");
            #endif
        } 

        else {
            // the function returned an error
            size_t length = regerror (result, (regex_t *) &regex, NULL, 0);
            print_regerror (result, length, (regex_t *) &regex);  
        }
    }

	return retval;

}