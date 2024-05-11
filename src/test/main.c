#include "warble/test.h"

#include "test/arraylist.h"
#include "test/buffer.h"
#include "test/hash.h"
#include "test/hashmap.h"
#include "test/slice.h"

int main(int argc, char **argv) {
	TestContext ctx;

	test_context_init(&ctx);

	test_arraylist(&ctx);
	test_buffer(&ctx);
	test_hashmap(&ctx);
	test_hash(&ctx);
	test_slice(&ctx);

	test_context_report(&ctx);
}
