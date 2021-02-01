""" Arrus device handle. """
import abc
import dataclasses
import arrus.core


@dataclasses.dataclass(frozen=True)
class DeviceType:
    type: str
    core_repr: object


# Currently available python devices.
CPU = DeviceType("CPU", arrus.core.DeviceType_CPU)
Us4R = DeviceType("Us4R", arrus.core.DeviceType_Us4R)


@dataclasses.dataclass(frozen=True)
class DeviceId:
    device_type: object
    ordinal: int


def get_device_type_str(s):
    """
    Extracts device type from given string id.

    :param str: id as a string
    :return: device type string
    """
    s = s.strip()
    n = s.split("/")
    if s.startswith("/"):
        n = n[1:]
    if len(n) == 0:
        raise ValueError("No device provided in the id.")
    c = n[0].split(":")
    return c[0]


class Device(abc.ABC):
    """
    A handle to device.

    This is an abstract class and should not be instantiated.
    """

    @abc.abstractmethod
    def get_device_id(self) -> DeviceId:
        pass

    def __str__(self):
        return str(self.get_device_id())

    def __repr__(self):
        return self.__str__()


class UltrasoundDeviceDTO(abc.ABC):
    @abc.abstractmethod
    def get_id(self):
        pass
