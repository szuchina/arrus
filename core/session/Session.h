#ifndef ARRUS_CORE_SESSION_SESSION_H
#define ARRUS_CORE_SESSION_SESSION_H

#include <memory>
#include <unordered_map>

#include "arrus/core/devices/Device.h"
#include "arrus/core/devices/DeviceId.h"
#include "arrus/core/session/SessionSettings.h"
#include "arrus/core/common/exceptions.h"
#include "arrus/core/devices/us4r/Us4RSettings.h"

namespace arrus {

class Session {
public:
    /**
     * Creates a new session with the provided configuration.
     *
     * @param sessionSettings session settings to set.
     */
    explicit Session(const SessionSettings &sessionSettings);

    /**
     * Releases all allocated resources and devices.
     */
    ~Session() = default;

    Session(const Session &) = delete;

    Session(const Session &&) = delete;

    Session &operator=(const Session &) = delete;

    Session &operator=(const Session &&) = delete;

    /**
     * Returns a handle to device with given Id.
     *
     * @param deviceId device identifier
     * @return a device handle
     */
    Device::Handle& getDevice(const std::string &deviceId);

    /**
     * Returns a handle to device with given Id.
     *
     * @param deviceId device identifier
     * @return a device handle
     */
    Device::Handle& getDevice(const DeviceId &deviceId);

private:
    using DeviceMap = std::unordered_map<DeviceId, Device::Handle,
            GET_HASHER_NAME(DeviceId)>;

    DeviceMap configureDevices(const SessionSettings &sessionSettings);

    DeviceMap devices;
};
}


#endif //ARRUS_CORE_SESSION_SESSION_H
