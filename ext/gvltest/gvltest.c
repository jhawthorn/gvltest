#include "gvltest.h"

#include <time.h>
#include <errno.h>

VALUE rb_mGVLTest;

VALUE sleep_holding_gvl(VALUE self, VALUE timev) {
    double time = NUM2DBL(timev);
    unsigned long long int ns = time * 1E9;
    struct timespec ts = { ns / 1000000000LL, ns % 1000000000LL };

    int res;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return timev;
}

RUBY_FUNC_EXPORTED void
Init_gvltest(void)
{
  rb_mGVLTest = rb_define_module("GVLTest");
  rb_define_singleton_method(rb_mGVLTest, "sleep_holding_gvl", sleep_holding_gvl, 1);
}
