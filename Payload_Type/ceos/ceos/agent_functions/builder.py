import pathlib
from mythic_container.PayloadBuilder import *
from mythic_container.MythicCommandBase import *
from mythic_container.MythicRPC import *
import json


class CeosAgent(PayloadType):
    name = "Ceos"
    file_extension = "exe"
    author = "@RedTeam_SNCF"
    supported_os = [SupportedOS.Windows]
    wrapper = False
    wrapped_payloads = []
    note = """Basic Implant in C"""
    supports_dynamic_loading = False
    c2_profiles = ["http"]
    mythic_encrypts = False
    translation_container = "CeosTranslator" 
    build_parameters = []
    agent_path = pathlib.Path(".") / "ceos"
    agent_icon_path = agent_path / "agent_functions" / "ceos.png"
    agent_code_path = agent_path / "agent_code"

    build_steps = [
        BuildStep(step_name="Gathering Files", step_description="Making sure all commands have backing files on disk"),
        BuildStep(step_name="Configuring", step_description="Stamping in configuration values")
    ]

    async def build(self) -> BuildResponse:
        # this function gets called to create an instance of your payload
        resp = BuildResponse(status=BuildStatus.Success)
        # create the payload
        build_msg = ""

        return resp
