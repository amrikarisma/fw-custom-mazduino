#include "pch.h"
#include "bench_test.h"
#include "flash_main.h"
#include "tunerstudio.h"

static void setSdCardSpi3() {
	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3mosiPin = Gpio::C12;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3sckPin = Gpio::C10;

    engineConfiguration->isSdCardEnabled = true;
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
	engineConfiguration->sdCardCsPin = Gpio::D2;
}

static void setBoard_04_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::B14;
	engineConfiguration->injectionPins[2] = Gpio::B12;
	engineConfiguration->injectionPins[3] = Gpio::B13;

	engineConfiguration->ignitionPins[0] = Gpio::E2;
	engineConfiguration->ignitionPins[1] = Gpio::E3;
	engineConfiguration->ignitionPins[2] = Gpio::C13;
	engineConfiguration->ignitionPins[3] = Gpio::E7;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;
	engineConfiguration->afr.hwChannel = EFI_ADC_8;
	engineConfiguration->vbattAdcChannel = EFI_ADC_4;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_2;
	engineConfiguration->clt.adcChannel = EFI_ADC_1;
	engineConfiguration->iat.adcChannel = EFI_ADC_0;

	setSdCardSpi3();
}

static void setBoard_ua4c_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::D8;
	engineConfiguration->injectionPins[2] = Gpio::D9;
	engineConfiguration->injectionPins[3] = Gpio::D10;

	engineConfiguration->ignitionPins[0] = Gpio::E15;
	engineConfiguration->ignitionPins[1] = Gpio::E4;
	engineConfiguration->ignitionPins[2] = Gpio::D13;
	engineConfiguration->ignitionPins[3] = Gpio::E5;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_0;
	engineConfiguration->afr.hwChannel = EFI_ADC_1;
	engineConfiguration->vbattAdcChannel = EFI_ADC_2;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_3;
	engineConfiguration->clt.adcChannel = EFI_ADC_4;
	engineConfiguration->iat.adcChannel = EFI_ADC_5;
	setSdCardSpi3();

}

static void setBoard_compact_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::D8;
	engineConfiguration->injectionPins[2] = Gpio::D9;
	engineConfiguration->injectionPins[3] = Gpio::D10;
	engineConfiguration->injectionPins[4] = Gpio::Unassigned;
	engineConfiguration->injectionPins[5] = Gpio::Unassigned;

	engineConfiguration->ignitionPins[0] = Gpio::E15;
	engineConfiguration->ignitionPins[1] = Gpio::E4;
	engineConfiguration->ignitionPins[2] = Gpio::D13;
	engineConfiguration->ignitionPins[3] = Gpio::E5;
	engineConfiguration->ignitionPins[4] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[5] = Gpio::Unassigned;
	engineConfiguration->acSwitch = Gpio::B0;
	engineConfiguration->acRelayPin = Gpio::C7;
	engineConfiguration->fuelPumpPin = Gpio::C8;	
	engineConfiguration->idle.solenoidPin = Gpio::D9;
	engineConfiguration->fanPin = Gpio::A15;	
	engineConfiguration->mainRelayPin = Gpio::E8;
	engineConfiguration->tachOutputPin = Gpio::C9;
	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7;

	engineConfiguration->clutchDownPin = Gpio::E13;
	engineConfiguration->clutchDownPinMode = PI_INVERTED_PULLUP;
	setSdCardSpi3();

}

static void setBoard_mini_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::D8;
	engineConfiguration->injectionPins[1] = Gpio::B15;
	engineConfiguration->injectionPins[2] = Gpio::B14;
	engineConfiguration->injectionPins[3] = Gpio::B13;
	engineConfiguration->injectionPins[4] = Gpio::D9;
	engineConfiguration->injectionPins[5] = Gpio::E8;

	engineConfiguration->ignitionPins[0] = Gpio::E15;
	engineConfiguration->ignitionPins[1] = Gpio::E14;
	engineConfiguration->ignitionPins[2] = Gpio::D13;
	engineConfiguration->ignitionPins[3] = Gpio::E5;
	engineConfiguration->ignitionPins[4] = Gpio::E2;
	engineConfiguration->ignitionPins[5] = Gpio::E3;
	engineConfiguration->acSwitch = Gpio::B5;
	engineConfiguration->acRelayPin = Gpio::C7;
	engineConfiguration->fuelPumpPin = Gpio::C8;	
	engineConfiguration->idle.solenoidPin = Gpio::D10;
	engineConfiguration->fanPin = Gpio::A15;	
	engineConfiguration->mainRelayPin = Gpio::C5;
	engineConfiguration->tachOutputPin = Gpio::C9;
	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7;

	engineConfiguration->clutchDownPin = Gpio::E12;
	engineConfiguration->clutchDownPinMode = PI_INVERTED_PULLUP;
	setSdCardSpi3();
}



/*PUBLIC_API_WEAK*/ void boardTsAction(uint16_t index) {
    if (index == 0) {
        setBoard_04_pinout();
    } else if (index == 1) {
        setBoard_ua4c_pinout();
    } else if (index == 2) {
		setBoard_compact_pinout();
	} else if (index == 3) {
		setBoard_mini_pinout();
	} else {
		efiPrintf("Unknown board index %d", index);
		return;
	}

	
	
    writeToFlashNow();
    onApplyPreset();
}