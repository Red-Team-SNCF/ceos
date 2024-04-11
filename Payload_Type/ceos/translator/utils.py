import base64
import os


def getBytesWithSize(data):
    size = int.from_bytes(data[0:4])
    data = data[4:]
    return data[:size], data[size:]
