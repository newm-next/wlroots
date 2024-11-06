#include <stdlib.h>
#include <string.h>
#include <wayland-server-core.h>
#include <wlr/interfaces/wlr_switch.h>
#include <wlr/types/wlr_switch.h>

void wlr_switch_init(struct wlr_switch *switch_device,
		const struct wlr_switch_impl *impl, const char *name) {
	wlr_input_device_init(&switch_device->base, WLR_INPUT_DEVICE_SWITCH, name);
	switch_device->base.switch_device = switch_device;

	switch_device->impl = impl;
	wl_signal_init(&switch_device->events.toggle);
}

void wlr_switch_destroy(struct wlr_switch *switch_device) {
	if (!switch_device) {
		return;
	}
	wlr_input_device_finish(&switch_device->base);
	if (switch_device->impl && switch_device->impl->destroy) {
		switch_device->impl->destroy(switch_device);
	} else {
		free(switch_device);
	}
}