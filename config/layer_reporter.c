#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>
#include <raw_hid/hid.h>

static int layer_state_listener(const zmk_event_t *eh) {
    printk("LAYER EVENT!\n");
    struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (!ev) return ZMK_EV_EVENT_BUBBLE;

    uint8_t report[32] = {0};
    report[0] = 0x01;                          // command: layer update
    report[1] = zmk_keymap_highest_layer_active(); // 현재 layer index
    raw_hid_send(report, sizeof(report));

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_reporter, layer_state_listener);
ZMK_SUBSCRIPTION(layer_reporter, zmk_layer_state_changed);
