{
  description = "arduino environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
      let 
            system = "x86-64_linux";
            pkgs = import nixpkgs { inherit system; };
      in 
      { 
      devShells.${system}.default = pkgs.mkShell {
            package = with pkgs; [
                  arduino-cli
                  arduino-language-server
                  gcc
            ];
      };
  };
}
