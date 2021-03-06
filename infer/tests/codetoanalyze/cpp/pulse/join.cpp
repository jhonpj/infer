/*
 * Copyright (c) 2018-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
struct foo {
  int* val;
};

struct list {
  struct list* next;
  struct foo* foo;
};

int invalidate_node_alias_bad(struct list* head, int cond) {
  int* result = 0;
  struct list* x = head;
  if (cond) {
    result = x->next->foo->val;
    delete result;
  } else {
    x = x->next;
    struct list* y = x->next;
    result = x->foo->val;
    delete result;
  }
  return *result;
}

struct BasicStruct {
  // force destructor calls to be injected
  virtual void some_method() {}
};

int nested_loops_ok() {
  while (true) {
    BasicStruct x;
    for (;;) {
      x.some_method();
    }
  }
}
