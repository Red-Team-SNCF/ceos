import json
import base64

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
        response.Message = json.dumps(inputMsg.Message).encode()
        return response

    async def translate_from_c2_format(self, inputMsg: TrCustomMessageToMythicC2FormatMessage) -> TrCustomMessageToMythicC2FormatMessageResponse:
        response = TrCustomMessageToMythicC2FormatMessageResponse(Success=True)
        response.Message = json.loads(inputMsg.Message)
        return response
