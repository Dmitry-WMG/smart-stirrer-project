import csv
import time
import uuid
import Adafruit_BluefruitLE

# Define service and characteristic UUIDs.
UART_SERVICE_UUID = uuid.UUID('6E400001-B5A3-F393-E0A9-E50E24DCCA9E')
TX_CHAR_UUID = uuid.UUID('6E400002-B5A3-F393-E0A9-E50E24DCCA9E')
RX_CHAR_UUID = uuid.UUID('6E400003-B5A3-F393-E0A9-E50E24DCCA9E')
STIRRERADDRESS = "78E36E16-5C43-4FD5-AF4E-3D66ECB00B76"

ble = Adafruit_BluefruitLE.get_provider()


def main():
    adapter = ble.get_default_adapter()
    adapter.power_on()
    ble.disconnect_devices([UART_SERVICE_UUID])
    global device

    print("Searching for Smart Stirrer...")
    try:
        adapter.start_scan()
        device = ble.find_device(service_uuids=[UART_SERVICE_UUID])
        if "Smart" in device.name:
            print("Discovered device: {0}".format(device.name))
        if device is None:
            raise RuntimeError("     Failed to find Smart Stirrer!")
    finally:
        adapter.stop_scan()
    print("Connected.")
    device.connect()

    try:
        # find the UART service and characteristics associated with the device
        device.discover([UART_SERVICE_UUID], [TX_CHAR_UUID, RX_CHAR_UUID])
        uart = device.find_service(UART_SERVICE_UUID)
        rx = uart.find_characteristic(RX_CHAR_UUID)
        tic = time.perf_counter()

        def hex2byte(string):
            # converts bit data array from the Stirrer to string
            try:
                return string.decode("utf-8")
            except ValueError:
                return string

        def typecast(string):
            """
            convert string of bits to numeric array
            first 8 bytes are color sensor (RGBC)
            then 6 bytes for adc: first pair is for thermistor,
            then OPA and conductivity
            """
            # last 8 bytes for accelerometer (X,Y, Z and temperature sensor)
            out = [int(str(string[i])) for i in range(0, len(string))]
            # convert each pair of bytes to int16 number
            hex2data = [((out[i] << 8) + (out[i + 1] & 0x00ff)) for i in range(0, len(out), 2)]
            # need this to swap bytes for accelerometer
            for idx, val in enumerate(hex2data):
                if idx >= 7:
                    hex2data[idx] = hex2data[idx] - 2**16
            return hex2data

        def save2csv(string):
            # save converted data (R G B C adc1 adc2 adc3 accX accY acc Z temperature) to file
            with open("/Users/Dmitry/Documents/PythonProjects/test_csv_file.csv", 'a') as file:
                sensor = csv.writer(file)
                sensor.writerow(string)

        def received(raw_data):
            # read and convert the new data from the UART
            global data
            toc = float(f"{(time.perf_counter() - tic):4f}")
            hexdata = hex2byte(raw_data)
            data = typecast(hexdata)
            data.insert(0, toc)
            save2csv(data)
            print("Data: ", data)

        while True:
            # Subscribe to RX characteristic changes to receive data.
            rx.start_notify(received)
            time.sleep(0.5)

    except KeyboardInterrupt:
        pass

    finally:
        device.disconnect()


if __name__ == "__main__":
    ble.initialize()
    ble.run_mainloop_with(main)
