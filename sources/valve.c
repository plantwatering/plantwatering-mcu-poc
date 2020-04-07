#include <stdlib.h>
#include "valve.h"
#include "errno.h"

#define UNUSED(x) (void)(x)

static void valve_notificate_default(const struct valve *v, bool value)
{
    UNUSED(v);
    UNUSED(value);
    return;
}

int valve_set(struct valve *v, bool value)
{
    if (value) {
        v->drv->open(v->drv);
    } else {
        v->drv->close(v->drv);
    }

    v->notificate(v, value);

    return 0;
}

int valve_get(const struct valve *v, bool *value)
{
    v->drv->get_state(v->drv, value);

    return 0;
}

int valve_init(struct valve *v, struct valve_driver *drv)
{
    int ret;

    if (!drv) {
        ret = -EINVAL;
        goto exit;
    }

    v = (struct valve*) malloc(sizeof(*v));
    if (!v) {
        ret = -ENOMEM;
        goto exit;
    }

    v->get = valve_get;
    v->set = valve_set;
    v->notificate = valve_notificate_default;
    v->drv = drv;

    return 0;
exit:
    return ret;
}
