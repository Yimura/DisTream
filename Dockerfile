FROM archlinux:base AS build

RUN pacman -Sy

RUN pacman -S --noconfirm make gcc 

RUN pacman -S --noconfirm premake

RUN pacman -S --noconfirm boost websocketpp

WORKDIR /build

COPY . .

RUN ./scripts/build_release.sh

FROM archlinux:base AS final

WORKDIR /app

COPY --from=build /build/bin/Release/DisTream .

ENTRYPOINT [ "./DisTream" ]