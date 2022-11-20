FROM alpine

WORKDIR /workdir

RUN \
    apk add --no-cache \
        bash \
        dbus \
        g++ \
        git \
        gmock \
        gtest \
        gtest-dev \
        meson \
        musl-dev \
        sdbus-cpp\
        sdbus-cpp-dev \
        spdlog \
        spdlog-dev \
        valgrind \
    && \
    rm -rf "/var/cache/apk/"

COPY "./dockerfiles/session.conf" "/etc/dbus-1/"
COPY "./dockerfiles/docker-entrypoint.sh" "/init"

ENTRYPOINT [ "/init" ]
