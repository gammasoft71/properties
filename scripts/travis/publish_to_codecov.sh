#!/bin/bash

set -ev

# publish to codecov
export CODECOV_TOKEN="2aed4e26-3197-4973-a3fd-dc5abde4cb8a"
bash <(curl -s https://codecov.io/bash)
