#include "warble/test.h"

#include "arraylist.h"
#include "buffer.h"
#include "hashmap.h"
#include "slice.h"

int main(int argc, char **argv) {
	TestContext ctx;

	test_context_init(&ctx);

	test_arraylist(&ctx);
	test_buffer(&ctx);
	test_hashmap(&ctx);
	test_slice(&ctx);

	test_context_report(&ctx);
}
