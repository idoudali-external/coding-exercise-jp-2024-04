"""ubuntu_base docker image"""

import os
from typing import List

import docker_wrapper


class DockerImage(docker_wrapper.DockerImage):
    """build_env docker image

    Args:
        docker_wrapper (_type_): Parent class
    """

    NAME = "build_env"

    def __init__(self) -> None:
        super().__init__()
        self.name = "build_env"
        self.docker_folder = os.path.realpath(
            os.path.join(os.path.realpath(__file__), "../Docker")
        )
        print(self.docker_folder)
