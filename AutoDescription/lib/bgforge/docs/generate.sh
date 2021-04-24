#!/bin/bash

set -xeu -o pipefail

site_dir="docs"
pages_dir="_pages"
data_dir="data"

cd "$site_dir"
mkdir -p "$pages_dir"
./yaml_to_md.py "$data_dir" "$pages_dir"

bundle install
bundle exec jekyll build
