let
pkgs = import(fetchTarball("https://github.com/nixos/nixpkgs/archive/nixos-22.11.tar.gz"))
{};
in
with pkgs;
mkShell{
     buildInputs = [
     pkgs.nlohmann_json
     pkgs.websocketpp
    #pkgs.websocket++ #unsure which one to use
    #used search.nixos.org/packages?channel=22.11 as reference
     pkgs.boost
     pkgs.cmake

     pkgs.nodejs-18_x
   ];
}
