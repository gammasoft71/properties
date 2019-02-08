#!/bin/bash

set -ev

# publish to codecov
export CODECOV_TOKEN="d2fd298e-9f95-481a-a1f6-b852a0971c47"
bash <(curl -s https://codecov.io/bash)
