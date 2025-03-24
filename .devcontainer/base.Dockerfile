FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN \
    apt update \
    && apt install -y --no-install-recommends \
    build-essential \
    cmake 


# Set the default shell to bash instead of sh
ENV SHELL /bin/zsh