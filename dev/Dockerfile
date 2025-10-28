# Dev container Dockerfile for Phlex
# Uses the CI image as a base and adds VS Code dev container requirements
#
# Podman instructions for building an image with this file:
#
#   $ cd <directory with this file>
#   $ podman build --format docker --tag phlex-dev:<tag> [-v <local-buildcache>:/build-cache] .
#   $ podman login ghcr.io --username <username> -p <token>
#   $ podman push phlex-dev:<tag> ghcr.io/framework-r-d/phlex-dev:<tag>
# ... and optionally:
#   $ podman push phlex-dev:<tag> ghcr.io/framework-r-d/phlex-dev:latest
#
# where <tag> is the date (e.g. "2025-08-12").

FROM ghcr.io/framework-r-d/phlex-ci:latest

# Note: The parent image already sets LANG and LC_ALL, and creates the vscode user

USER root
# Install GitHub's act CLI for local workflow testing
RUN curl -s https://api.github.com/repos/nektos/act/releases/latest \
    | grep -Ee '"browser_download_url": .*/act_Linux_x86_64\.' \
    | cut -d '"' -f 4 \
    | xargs curl -sfSL | tar -C /usr/local/bin -zx act && \
    chmod +x /usr/local/bin/act

# Install GitHub CLI (gh)
RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl gnupg \
    && curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg \
        | dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
    && chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" \
        > /etc/apt/sources.list.d/github-cli.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends gh \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set user and workdir for dev container
USER vscode
WORKDIR /workspaces/phlex

# Default shell initialization and healthcheck (optional)
# Note: Podman OCI format ignores SHELL and HEALTHCHECK. Use --format docker if needed.
SHELL ["/bin/bash", "-c"]
HEALTHCHECK CMD curl -f https://github.com || exit 1
