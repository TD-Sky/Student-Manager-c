#ifndef __VEC_H
#define __VEC_H

#include <stdbool.h>
#include <stdlib.h>

#include "student.h"

// 值泛型
typedef Student T;

// 变长数组
typedef struct Vec {
    T *buf;
    size_t cap;
    size_t len;
} Vec;

// 过滤器，满足条件者保留
typedef struct VecFilter {
    const Vec *vec;
    size_t cur;
    size_t len;
    bool (*predicate)(const T *);
} VecFilter;

// 构造对象
extern Vec Vec_new(void);

// 销毁对象
extern void Vec_drop(Vec *self);

// 添加值到末端
//
// false：重新分配堆内存失败
extern bool Vec_push(Vec *self, T value);

// 弹出末端值
//
// 失败：数组为空
extern T Vec_pop(Vec *self);

// 移除指定位置的元素
//
// 失败：索引超出数组长度
extern T Vec_remove(Vec *self, size_t index);

// 插入元素到指定位置，将原来的元素往后挤
//
// false：重新分配堆内存失败
extern bool Vec_insert(Vec *self, size_t index, T element);

// 长度
extern size_t Vec_len(const Vec *self);

// 是否为空
extern bool Vec_is_empty(const Vec *self);

// 获取指定位置元素的不可修改引用
extern const T *Vec_at(const Vec *self, size_t index);

// 返回第一个满足条件元素的1起计数位置
//
// 0：没找到
extern size_t Vec_position(const Vec *self, const void *value,
                           bool (*predicate)(const T *, const void *));

// 寻找第一个匹配条件的值
//
// NULL：没找到
extern const T *Vec_find(const Vec *self, const void *value,
                         bool (*predicate)(const T *, const void *));

// 对所有元素应用动作
extern void Vec_for_each(const Vec *self, void (*f)(const T *));

// 创建过滤器
extern VecFilter Vec_filter(const Vec *self, bool (*predicate)(const T *));

// 取下一过滤出来的元素
//
// NUll：结束
extern const T *VecFilter_next(VecFilter *self);

#endif
