#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int vasprintf (char **string_ptr, const char *format, va_list args)
{
	va_list copy;
	va_copy(copy, args);

	int nb_chars = vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	if (nb_chars < 0)
		return nb_chars;

// we use another pointer in case *string_ptr is also used as a %s argument
// otherwise, there would be overlap
	char *string = malloc(nb_chars + 1);

	if (string == NULL)
		return -1;

	int retval = vsprintf(string, format, args);

	if (retval < 0) {
		free(string);
		return retval;
	}

	*string_ptr = string;
	return retval;
}

int asprintf (char **string_ptr, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	int retval = vasprintf(string_ptr, format, args);
	va_end(args);

	return retval;
}
