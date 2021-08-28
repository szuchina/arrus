#ifndef ARRUS_CORE_DEVICES_US4R_US4R_H
#define ARRUS_CORE_DEVICES_US4R_US4R_H

#include <memory>

#include "arrus/core/api/devices/Device.h"
#include "arrus/core/api/devices/DeviceWithComponents.h"
#include "arrus/core/api/devices/us4r/Us4OEM.h"
#include "arrus/core/api/devices/us4r/ProbeAdapter.h"
#include "arrus/core/api/devices/probe/Probe.h"
#include "arrus/core/api/ops/us4r/TxRxSequence.h"
#include "arrus/core/api/ops/us4r/Scheme.h"
#include "arrus/core/api/framework/Buffer.h"
#include "arrus/core/api/framework/DataBufferSpec.h"
#include "FrameChannelMapping.h"


namespace arrus::devices {

/**
 * Us4R system: a group of Us4OEM modules and related components.
 */
class Us4R : public DeviceWithComponents {
public:
    using Handle = std::unique_ptr<Us4R>;
    static constexpr long long INF_TIMEOUT = -1;

    explicit Us4R(const DeviceId &id): DeviceWithComponents(id) {}

    ~Us4R() override = default;

    /**
     * Returns a handle to Us4OEM identified by given ordinal number.
     *
     * @param ordinal ordinal number of the us4oem to get
     * @return a handle to the us4oem module
     */
    virtual Us4OEM::RawHandle getUs4OEM(Ordinal ordinal) = 0;

    /**
     * Returns a handle to an adapter identified by given ordinal number.
     *
     * @param ordinal ordinal number of the adapter to get
     * @return a handle to the adapter device
     */
    virtual ProbeAdapter::RawHandle getProbeAdapter(Ordinal ordinal) = 0;

    /**
     * Returns a handle to a probe identified by given ordinal number.
     *
     * @param ordinal ordinal number of the probe to get
     * @return a handle to the probe
     */
    virtual arrus::devices::Probe* getProbe(Ordinal ordinal) = 0;

    virtual std::pair<
        std::shared_ptr<arrus::framework::Buffer>,
        std::shared_ptr<arrus::devices::FrameChannelMapping>
    >
    upload(const ::arrus::ops::us4r::TxRxSequence &seq, unsigned short rxBufferSize,
           const ::arrus::ops::us4r::Scheme::WorkMode &workMode,
           const ::arrus::framework::DataBufferSpec &hostBufferSpec) = 0;

    /**
     * Sets HV voltage.
     *
     * @param voltage voltage to set [V]
     */
    virtual void setVoltage(Voltage voltage) = 0;

    /**
     * Disables HV voltage.
     */
    virtual void disableHV() = 0;

    /**
     * Sets tgc curve points asynchronously.
     *
     * Setting empty vector turns off analog TGC.
     * Setting non-empty vector turns off DTGC and turns on analog TGC.
     *
     *
     *
     * @param tgcCurvePoints tgc curve points to set.
     * @param applyCharacteristic set it to true if you want to apply a pre-computed characteristic. True works only
     *
     */
    virtual void setTgcCurve(const std::vector<float>& tgcCurvePoints, bool applyCharacteristic = true) = 0;

    /**
     * Sets low-pass filter cutoff frequency (AFE parameter).
     *
     * Available values: 10000000, 15000000, 20000000, 30000000, 35000000,
     * 50000000 [Hz].
     *
     * @param value cutoff frequency to set [Hz]
     */
    virtual void setLpfCutoff(uint32 value) = 0;

    /**
     * Sets active termination value (AFE parameter).
     *
     * Available values: 50, 100, 200, 400 [Ohm].
     * std::nullopt turns off active termination
     *
     * @param value active termination to set [Ohm]
     */
    virtual void setActiveTermination(std::optional<uint16> value) = 0;

    /**
     * Sets digital time gain compensation, measured in attenuation values
     * (AFE parameter).
     *
     * Available values: 0, 6, 12, 18, 24, 30, 36, 42 [dB].
     * std::nullopt turns off DTGC.
     * Setting any other acceptable value turns off analog TGC and turns on
     * DTGC.
     *
     * @param value DTGC attenuation to set [dB]
     */
    virtual void setDtgcAttenuation(std::optional<uint8> value) = 0;



    virtual void start() = 0;
    virtual void stop() = 0;

    Us4R(Us4R const&) = delete;
    Us4R(Us4R const&&) = delete;
    void operator=(Us4R const&) = delete;
    void operator=(Us4R const&&) = delete;
};

}

#endif //ARRUS_CORE_DEVICES_US4R_US4R_H
