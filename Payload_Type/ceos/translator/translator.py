import json
import base64
import binascii
import os

from translator.utils import *
from translator.commands_from_c2 import *
from translator.commands_from_implant import *

from mythic_container.TranslationBase import *


class myPythonTranslation(TranslationContainer):
    name = "CeosTranslator"
    description = "Translator for Ceos agent"
    author = "@RedTeam_SNCF"

    async def generate_keys(self, inputMsg: TrGenerateEncryptionKeysMessage) -> TrGenerateEncryptionKeysMessageResponse:
        response = TrGenerateEncryptionKeysMessageResponse(Success=True)
        response.DecryptionKey = b""
        response.EncryptionKey = b""
        return response

    async def translate_to_c2_format(self, inputMsg: TrMythicC2ToCustomMessageFormatMessage) -> TrMythicC2ToCustomMessageFormatMessageResponse:
        response = TrMythicC2ToCustomMessageFormatMessageResponse(Success=True)
        print("C2 --> IMPLANT :" + json.dumps(inputMsg.Message))
        response.Message = json.dumps(inputMsg.Message).encode()
        return response

    async def translate_from_c2_format(self, inputMsg: TrCustomMessageToMythicC2FormatMessage) -> TrCustomMessageToMythicC2FormatMessageResponse:
        response = TrCustomMessageToMythicC2FormatMessageResponse(Success=True)
        print("IMPLANT --> C2 : " + binascii.hexlify(inputMsg.Message).decode('cp850'))
        #response.Message = json.loads(inputMsg.Message)
        data = inputMsg.Message
        if data[0] == commands["checkin"]["hex_code"]:
            print("CHECK IN")
            response.Message = checkIn(data[1:])
        elif data[0] == commands["get_tasking"]["hex_code"]: #GET_TASKING
            print("GET TASKING")
            response.Message = getTasking(data[1:])
        elif data[0] == commands["post_response"]["hex_code"]: #POSTREPONSE
            print("POST RESPONSE")
            response.Message = postResponse(data[1:])

        return response
