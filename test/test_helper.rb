# frozen_string_literal: true

$LOAD_PATH.unshift File.expand_path("../lib", __dir__)
require "gvltest"

require "gvl_timing"

ENV["MT_CPU"] = "0"
require "minitest/autorun"

class Minitest::Test
  make_my_diffs_pretty!
end
