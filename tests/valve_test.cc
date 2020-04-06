#include "gtest/gtest.h"
#include "valve.h"

TEST(Valve, init_test_driver) {
    struct valve_driver *drv = NULL;
    struct valve *v = NULL;

    EXPECT_EQ(valve_init(v, drv), -EINVAL);
}
