#!/usr/bin/env python3

"""Command line helper tool for this repo"""

import os
from enum import Enum

import docker_wrapper


def main() -> None:
    """Helper main function"""

    image_dir = os.path.join(
        os.path.dirname(os.path.realpath(__file__)), "docker-images"
    )

    app = docker_wrapper.cli.create_cli(image_dir)  # type: ignore
    app()


# Allow the script to be run standalone (useful during development).
if __name__ == "__main__":
    main()
