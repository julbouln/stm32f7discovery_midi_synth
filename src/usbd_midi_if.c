#include "usbd_midi_if.h"
#include "lfluidsynth.h"

extern fluid_synth_t* synth;

static int8_t Midi_Receive(uint8_t *msg, uint32_t len);

extern USBD_HandleTypeDef USBD_Device;
USBD_Midi_ItfTypeDef USBD_Midi_fops = {
	Midi_Receive,
};

static int8_t Midi_Receive(uint8_t *msg, uint32_t len) {

	uint8_t chan = msg[1] & 0xf;
	uint8_t msgtype = msg[1] & 0xf0;
	uint8_t b1 =  msg[2];
	uint8_t b2 =  msg[3];
	uint16_t b = ((b2 & 0x7f) << 7) | (b1 & 0x7f);

	switch (msgtype) {
	case 0x80:
		fluid_synth_noteoff(synth, chan, b1);
		break;
	case 0x90:
		fluid_synth_noteon(synth, chan, b1, b2);
		break;
	case 0xB0:
		fluid_synth_cc(synth, chan, b1, b2);
		break;
	case 0xC0:
		fluid_synth_program_change(synth, chan, b1);
		break;
	case 0xD0:
		fluid_synth_channel_pressure(synth, chan, b1);
		break;
	case 0xE0:
		fluid_synth_pitch_bend(synth, chan, b);
		break;
	default:
		break;
	}

	return 0;
}