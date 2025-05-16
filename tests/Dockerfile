# Base image
FROM ubuntu

# Prevent interactive prompts during install
ENV DEBIAN_FRONTEND=noninteractive

# Tools and libraries
RUN apt update && apt install -y \
    build-essential \
    valgrind \
    libunistring-dev \
    curl \
    git \
    ca-certificates \
    locales \
    && locale-gen en_US.UTF-8

# Env
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8
ENV PATH="/root/.local/bin:${PATH}"

# Working directory
RUN mkdir -p "/volume/strui"
COPY . /volume/strui
WORKDIR /volume/strui

# Default shell
CMD ["/bin/bash"]
