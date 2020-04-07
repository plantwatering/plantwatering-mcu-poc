#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "valve_driver.h"
#include "valve_mock.h"
#include "gtest/gtest.h"

struct valve_mock_priv {
    bool cached_state; /* false means closed, true means open */
};

static int valve_mock_open(struct valve_driver* drv)
{
    struct valve_mock_priv *priv = (struct valve_mock_priv*) drv->priv;

    if (!priv->cached_state) {
        priv->cached_state = !priv->cached_state;
        SUCCEED();
    } else {
        ADD_FAILURE() << "Valve already open";
    }

    return 0;
}

static int valve_mock_close(struct valve_driver* drv)
{
    struct valve_mock_priv *priv = (struct valve_mock_priv*) drv->priv;

    if (priv->cached_state) {
        priv->cached_state = !priv->cached_state;
        SUCCEED();
    } else {
        ADD_FAILURE() << "Valve already closed";
    }

    return 0;
}

static int valve_mock_get_state(const struct valve_driver* drv, bool *value)
{
    struct valve_mock_priv *priv = (struct valve_mock_priv*) drv->priv;

    *value = priv->cached_state;

    return 0;
}

static int valve_mock_priv_init(struct valve_driver *drv)
{
    struct valve_mock_priv *priv = (struct valve_mock_priv*) drv->priv;

    priv->cached_state = false;

    return 0;
}

int valve_mock_init(struct valve_driver *drv)
{
    int ret;

    if (!drv) {
        return -EINVAL;
    }

    drv->open = valve_mock_open;
    drv->close = valve_mock_close;
    drv->get_state = valve_mock_get_state;

    drv->priv = (struct valve_mock_priv*) malloc(sizeof(struct valve_mock_priv));
    if (!drv->priv) {
        ret = -ENOMEM;
        goto nomem;
    }

    return valve_mock_priv_init(drv);
nomem:
    free(drv);
    return ret;
}

void valve_mock_deinit(struct valve_driver *drv)
{
    if (!drv)
        return;
    free(drv->priv);
}
