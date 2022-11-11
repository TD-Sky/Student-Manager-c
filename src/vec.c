#include "vec.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

Vec Vec_new(void) {
    Vec vec = {
        .buf = (T *)calloc(8, sizeof(T)),
        .len = 0,
        .cap = 8,
    };

    return vec;
}

void Vec_drop(Vec *self) {
    free(self->buf);
    self->buf = NULL;
    self->len = 0;
    self->cap = 0;
}

bool Vec_push(Vec *self, T value) {
    if (self->len >= self->cap) {
        self->cap *= 2;
        self->buf = (T *)reallocarray(self->buf, self->cap, sizeof(T));

        if (self->buf == NULL) {
            return false;
        }
    }

    self->buf[self->len++] = value;

    return true;
}

T Vec_pop(Vec *self) {
    if (self->len == 0) {
        exit(EXIT_FAILURE);
    }

    return self->buf[--self->len];
}

T Vec_remove(Vec *self, size_t index) {
    if (index >= self->len) {
        exit(EXIT_FAILURE);
    }

    T rm = self->buf[index];

    memmove(&self->buf[index], &self->buf[index + 1],
            (self->len - 1 - index) * sizeof(T));

    self->len -= 1;

    return rm;
}

bool Vec_insert(Vec *self, size_t index, T element) {
    if (self->len >= self->cap) {
        self->cap *= 2;
        self->buf = (T *)reallocarray(self->buf, self->cap, sizeof(T));

        if (self->buf == NULL) {
            return false;
        }
    }

    memmove(&self->buf[index + 1], &self->buf[index],
            (self->len - index) * sizeof(T));
    self->buf[index] = element;
    self->len += 1;

    return true;
}

size_t Vec_len(const Vec *self) { return self->len; }

bool Vec_is_empty(const Vec *self) { return self->len == 0; }

void Array_sorted_by(const Vec *self, T *sorted[],
                     int (*compare)(const void *lhs, const void *rhs)) {
    for (size_t i = 0; i < self->len; i++) {
        sorted[i] = &self->buf[i];
    }

    // 降序排列
    qsort(sorted, self->len, sizeof(T *), compare);
}

/* Index */

const T *Vec_at(const Vec *self, size_t index) {
    return index < self->len ? &self->buf[index] : NULL;
}

/* Iterator */

size_t Vec_position(const Vec *self, const void *value,
                    bool (*predicate)(const T *, const void *)) {
    for (size_t i = 0; i < self->len; i++) {
        if (predicate(&self->buf[i], value)) {
            return i + 1;
        }
    }

    return 0;
}

const T *Vec_find(const Vec *self, const void *value,
                  bool (*predicate)(const T *, const void *)) {
    for (size_t i = 0; i < self->len; i++) {
        if (predicate(&self->buf[i], value)) {
            return &self->buf[i];
        }
    }

    return NULL;
}

void Vec_for_each(const Vec *self, void (*f)(const T *)) {
    for (size_t i = 0; i < self->len; i++) {
        f(&self->buf[i]);
    }
}

VecFilter Vec_filter(const Vec *self, bool (*predicate)(const T *)) {
    VecFilter filter = {
        .vec = self,
        .cur = 0,
        .len = self->len,
        .predicate = predicate,
    };

    return filter;
}

const T *VecFilter_next(VecFilter *self) {
    for (; self->cur < self->len; self->cur += 1) {
        const T *item = &self->vec->buf[self->cur];

        if (self->predicate(item)) {
            self->cur += 1;  // 提前返回，所以要提前增序
            return item;
        }
    }

    return NULL;
}
