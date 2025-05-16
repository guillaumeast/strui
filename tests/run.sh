#!/usr/bin/env sh

RED=$(printf "\033[31m")
ORANGE=$(printf "\033[38;5;208m")
GREEN=$(printf "\033[32m")
RESET=$(printf "\033[0m")

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
STRUI_DIR="${SCRIPT_DIR}/.."

DOCKERFILE="${STRUI_DIR}/tests/Dockerfile"
IMAGE="strui-test"

VOLUME_LOCAL="${STRUI_DIR}/tests/volume"
VOLUME_DOCKER="/volume"

printf -- "----------------\n"
printf "🧪 ${ORANGE}Launching Local test...${RESET}\n"

sh "${STRUI_DIR}/tests/test.sh" || exit 1

printf -- "\n----------------\n"
printf "🐳  ${ORANGE}Launching Docker test...${RESET}\n"
printf -- "----------------\n"

mkdir -p "${VOLUME_LOCAL}" || exit 1

if [ "$1" = "--verbose" ]; then
    docker build -f "${DOCKERFILE}" -t "${IMAGE}" "${STRUI_DIR}"
else
    docker build -f "${DOCKERFILE}" -t "${IMAGE}" "${STRUI_DIR}" >/dev/null 2>&1
fi

if [ $? = 0 ]; then
    printf "${GREEN}✔${RESET} Image built\n"
else
    printf "${RED}❌ Build failed\n${RESET}" >&2
    return 1
fi

docker run --rm -it "${IMAGE}" bash -c "make install && sh ./tests/test.sh"

printf -- "\n----------------\n"
printf "🧹 ${ORANGE}Cleaning test files...${RESET}\n"
printf -- "----------------\n"

[ -d "${VOLUME_LOCAL}" ] && rm -rf "${VOLUME_LOCAL}"

printf "\n ✅ Done\n"
