#!/bin/bash

set -xeu -o pipefail

# launch from root repo dir
ext_dir="external"
iesdp_dir="$ext_dir/iesdp"
repo="Gibberlings3/iesdp"
opcode_file="opcode.tpp"

if [[ ! -d "$iesdp_dir" ]]; then
  cd "$tmp_dir"
  git clone https://github.com/$repo/
  cd ..
fi

./scripts/iesdp-update.py -s "$iesdp_dir" --opcode_file "$opcode_file"
