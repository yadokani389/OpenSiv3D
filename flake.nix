{
  description = "A C++20 framework for creative coding (2D/3D games, media art, visualizers, and simulators).";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" "aarch64-linux" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        packages.default = with pkgs;
          stdenv.mkDerivation rec {
            pname = "OpenSiv3D";
            version = "0.6.14";

            src = ./.;

            nativeBuildInputs = [ cmake ninja ];

            buildInputs = [
              pkgconf
              zlib
              alsaLib
              ffmpeg
              boost175
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
              epoxy
            ];

            cmakeFlags =
              [ "-GNinja" "-DCMAKE_BUILD_TYPE=RelWithDebInfo" "-S ../Linux" ];
          };
      };
    };
}
