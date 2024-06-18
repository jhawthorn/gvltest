require "test_helper"

class TestGVLtest < Minitest::Test
  def test_sleep_without_gvl
    timer = GVLTiming.measure do
      GVLTest.sleep_without_gvl(1)
    end

    assert_near 1.0, timer.duration
    assert_near 0, timer.running_duration
  end

  def test_sleep_holding_gvl
    timer = GVLTiming.measure do
      GVLTest.sleep_holding_gvl(1)
    end

    assert_near 1.0, timer.duration
    assert_near 1.0, timer.running_duration
  end

  def assert_near(expected, actual, allowed_delta=0.010)
    expected_range = (expected - allowed_delta)..(expected + allowed_delta)
    assert_includes expected_range, actual
  end
end
