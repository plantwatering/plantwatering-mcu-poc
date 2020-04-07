#include "gtest/gtest.h"
#include "valve.h"
#include "valve_console.h"

TEST(Valve, init_test_driver_console_fail) {
    struct valve_driver *drv = NULL;

    EXPECT_EQ(valve_console_init(drv), -EINVAL);
}

TEST(Valve, init_test_driver_console_succeed) {
    struct valve_driver drv;

    EXPECT_EQ(valve_console_init(&drv), 0);

    valve_console_deinit(&drv);
}

TEST(Valve, init_test_stack_fail1) {
    struct valve_driver *drv = NULL;
    struct valve *v = NULL;

    EXPECT_EQ(valve_init(v, drv), -EINVAL);
}

TEST(Valve, init_test_stack_fail2) {
    struct valve_driver *drv = NULL;
    struct valve v;

    EXPECT_EQ(valve_init(&v, drv), -EINVAL);
}

TEST(Valve, init_test_stack_fail3) {
    struct valve_driver drv;
    struct valve *v = NULL;

    EXPECT_EQ(valve_init(v, &drv), -EINVAL);
}

TEST(Valve, init_test_stack_succeed) {
    struct valve_driver drv;
    struct valve v;

    valve_console_init(&drv);

    EXPECT_EQ(valve_init(&v, &drv), 0);

    valve_console_deinit(&drv);
}
