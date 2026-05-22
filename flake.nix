{
  description = "arduino environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
      let 
            system = "x86_64-linux";
            pkgs   =  nixpkgs.legacyPackages.${system};
      in { 
      devShells.${system}.default = pkgs.mkShell {
            packages = with pkgs; [
                  arduino-cli
                  arduino-language-server
                  gcc
            ];
            shellHook = ''
                  echo "arduino environment"
            '';
 
      };
  };
}
