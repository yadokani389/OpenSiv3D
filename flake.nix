{
  description = "A C++20 framework for creative coding (2D/3D games, media art, visualizers, and simulators).";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/release-24.11";
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];
      perSystem =
        { pkgs, ... }:
        {
          packages.default =
            with pkgs;
            stdenv.mkDerivation {
              pname = "OpenSiv3D";
              version = "0.6.15";

              src = ./.;

              nativeBuildInputs = [
                cmake
                ninja
                pkgconf
                libsysprof-capture
              ];

              propagatedBuildInputs = [
                zlib
                alsa-lib
                ffmpeg_7
                boost183
                giflib
                mesa
                libmpg123
                opencv
                opusfile
                soundtouch
                libtiff
                libwebp
                util-linux
                xorg.libXft
                xorg.libXdmcp
                xorg.libXtst
                libGLU
                libvorbis
                harfbuzz
                glib
                gtk3
                curl
                pcre
                pcre2
                libselinux
                libthai
                libsepol
                libdatrie
                libxkbcommon
                libepoxy
                lerc
              ];

              cmakeFlags = [
                "-GNinja"
                "-DCMAKE_BUILD_TYPE=RelWithDebInfo"
                "-S ../Linux"
              ];

              env = {
                NIX_CFLAGS_COMPILE = toString [
                  "-Wno-deprecated-declarations"
                ];
              };
            };
        };
    };
}
