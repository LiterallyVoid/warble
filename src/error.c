#include "error.h"

const char *error_to_string(Error self) {
	switch (self) {
	case ERR_SUCCESS:	return "(success)";
	case ERR_UNKNOWN:	return "unknown error";
	case ERR_OUT_OF_MEMORY:	return "out of memory";
	case ERR_NO_SPACE:	return "no space left";
	case ERR_NOT_FOUND:	return "not found";
	case ERR_PARSE_FAILED:	return "parse failed";
	case ERR_HTTP_NOT_FOUND:	return "http not found";
	}

	if (self > 0) {
		return "(unrecognized success value)";
	}

	return "(unrecognized error)";
}
