#include "gvltest.h"

#include <ruby/thread.h>
#include <time.h>
#include <errno.h>

static VALUE rb_mGVLTest;

static VALUE sleep_holding_gvl(VALUE self, VALUE timev) {
    double time = NUM2DBL(timev);
    unsigned long long int ns = time * 1E9;
    struct timespec ts = { ns / 1000000000LL, ns % 1000000000LL };

    int res;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return timev;
}

static void *nop(void *) {
    return NULL;
}

static VALUE nogvl_nop(VALUE self) {
    rb_thread_call_without_gvl(nop, NULL, NULL, NULL);
    return Qnil;
}

RUBY_FUNC_EXPORTED void
Init_gvltest(void)
{
  rb_mGVLTest = rb_define_module("GVLTest");
  rb_define_singleton_method(rb_mGVLTest, "sleep_holding_gvl", sleep_holding_gvl, 1);
  rb_define_singleton_method(rb_mGVLTest, "nogvl_nop", nogvl_nop, 0);
}
