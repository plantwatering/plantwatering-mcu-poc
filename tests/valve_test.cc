#include "gtest/gtest.h"
#include "valve.h"
#include "valve_console.h"
#include "valve_mock.h"

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

TEST(Valve, stack_test_mock) {
    struct valve_driver drv;
    struct valve v;

    valve_mock_init(&drv);

    EXPECT_EQ(valve_init(&v, &drv), 0);

    valve_mock_deinit(&drv);
}

TEST(Valve, stack_test_get_value) {
    struct valve_driver drv;
    struct valve v;
    bool val;

    valve_mock_init(&drv);
    valve_init(&v, &drv);

    // Mocked valve is normally closed
    EXPECT_EQ(v.get(&v, &val), 0);
    EXPECT_EQ(val, false);

    valve_mock_deinit(&drv);
}

TEST(Valve, stack_test_set_value) {
    struct valve_driver drv;
    struct valve v;
    bool val;

    valve_mock_init(&drv);
    valve_init(&v, &drv);

    for (int i = 0 ; i < 16; ++i) {
        // Open valve
        EXPECT_EQ(v.set(&v, true), 0);
        EXPECT_EQ(v.get(&v, &val), 0);
        EXPECT_EQ(val, true);
        // Close valve
        EXPECT_EQ(v.set(&v, false), 0);
        EXPECT_EQ(v.get(&v, &val), 0);
        EXPECT_EQ(val, false);
    }

    valve_mock_deinit(&drv);
}

void notificate_callback(const struct valve *v, bool value)
{
    EXPECT_EQ(value, true);
}

TEST(Valve, stack_test_notif) {
    struct valve_driver drv;
    struct valve v;

    valve_mock_init(&drv);
    valve_init(&v, &drv);

    v.notificate = notificate_callback;

    // Open valve
    v.set(&v, true);

    valve_mock_deinit(&drv);
}
