/*
 * Copyright (c) 2020 Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_DRIVERS_SENSOR_BQ274XX_H_
#define ZEPHYR_INCLUDE_DRIVERS_SENSOR_BQ274XX_H_

#include <zephyr/device.h>

/**
 * @brief Skip the devicetree-derived Subclass 82 state recompute on the
 * next bq274xx_gauge_configure() pass.
 *
 * With `zephyr,lazy-load` set, the driver normally recomputes
 * design_capacity/design_energy/terminate_voltage/taper_rate (Subclass 82)
 * from this node's design-capacity/design-voltage/taper-current/
 * terminate-voltage properties on the first sensor_sample_fetch(),
 * overwriting whatever was already on the gauge if they don't match.
 *
 * Call this before the first sensor_sample_fetch() when a caller has
 * already fully configured Subclass 82 itself (e.g. by writing a
 * manufacturer-supplied Golden Image flashstream directly over I2C) and
 * wants those values to stick instead of being silently recomputed from
 * devicetree.
 *
 * Everything else bq274xx_gauge_configure() normally does on that same
 * pass - unsealing, entering/exiting CONFIG UPDATE, the BQ27427-family CC
 * Gain erratum fix, the chemistry ID check, re-sealing, and BAT_INSERT -
 * still runs as usual. Only the Subclass 82 read/compare/write step is
 * skipped.
 *
 * @param dev bq274xx device instance.
 */
void bq274xx_skip_dt_state_config(const struct device *dev);

#endif /* ZEPHYR_INCLUDE_DRIVERS_SENSOR_BQ274XX_H_ */
