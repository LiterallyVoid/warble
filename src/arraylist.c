#include "warble/arraylist.h"

#include "warble/util.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void arraylist_init(ArrayList *self, size_t item_size) {
	*self = (ArrayList) {
		.item_size = item_size,

		.items = NULL,
		.len = 0,
		.cap = 0,
	};
}

void arraylist_deinit(ArrayList *self) {
	free(self->items);

	set_undefined(self, sizeof(*self));
}

static void *arraylist_get_unchecked(ArrayList *self, size_t index) {
	return (char*) self->items + self->item_size * index;
}

void *arraylist_get(ArrayList *self, size_t index) {
	assert(index >= 0 && index < self->len);

	return arraylist_get_unchecked(self, index);
}

Error arraylist_reserve_total(ArrayList *self, size_t total) {
	if (self->cap >= total) return ERR_SUCCESS;

	size_t new_cap = next_power_of_two(total);
	if (new_cap < 8) new_cap = 8;

	void *new_items = realloc(self->items, self->item_size * new_cap);
	if (new_items == NULL) return ERR_OUT_OF_MEMORY;

	self->items = new_items;
	self->cap = new_cap;

	return ERR_SUCCESS;
}

Error arraylist_reserve_additional(ArrayList *self, size_t additional) {
	size_t total = self->len + additional;

	// Unsigned integer overflow is defined to wrap, so this isn't undefined behavior.
	assert(total >= self->len);

	arraylist_reserve_total(self, total);

	return ERR_SUCCESS;
}

Error arraylist_append(ArrayList *self, void *item) {
	return arraylist_splice(self, self->len, 0, item, 1);
}

void arraylist_append_assume_capacity(ArrayList *self, void *item) {
	arraylist_splice_assume_capacity(self, self->len, 0, item, 1);
}

Error arraylist_splice(
	ArrayList *self,
	size_t index, size_t count,
	void *new_items,
	size_t new_items_count
) {
	if (new_items_count > count) {
		size_t additional = new_items_count - count;

		// Make sure there's no overflow.
		assert(self->len + additional >= self->len);

		Error err = arraylist_reserve_additional(self, additional);
		if (err != ERR_SUCCESS) return err;
	}

	arraylist_splice_assume_capacity(self, index, count, new_items, new_items_count);

	return ERR_SUCCESS;
}

void arraylist_splice_assume_capacity(
	ArrayList *self,
	size_t index, size_t count,
	void *new_items,
	size_t new_items_count
) {
	assert(index <= self->len);

	// Make sure there's no overflow on `index + count`.
	assert(index + count <= self->len);

	if (new_items_count > count) {
		size_t additional = new_items_count - count;

		// Make sure there's no overflow...
		assert(self->len + additional >= self->len);

		// ...and we have the capacity.
		assert(self->len + additional <= self->cap);
	}

	memmove(
		arraylist_get_unchecked(self, index + count),
		arraylist_get_unchecked(self, index + new_items_count),
		self->item_size * (self->len - index - count)
	);

	memcpy(
		arraylist_get_unchecked(self, index),
		new_items,
		self->item_size * new_items_count
	);

	self->len -= count;
	self->len += new_items_count;
}
