#include "test/hash.h"
#include "warble/hash.h"

void test_hash(TestContext *ctx) {
	test(ctx, "hash");
	// expected == actual; reversed so they line up.
	EXPECT(ctx, 0x811C'9DC5 == hash_fnv1a32(slice_from_cstr("")));
	EXPECT(ctx, 0xE40C'292C == hash_fnv1a32(slice_from_cstr("a")));
	EXPECT(ctx, 0x48D4'443E == hash_fnv1a32(slice_from_cstr("fnv1a32")));
}
