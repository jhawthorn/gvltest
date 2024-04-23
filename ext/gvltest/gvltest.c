#include "gvltest.h"

VALUE rb_mGvltest;

RUBY_FUNC_EXPORTED void
Init_gvltest(void)
{
  rb_mGvltest = rb_define_module("Gvltest");
}
