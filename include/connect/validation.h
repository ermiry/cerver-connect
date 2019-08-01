#ifndef _ERMIRY_VALIDATION_H_
#define _ERMIRY_VALIDATION_H_

#include <stdbool.h>

#include <sys/types.h>
#include <regex.h>

#include "cengine/types/string.h"

extern const regex_t ip_regex;
extern const String *ip_regex_pattern;

extern void print_regerror (int errcode, size_t length, regex_t *compiled);

// load validation regex from files
extern int validation_init (void);

extern void validation_end (void);

// check for valid value using the regex the regex
extern bool validation_check_value (const regex_t regex, const char *value);

#endif