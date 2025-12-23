#include <jeff/jasync-sem.h>
#include <jeff/jasync.h>
#include <jeff/jeff.h>
#include <stdio.h>

static int async1_flag, async2_flag;

static async async1(jasync *p) {
  async_begin(p);

  while (JTRUE) {
    await(async2_flag != 0);
    printf("async1 is running!\n");

    async2_flag = 0;
    async1_flag = 1;
  }

  async_end;
}

static async async2(jasync *p) {
  async_begin(p);

  while (JTRUE) {
    /* Let the other async run. */
    async2_flag = 1;

    /* Wait until the other async has set its flag. */
    await(async1_flag != 0);
    printf("async2 running!\n");

    /* We then reset the other async's flag. */
    async1_flag = 0;

    /* And we loop. */
  }

  async_end;
}

void example_small(int i) {
  jasync *p1 = MALLOC(jasync);
  jasync *p2 = MALLOC(jasync);

  void **garbage = CALLOC(void *, 2);
  garbage[0] = VOID_PTR(p1);
  garbage[1] = VOID_PTR(p2);

  /* Initialize the async state variables with async_init(). */
  async_init(p1);
  async_init(p2);

  /*
   * Then we schedule the two asyncs by repeatedly calling their
   * async functions and passing a pointer to the async
   * state variables as arguments.
   */
  while (--i >= 0) {
    async1(p1);
    async2(p2);
  }

  j_gc(garbage, 3);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
